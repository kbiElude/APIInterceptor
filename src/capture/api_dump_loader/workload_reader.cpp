/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#define ZSTD_STATIC_LINKING_ONLY /* ZSTD_d_forceIgnoreChecksum */
#include "capture/api_dump_loader/segment_decoder.h"
#include "capture/api_dump_loader/workload_reader.h"
#include "common/workload_format.h"
#include "zstd_errors.h"
#include <algorithm>
#include <condition_variable>
#include <deque>
#include <map>
#include <mutex>
#include <string.h>
#include <thread>

/* Cuts a file into the frames the dumper wrote (one for each segment), without decompressing anything. */
struct Capture::APIDumpLoader::WorkloadReader::FrameSource
{
    /* What the next bytes of the file are. */
    enum class Result
    {
        CUT,     /* the start of a frame whose end the file does not have: all the bytes that are left        */
        DAMAGED, /* bytes which are not the start of a frame                                                   */
        END,     /* no bytes are left                                                                          */
        FRAME
    };

    FrameSource(FILE*          in_file_handle,
                const uint64_t& in_first_frame_offset)
        :buffer_u8_vec    (INITIAL_BUFFER_N_BYTES),
         end              (0),
         file_handle      (in_file_handle),
         is_at_end        (false),
         last_frame_offset(0),
         next_frame_offset(in_first_frame_offset),
         start            (0)
    {
        /* Stub */
    }

    /* The bytes of the next frame, if there is one. */
    Result read_next(std::vector<uint8_t>* out_frame_byte_vec_ptr)
    {
        Result result = Result::END;

        for (;;)
        {
            const size_t n_bytes_available = end - start;

            if (n_bytes_available != 0)
            {
                const size_t n_frame_bytes = ::ZSTD_findFrameCompressedSize(buffer_u8_vec.data() + start,
                                                                            n_bytes_available);

                if (::ZSTD_isError(n_frame_bytes) == false)
                {
                    out_frame_byte_vec_ptr->assign(buffer_u8_vec.data() + start,
                                                   buffer_u8_vec.data() + start + n_frame_bytes);

                    last_frame_offset  = next_frame_offset;
                    next_frame_offset += n_frame_bytes;
                    start             += n_frame_bytes;

                    result = Result::FRAME;

                    break;
                }

                if (::ZSTD_getErrorCode(n_frame_bytes) != ZSTD_error_srcSize_wrong)
                {
                    result = Result::DAMAGED;

                    break;
                }
            }

            /* Either nothing is there, or not the whole of the frame. */
            if (is_at_end)
            {
                if (n_bytes_available != 0)
                {
                    out_frame_byte_vec_ptr->assign(buffer_u8_vec.data() + start,
                                                   buffer_u8_vec.data() + end);

                    last_frame_offset  = next_frame_offset;
                    next_frame_offset += end - start;
                    start              = end;
                    result = Result::CUT;
                }

                break;
            }

            fill_buffer();
        }

        return result;
    }

    /* Reads more of the file after the bytes which are held, making room for it. */
    void fill_buffer()
    {
        if (start != 0)
        {
            ::memmove(buffer_u8_vec.data(),
                      buffer_u8_vec.data() + start,
                      end - start);

            end   -= start;
            start  = 0;
        }

        if (end == buffer_u8_vec.size() )
        {
            buffer_u8_vec.resize(buffer_u8_vec.size() * 2);
        }

        const size_t n_bytes_read = ::fread(buffer_u8_vec.data() + end,
                                            1,
                                            buffer_u8_vec.size() - end,
                                            file_handle);

        if (n_bytes_read == 0)
        {
            is_at_end = true;
        }

        end += n_bytes_read;
    }


    static constexpr size_t INITIAL_BUFFER_N_BYTES = 8 * 1024 * 1024; /* a frame is a few MB; a larger one makes the buffer grow */

    std::vector<uint8_t> buffer_u8_vec;
    size_t               end;
    FILE*                file_handle;
    bool                 is_at_end;
    uint64_t             last_frame_offset; /* of the frame that read_next() last gave                              */
    uint64_t             next_frame_offset; /* of the one it will give                                              */
    size_t               start;
};

