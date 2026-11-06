/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "call_walker.h"
#include "capture/api_dump_loader/workload_index.h"
#include <algorithm>
#include <thread>

Replay::ReplayEngineDLL::CallWalker::CallWalker()
    :m_n_next_call(0)
{
    /* Stub */
}

Replay::ReplayEngineDLL::CallWalker::~CallWalker()
{
    stop_prefetching();
}

const Capture::APIDumpLoader::DataChunk* Replay::ReplayEngineDLL::CallWalker::get_data_chunk_ptr(const uint32_t& in_data_chunk_id) const
{
    return Capture::APIDumpLoader::get_data_chunk_ptr(m_segment,
                                                      in_data_chunk_id);
}

uint32_t Replay::ReplayEngineDLL::CallWalker::get_pointer_n_bytes() const
{
    return m_segment.pointer_n_bytes;
}

const Capture::APIDumpLoader::Workload& Replay::ReplayEngineDLL::CallWalker::get_segment() const
{
    return m_segment;
}

bool Replay::ReplayEngineDLL::CallWalker::open(const char*  in_filename_ptr,
                                               std::string* out_error_ptr)
{
    bool result = false;

    if (start_reader(in_filename_ptr,
                     0, /* in_start_offset_n_bytes */
                     0, /* in_n_data_chunks_before */
                     out_error_ptr) == false)
    {
        goto end;
    }

    m_filename    = in_filename_ptr;
    m_n_next_call = 0;
    m_segment     = Capture::APIDumpLoader::Workload();
    result        = true;

end:
    return result;
}

void Replay::ReplayEngineDLL::CallWalker::prefetch_main()
{
    bool is_done = false;

    while (is_done == false)
    {
        Capture::APIDumpLoader::Workload next_segment;
        Capture::APIDumpLoader::Workload old_segment;
        bool                             is_read = false;

        {
            std::unique_lock<std::mutex> lock(m_prefetch.mutex);

            const auto can_prefetch_func = [this]()
            {
                return (m_prefetch.is_ready == false ||
                        m_prefetch.is_stop_requested);
            };

            m_prefetch.cv.wait(lock,
                               can_prefetch_func);

            if (m_prefetch.is_stop_requested)
            {
                break;
            }

            /* What is left in the slot is the segment which the replay has finished with. */
            old_segment = std::move(m_prefetch.segment);
        }

        /* Free the memory of the old segment (it takes a while), then read the next one. */
        old_segment = Capture::APIDumpLoader::Workload();
        is_read     = m_reader_ptr->read_next_segment (&next_segment);

        {
            std::lock_guard<std::mutex> lock(m_prefetch.mutex);

            if (m_prefetch.is_stop_requested)
            {
                break;
            }

            if (is_read)
            {
                m_prefetch.segment  = std::move(next_segment);
                m_prefetch.is_ready = true;
            }
            else
            {
                m_prefetch.is_finished = true;
            }
        }

        m_prefetch.cv.notify_all();

        is_done = (is_read == false);
    }
}

bool Replay::ReplayEngineDLL::CallWalker::read_next_call(const Capture::APIDumpLoader::DumpedAPICall** out_call_ptr_ptr)
{
    bool result = false;

    if (m_reader_ptr == nullptr)
    {
        goto end;
    }

    /* A segment may hold no calls; skip those. */
    while (m_segment.dumped_api_call_vec_ptr == nullptr                                   ||
           m_n_next_call                     >= m_segment.dumped_api_call_vec_ptr->size() )
    {
        if (read_next_segment() == false)
        {
            goto end;
        }
    }

    *out_call_ptr_ptr = &m_segment.dumped_api_call_vec_ptr->at(m_n_next_call);
    m_n_next_call++;

    result = true;

end:
    return result;
}