/* The threads which read segments ahead of the caller. */
struct Capture::APIDumpLoader::WorkloadReader::Pipeline
{
    /* A frame to be decoded. */
    struct Job
    {
        uint64_t             file_offset = 0; /* of the frame, in the file        */
        std::vector<uint8_t> frame_byte_vec;
        uint64_t             sequence    = 0; /* the place of the frame in the file */
    };

    Pipeline(FrameSource*    in_frame_source_ptr,
             const uint32_t& in_n_threads,
             const uint32_t& in_n_segments_in_flight,
             const Options&  in_options,
             const bool&     in_ignores_checksums)
        :frame_source_ptr                (in_frame_source_ptr),
         ignores_checksums               (in_ignores_checksums),
         is_damaged                      (false),
         is_producer_done                (false),
         is_stopping                     (false),
         n_frames_produced               (0),
         n_in_flight                     (0),
         n_segments_in_flight            (in_n_segments_in_flight),
         next_sequence                   (0),
         options                         (in_options)
    {
        producer_thread = std::thread(&Pipeline::run_producer,
                                      this);

        for (uint32_t n_thread = 0;
                      n_thread < in_n_threads;
                    ++n_thread)
        {
            worker_thread_vec.emplace_back(&Pipeline::run_worker,
                                           this);
        }
    }

    ~Pipeline()
    {
        {
            std::lock_guard<std::mutex> lock(mutex);

            is_stopping = true;
        }

        job_available_condition.notify_all();
        result_ready_condition.notify_all();
        slot_free_condition.notify_all();

        producer_thread.join();

        for (auto& worker_thread : worker_thread_vec)
        {
            worker_thread.join();
        }
    }

    /* The next segment in the order of the file: waits for it. */
    Fetch take_next(DecodedSegment* out_segment_ptr)
    {
        std::unique_lock<std::mutex> lock(mutex);
        Fetch                        result = Fetch::CLEAN_END;

        result_ready_condition.wait(lock,
                                    [&]()
                                    {
                                        return (result_map.find(next_sequence) != result_map.end() ||
                                                is_stopping                                         ||
                                                (is_producer_done                                   &&
                                                 next_sequence >= n_frames_produced) );
                                    });

        const auto result_iterator = result_map.find(next_sequence);

        if (result_iterator != result_map.end() )
        {
            *out_segment_ptr = std::move(result_iterator->second);

            result_map.erase(result_iterator);

            next_sequence++;
            n_in_flight--;

            result = Fetch::SEGMENT;

            slot_free_condition.notify_one();
        }
        else
        if (is_damaged)
        {
            result = Fetch::DAMAGED_END;
        }

        return result;
    }

    /* Reads the frames from the file, as far as there is room for the segments they will make. */
    void run_producer()
    {
        for (;;)
        {
            FrameSource::Result  source_result = FrameSource::Result::END;
            Job                  job;

            {
                std::unique_lock<std::mutex> lock(mutex);

                slot_free_condition.wait(lock,
                                         [&]()
                                         {
                                             return (n_in_flight < n_segments_in_flight ||
                                                     is_stopping);
                                         });

                if (is_stopping)
                {
                    break;
                }
            }

            source_result   = frame_source_ptr->read_next(&job.frame_byte_vec);
            job.file_offset = frame_source_ptr->last_frame_offset;

            {
                std::lock_guard<std::mutex> lock(mutex);

                if (source_result == FrameSource::Result::END     ||
                    source_result == FrameSource::Result::DAMAGED)
                {
                    is_damaged       = (source_result == FrameSource::Result::DAMAGED);
                    is_producer_done = true;
                }
                else
                {
                    job.sequence = n_frames_produced++;

                    job_deque.push_back(std::move(job) );

                    n_in_flight++;
                }
            }

            /* All of them: when the producer is done, the workers which wait for a job are to see it. */
            job_available_condition.notify_all();
            result_ready_condition.notify_all();

            if (source_result == FrameSource::Result::END     ||
                source_result == FrameSource::Result::DAMAGED)
            {
                break;
            }
        }
    }

    /* Decompresses frames and reads the segments out of them. */
    void run_worker()
    {
        ZSTD_DCtx* decompressor_ptr = ::ZSTD_createDCtx();

        if (ignores_checksums)
        {
            ::ZSTD_DCtx_setParameter(decompressor_ptr,
                                     ZSTD_d_forceIgnoreChecksum,
                                     1);
        }

        for (;;)
        {
            Job            job;
            DecodedSegment decoded_segment;

            {
                std::unique_lock<std::mutex> lock(mutex);

                job_available_condition.wait(lock,
                                             [&]()
                                             {
                                                 return (job_deque.empty() == false ||
                                                         is_stopping                ||
                                                         is_producer_done);
                                             });

                if (is_stopping                         ||
                    job_deque.empty() )
                {
                    break; /* nothing is left to be done (the producer is done, since the wait is over) */
                }

                job = std::move(job_deque.front() );

                job_deque.pop_front();
            }

            if (decompressor_ptr != nullptr)
            {
                decode_frame(decompressor_ptr,
                             job.frame_byte_vec,
                             job.file_offset,
                             options,
                            &decoded_segment);
            }

            decoded_segment.file_offset_n_bytes = job.file_offset;
            decoded_segment.n_compressed_bytes  = job.frame_byte_vec.size();

            {
                std::lock_guard<std::mutex> lock(mutex);

                result_map[job.sequence] = std::move(decoded_segment);
            }

            result_ready_condition.notify_all();
        }

        if (decompressor_ptr != nullptr)
        {
            ::ZSTD_freeDCtx(decompressor_ptr);
        }
    }


    std::condition_variable    job_available_condition;
    FrameSource*               frame_source_ptr;
    bool                       ignores_checksums; /* the decompressors do not check the checksum of a frame */
    bool                       is_damaged;        /* the producer found bytes which are not a frame        */
    bool                       is_producer_done;
    bool                       is_stopping;
    std::deque<Job>            job_deque;
    std::mutex                 mutex;             /* guards all of the below, and the flags above          */
    uint64_t                   n_frames_produced;
    uint32_t                   n_in_flight;       /* jobs queued, being decoded, or decoded and not taken  */
    uint32_t                   n_segments_in_flight;
    uint64_t                   next_sequence;     /* of the segment which the caller is to get next        */
    Options                    options;
    std::thread                producer_thread;
    std::condition_variable    result_ready_condition;
    std::map<uint64_t, DecodedSegment> result_map;
    std::condition_variable    slot_free_condition;
    std::vector<std::thread>   worker_thread_vec;
};

Capture::APIDumpLoader::WorkloadReader::WorkloadReader()
    :m_decompressor_ptr   (::ZSTD_createDCtx() ),
     m_file_handle        (nullptr),
     m_is_finished        (false),
     m_is_truncated       (false),
     m_n_data_chunks_read (0),
     m_pointer_n_bytes    (0),
     m_qpc_frequency      (0)
{
    /* Stub */
}

Capture::APIDumpLoader::WorkloadReader::~WorkloadReader()
{
    /* The threads use the file, so they go first. */
    m_pipeline_ptr.reset();
    m_frame_source_ptr.reset();

    if (m_decompressor_ptr != nullptr)
    {
        ::ZSTD_freeDCtx(m_decompressor_ptr);
    }

    if (m_file_handle != nullptr)
    {
        ::fclose(m_file_handle);
    }
}

bool Capture::APIDumpLoader::WorkloadReader::contains_api_group(const APIGroup& in_group)
{
    bool     result = false;
    Workload workload;

    while (result                       == false &&
           read_next_segment(&workload) )
    {
        for (const auto& call : *workload.dumped_api_call_vec_ptr)
        {
            if (get_api_group(call.func) == in_group)
            {
                result = true;

                break;
            }
        }
    }

    return result;
}

Capture::APIDumpLoader::WorkloadReaderUniquePtr Capture::APIDumpLoader::WorkloadReader::create(const char*  in_filename_ptr,
                                                                                               std::string* out_error_ptr)
{
    return create(in_filename_ptr,
                  Options(),
                  out_error_ptr);
}