bool Replay::ReplayEngineDLL::CallWalker::read_next_segment()
{
    bool result = false;

    m_n_next_call = 0;

    /* The segments after the one that is being left are the ones the new filter is for: those the reader has read ahead are read again. */
    if (takes_pending_chunk_filter() )
    {
        std::string error;

        /* A reader that cannot be started leaves the old one at work: all the chunks are read, which is slower and not wrong. */
        start_reader(m_filename.c_str(),
                     m_segment.file_offset_n_bytes + m_segment.n_compressed_bytes,
                     m_segment.first_data_chunk_id + static_cast<uint32_t>(m_segment.data_chunk_ptr_vec.size() ),
                    &error);
    }

    {
        std::unique_lock<std::mutex> lock(m_prefetch.mutex);

        const auto is_prefetch_done_func = [this]()
        {
            return (m_prefetch.is_ready ||
                    m_prefetch.is_finished);
        };

        m_prefetch.cv.wait(lock,
                           is_prefetch_done_func);

        if (m_prefetch.is_ready)
        {
            /* The old segment goes to the thread, which destroys it. */
            std::swap(m_segment,
                      m_prefetch.segment);

            m_prefetch.is_ready = false;
            result              = true;
        }
    }

    m_prefetch.cv.notify_all();

    return result;
}

bool Replay::ReplayEngineDLL::CallWalker::read_segment_starts(const char*                                                        in_filename_ptr,
                                                              std::vector<Capture::APIDumpLoader::WorkloadReader::SegmentStart>* out_start_vec_ptr)
{
    const std::string                     index_filename = Capture::APIDumpLoader::WorkloadIndex::get_default_filename(in_filename_ptr);
    Capture::APIDumpLoader::WorkloadIndex index;
    std::string                           error;
    bool                                  result = false;

    if (Capture::APIDumpLoader::WorkloadIndex::load(index_filename.c_str(),
                                                   &index,
                                                   &error) == false)
    {
        goto end;
    }

    if (index.is_of(in_filename_ptr) == false)
    {
        goto end;
    }

    for (const auto& entry : index.get_segment_vec() )
    {
        Capture::APIDumpLoader::WorkloadReader::SegmentStart start;

        start.file_offset_n_bytes = entry.file_offset_n_bytes;
        start.first_data_chunk_id = entry.first_data_chunk_id;
        start.first_frame_index   = entry.first_frame_index;

        out_start_vec_ptr->push_back(start);
    }

    result = true;

end:
    return result;
}

bool Replay::ReplayEngineDLL::CallWalker::rewind(std::string* out_error_ptr)
{
    const std::string filename = m_filename;

    return open(filename.c_str(),
                out_error_ptr);
}

void Replay::ReplayEngineDLL::CallWalker::set_chunk_wanted_func(const Capture::APIDumpLoader::ChunkWantedFunc& in_func)
{
    std::lock_guard<std::mutex> lock(m_chunk_filter.mutex);

    m_chunk_filter.func       = in_func;
    m_chunk_filter.is_pending = true;
}