Capture::APIDumpLoader::WorkloadReaderUniquePtr Capture::APIDumpLoader::WorkloadReader::create(const char*    in_filename_ptr,
                                                                                               const Options& in_options,
                                                                                               std::string*   out_error_ptr)
{
    std::string                                        error;
    APIInterceptor::WorkloadFormat::WorkloadFileHeader header;
    WorkloadReaderUniquePtr                            result_ptr(new WorkloadReader() );

    if (result_ptr->m_decompressor_ptr == nullptr)
    {
        error = "The decompressor cannot be set up.";

        goto fail;
    }

    result_ptr->m_file_handle = ::fopen(in_filename_ptr,
                                        "rb");

    if (result_ptr->m_file_handle == nullptr)
    {
        error = "The file cannot be opened.";

        goto fail;
    }

    if (::fread(&header,
                sizeof(header),
                1,
                result_ptr->m_file_handle) != 1)
    {
        error = "This is not a workload file, or it was captured by an older version. Capture it again.";

        goto fail;
    }

    if (::memcmp(header.magic_i8vec8,
                 APIInterceptor::WorkloadFormat::MAGIC,
                 sizeof(header.magic_i8vec8) ) != 0)
    {
        error = "This is not a workload file, or it was captured by an older version. Capture it again.";

        goto fail;
    }

    if (header.version != APIInterceptor::WorkloadFormat::FILE_VERSION)
    {
        error = "The workload file has an unsupported version ("             +
                std::to_string(header.version)                               +
                ", expected "                                                +
                std::to_string(APIInterceptor::WorkloadFormat::FILE_VERSION) +
                "). Capture it again.";

        goto fail;
    }

    if (header.pointer_n_bytes != sizeof(uint32_t) &&
        header.pointer_n_bytes != sizeof(uint64_t) )
    {
        error = "The workload file header is corrupt.";

        goto fail;
    }

    result_ptr->m_pointer_n_bytes                = header.pointer_n_bytes;
    result_ptr->m_qpc_frequency                  = header.qpc_frequency;
    result_ptr->m_options                        = in_options;

    if (in_options.ignores_checksums)
    {
        ::ZSTD_DCtx_setParameter(result_ptr->m_decompressor_ptr,
                                 ZSTD_d_forceIgnoreChecksum,
                                 1);
    }

    /* The frames follow the header; a reader that is to start later is given where. */
    result_ptr->m_n_data_chunks_read = in_options.n_data_chunks_before;

    if (in_options.start_offset_n_bytes != 0)
    {
        if (in_options.start_offset_n_bytes < sizeof(header) ||
            ::_fseeki64(result_ptr->m_file_handle,
                        static_cast<__int64>(in_options.start_offset_n_bytes),
                        SEEK_SET) != 0)
        {
            error = "The file cannot be read from the place that was asked for.";

            goto fail;
        }
    }

    result_ptr->m_frame_source_ptr.reset(new FrameSource(result_ptr->m_file_handle,
                                                         (in_options.start_offset_n_bytes != 0) ? in_options.start_offset_n_bytes
                                                                                                : sizeof(header) ) );

    if (in_options.n_threads != 0)
    {
        const uint32_t n_segments_in_flight = (in_options.n_segments_in_flight != 0) ? in_options.n_segments_in_flight
                                                                                     : in_options.n_threads + 2;

        result_ptr->m_pipeline_ptr.reset(new Pipeline(result_ptr->m_frame_source_ptr.get(),
                                                      in_options.n_threads,
                                                      n_segments_in_flight,
                                                      in_options,
                                                      in_options.ignores_checksums) );
    }

    goto end;

fail:
    if (out_error_ptr != nullptr)
    {
        *out_error_ptr = error;
    }

    result_ptr.reset();
end:
    return result_ptr;
}

void Capture::APIDumpLoader::WorkloadReader::decode_frame(ZSTD_DCtx*                  in_decompressor_ptr,
                                                          const std::vector<uint8_t>& in_frame_byte_vec,
                                                          const uint64_t&             in_file_offset_n_bytes,
                                                          const Options&              in_options,
                                                          DecodedSegment*             out_segment_ptr)
{
    FrameStream            stream(in_decompressor_ptr,
                                  in_frame_byte_vec.data(),
                                  in_frame_byte_vec.size() );
    bool                   is_short = false;
    SegmentDecoder::Options options;

    options.skip_data_chunks_above_n_bytes = in_options.skip_data_chunks_above_n_bytes;

    /* The segments the reader has no start of are read in full. */
    if (in_options.chunk_wanted_func)
    {
        const auto start_iterator = std::lower_bound(in_options.segment_start_vec.begin(),
                                                     in_options.segment_start_vec.end(),
                                                     in_file_offset_n_bytes,
                                                     [](const SegmentStart& in_start,
                                                        const uint64_t&     in_offset_n_bytes)
                                                     {
                                                         return (in_start.file_offset_n_bytes < in_offset_n_bytes);
                                                     });

        if (start_iterator                      != in_options.segment_start_vec.end() &&
            start_iterator->file_offset_n_bytes == in_file_offset_n_bytes)
        {
            options.chunk_wanted_func   = in_options.chunk_wanted_func;
            options.first_data_chunk_id = start_iterator->first_data_chunk_id;
            options.first_frame_index   = start_iterator->first_frame_index;
        }
    }

    out_segment_ptr->workload_ptr.reset(new Workload() );

    out_segment_ptr->has_segment = SegmentDecoder::parse_segment(&stream,
                                                                  options,
                                                                  out_segment_ptr->workload_ptr.get(),
                                                                 &is_short);

    out_segment_ptr->is_truncated = is_short;

    /* A segment which was read in full still has the end of its frame to be checked. */
    if (is_short == false)
    {
        out_segment_ptr->is_truncated = (stream.finish() == false);
    }
}

Capture::APIDumpLoader::WorkloadReader::Fetch Capture::APIDumpLoader::WorkloadReader::fetch_next_segment(DecodedSegment* out_segment_ptr)
{
    std::vector<uint8_t> frame_byte_vec;
    Fetch                result = Fetch::CLEAN_END;

    if (m_pipeline_ptr != nullptr)
    {
        result = m_pipeline_ptr->take_next(out_segment_ptr);

        goto end;
    }

    switch (m_frame_source_ptr->read_next(&frame_byte_vec) )
    {
        case FrameSource::Result::CUT:
        case FrameSource::Result::FRAME:
        {
            decode_frame(m_decompressor_ptr,
                         frame_byte_vec,
                         m_frame_source_ptr->last_frame_offset,
                         m_options,
                         out_segment_ptr);

            out_segment_ptr->file_offset_n_bytes = m_frame_source_ptr->last_frame_offset;
            out_segment_ptr->n_compressed_bytes  = frame_byte_vec.size();

            result = Fetch::SEGMENT;

            break;
        }

        case FrameSource::Result::DAMAGED:
        {
            result = Fetch::DAMAGED_END;

            break;
        }

        case FrameSource::Result::END:
        {
            result = Fetch::CLEAN_END;

            break;
        }

        default:
        {
            result = Fetch::DAMAGED_END;

            break;
        }
    }

end:
    return result;
}

uint32_t Capture::APIDumpLoader::WorkloadReader::get_pointer_n_bytes() const
{
    return m_pointer_n_bytes;
}

bool Capture::APIDumpLoader::WorkloadReader::is_truncated() const
{
    return m_is_truncated;
}

bool Capture::APIDumpLoader::WorkloadReader::read_next_segment(Workload* out_workload_ptr)
{
    DecodedSegment segment;
    bool           result = false;

    if (m_is_finished)
    {
        goto end;
    }

    switch (fetch_next_segment(&segment) )
    {
        case Fetch::CLEAN_END:
        {
            m_is_finished = true;

            break;
        }

        case Fetch::DAMAGED_END:
        {
            m_is_finished  = true;
            m_is_truncated = true;

            break;
        }

        case Fetch::SEGMENT:
        {
            if (segment.has_segment == false)
            {
                /* So little is left of the frame that not even the counts of the segment are. */
                m_is_finished  = true;
                m_is_truncated = true;

                break;
            }

            *out_workload_ptr = std::move(*segment.workload_ptr);

            out_workload_ptr->file_offset_n_bytes = segment.file_offset_n_bytes;
            out_workload_ptr->first_data_chunk_id = m_n_data_chunks_read;
            out_workload_ptr->n_compressed_bytes  = segment.n_compressed_bytes;
            out_workload_ptr->pointer_n_bytes     = m_pointer_n_bytes;
            out_workload_ptr->qpc_frequency       = m_qpc_frequency;

            m_n_data_chunks_read += static_cast<uint32_t>(out_workload_ptr->data_chunk_ptr_vec.size() );

            if (segment.is_truncated)
            {
                m_is_finished  = true;
                m_is_truncated = true;
            }

            result = true;

            break;
        }

        default:
        {
            m_is_finished = true;

            break;
        }
    }

end:
    return result;
}