bool Replay::ReplayEngineDLL::CallWalker::start_reader(const char*     in_filename_ptr,
                                                       const uint64_t& in_start_offset_n_bytes,
                                                       const uint32_t& in_n_data_chunks_before,
                                                       std::string*    out_error_ptr)
{
    /* Segments are decompressed and read by threads of the loader, which a replay needs: playing the first frames of a long workload means
     * reading all the segments before them. A segment held is some 100 to 200 MB, and the replay of a 32-bit application is a 32-bit process
     * with two gigabytes to put them in (the segments being read, this walker's own two, and the one that is being freed), so it has a few. What
     * more threads would do for segments that are read in full (the work is of the memory) is not worth the risk of running out.
     */
    constexpr uint32_t N_READER_THREADS_32_BIT   = 3;
    constexpr uint32_t N_READER_THREADS_64_BIT   = 6;
    constexpr uint32_t N_READER_THREADS_FILTERED = 6; /* when chunks are left out: see below */

    const uint32_t                                  n_threads_wanted = (sizeof(void*) == sizeof(uint32_t) ) ? N_READER_THREADS_32_BIT
                                                                                                           : N_READER_THREADS_64_BIT;
    const uint32_t                                  n_cores          = std::max<uint32_t>(2,
                                                                                          std::thread::hardware_concurrency() );
    std::string                                     error;
    Capture::APIDumpLoader::WorkloadReader::Options reader_options;
    bool                                            result           = false;

    /* A replay reads a workload again and again (a seek starts over): the checksums of its frames are for the tools that say what is in it. */
    reader_options.ignores_checksums     = true;
    reader_options.n_threads             = std::min<uint32_t>(n_threads_wanted,
                                                              n_cores - 1);
    reader_options.n_segments_in_flight  = reader_options.n_threads + 1;
    reader_options.n_data_chunks_before  = in_n_data_chunks_before;
    reader_options.start_offset_n_bytes  = in_start_offset_n_bytes;

    {
        std::lock_guard<std::mutex> lock(m_chunk_filter.mutex);

        reader_options.chunk_wanted_func = m_chunk_filter.func;
        m_chunk_filter.is_pending        = false;
    }

    /* Without the index of the file there is no telling which frame a segment starts at, and all its chunks are read. */
    if (reader_options.chunk_wanted_func)
    {
        if (read_segment_starts(in_filename_ptr,
                               &reader_options.segment_start_vec) == false)
        {
            reader_options.chunk_wanted_func = Capture::APIDumpLoader::ChunkWantedFunc();
        }
    }

    /* With the chunks of the frames that nothing reads left out, the segments are small (a few MB, and not 100 to 200), and what takes the time is the
     * decompression, which more threads speed up: a seek to a frame of Kasparov takes 6.5 s with 3 threads, 4.9 s with 6, 4.8 s with 8. The peak memory of the
     * process is 1.2 GB with 6 (0.8 GB with 3), and 1.5 GB when it plays on from the frame, with the chunks of every frame again.
     */
    if (reader_options.chunk_wanted_func)
    {
        reader_options.n_threads            = std::min<uint32_t>(std::max<uint32_t>(n_threads_wanted,
                                                                                    N_READER_THREADS_FILTERED),
                                                                 n_cores - 1);
        reader_options.n_segments_in_flight = reader_options.n_threads + 1;
    }

    Capture::APIDumpLoader::WorkloadReaderUniquePtr reader_ptr = Capture::APIDumpLoader::WorkloadReader::create(in_filename_ptr,
                                                                                                                reader_options,
                                                                                                                &error);

    if (reader_ptr == nullptr)
    {
        if (out_error_ptr != nullptr)
        {
            *out_error_ptr = error;
        }

        goto end;
    }

    stop_prefetching();

    m_reader_ptr = std::move(reader_ptr);

    {
        std::lock_guard<std::mutex> lock(m_prefetch.mutex);

        m_prefetch.is_finished       = false;
        m_prefetch.is_ready          = false;
        m_prefetch.is_stop_requested = false;
        m_prefetch.segment           = Capture::APIDumpLoader::Workload();
    }

    m_prefetch_thread = std::thread(&CallWalker::prefetch_main,
                                    this);
    result            = true;

end:
    return result;
}

void Replay::ReplayEngineDLL::CallWalker::stop_prefetching()
{
    {
        std::lock_guard<std::mutex> lock(m_prefetch.mutex);

        m_prefetch.is_stop_requested = true;
    }

    m_prefetch.cv.notify_all();

    if (m_prefetch_thread.joinable() )
    {
        m_prefetch_thread.join();
    }
}

bool Replay::ReplayEngineDLL::CallWalker::takes_pending_chunk_filter()
{
    std::lock_guard<std::mutex> lock(m_chunk_filter.mutex);

    const bool result = m_chunk_filter.is_pending;

    m_chunk_filter.is_pending = false;

    return result;
}
