/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include <Windows.h>
#include "Common/callbacks.h"
#include "Common/frame_boundary.h"
#include "Common/macros.h"
#include "Common/workload_format.h"
#include "Interception/Hooks/Kernel32/callbacks.h"
#include "api_dumper.h"
#include "d3d7_swapchain_reader.h"
#include "d3d8_swapchain_reader.h"
#include "opengl_swapchain_reader.h"
#include "zstd_file_writer.h"
#include <algorithm>
#include <cassert>
#include <mutex>
#include <string.h>

/* Used by the constructor. */
static constexpr uint64_t DEFAULT_N_BYTES_BEFORE_SPILL = 128ull * 1024 * 1024;

APIDumper::APIDumper()
{
    m_settings.n_bytes_before_spill = DEFAULT_N_BYTES_BEFORE_SPILL;
}

APIDumper::~APIDumper()
{
    write_workload ();
    wait_for_writer();
}

APIDumperUniquePtr APIDumper::create()
{
    APIDumperUniquePtr result_ptr(new APIDumper() );

    if (result_ptr != nullptr)
    {
        if (result_ptr->init() == false)
        {
            result_ptr.reset();
        }
    }

    return result_ptr;
}

void APIDumper::cut_segment(const bool& in_is_last)
{
    /* Another thread presenting at the same time need not cut as well. The last segment is not optional, though. */
    if (in_is_last)
    {
        std::lock_guard<std::mutex> cut_guard(m_cut.mutex);

        perform_cut(true); /* in_is_last */
    }
    else
    {
        std::unique_lock<std::mutex> cut_lock(m_cut.mutex,
                                              std::try_to_lock);

        if (cut_lock.owns_lock() )
        {
            perform_cut(false); /* in_is_last */
        }
    }
}

uint64_t APIDumper::get_n_unwritten_bytes()
{
    const uint32_t n_data_chunks = APIInterceptor::get_n_data_chunks();

    /* Data chunks are counted once, as they show up. */
    for (;
         m_recorded.chunk_scan_cursor < n_data_chunks;
         m_recorded.chunk_scan_cursor++)
    {
        const void* data_chunk_ptr  = nullptr;
        uint32_t    data_chunk_size = 0;

        if (APIInterceptor::get_data_chunk(m_recorded.chunk_scan_cursor,
                                          &data_chunk_ptr,
                                          &data_chunk_size) )
        {
            m_recorded.n_chunk_bytes_counted += data_chunk_size;
        }
    }

    return m_recorded.api_call_deque.size() * sizeof(DumpedAPICall) + m_recorded.n_chunk_bytes_counted + m_recorded.n_surface_bytes;
}

bool APIDumper::init()
{
    bool result = false;

    /* Load settings */
    {
        constexpr uint64_t N_BYTES_PER_MB = 1024 * 1024;

        uint8_t settings_data_raw_u8vec12[12] = {};
        FILE*   settings_file_handle          = ::fopen("apidumper_settings.bin",
                                                        "rb");

        if (settings_file_handle == nullptr)
        {
            assert(settings_file_handle != nullptr);

            goto end;
        }

        if (::fread(settings_data_raw_u8vec12,
                     sizeof(settings_data_raw_u8vec12),
                     1,
                     settings_file_handle) != 1)
        {
            assert(false);

            goto end;
        }

        m_settings.n_frames_to_dump          = *reinterpret_cast<const uint32_t*>(settings_data_raw_u8vec12 + 0 * sizeof(uint32_t) );
        m_settings.dump_swapchain_on_present = *reinterpret_cast<const uint32_t*>(settings_data_raw_u8vec12 + 1 * sizeof(uint32_t) ) != 0;
        m_settings.n_bytes_before_spill      = static_cast<uint64_t>(*reinterpret_cast<const uint32_t*>(settings_data_raw_u8vec12 + 2 * sizeof(uint32_t) ) ) * N_BYTES_PER_MB;

        ::fclose(settings_file_handle);
    }

    /* Register for callbacks */
    for (uint32_t n_api_func = 0;
                  n_api_func < APIInterceptor::APIFUNCTION_COUNT;
                ++n_api_func)
    {
        APIInterceptor::register_for_post_callback(static_cast<APIInterceptor::APIFunction>(n_api_func),
                                                  &on_post_callback,
                                                   this);
        APIInterceptor::register_for_pre_callback (static_cast<APIInterceptor::APIFunction>(n_api_func),
                                                  &on_pre_callback,
                                                   this);
    }

    /* Segments are appended to the workload file as the dump grows. */
    m_recorded.file_handle = ::fopen("result_dump.workload",
                                     "wb");

    if (m_recorded.file_handle == nullptr)
    {
        assert(m_recorded.file_handle != nullptr);

        goto end;
    }

    /* The file starts with a header which says how to read the rest. */
    {
        APIInterceptor::WorkloadFormat::WorkloadFileHeader header = {};
        LARGE_INTEGER                                      qpc_frequency;

        ::QueryPerformanceFrequency(&qpc_frequency);

        ::memcpy(header.magic_i8vec8,
                 APIInterceptor::WorkloadFormat::MAGIC,
                 sizeof(header.magic_i8vec8) );

        header.pointer_n_bytes = static_cast<uint32_t>(sizeof(void*) );
        header.qpc_frequency   = static_cast<uint64_t>(qpc_frequency.QuadPart);
        header.version         = APIInterceptor::WorkloadFormat::FILE_VERSION;

        if (::fwrite(&header,
                     sizeof(header),
                     1,
                     m_recorded.file_handle) != 1)
        {
            assert(false);

            goto end;
        }
    }

    /* The writer thread would not survive the process being taken down, so the app's exit gives it time to finish. */
    Interception::Hooks::Kernel32::register_for_process_exiting_callback(on_process_exiting,
                                                                         this);

    result = true;
end:
    return result;
}

void APIDumper::on_frame_presented()
{
    bool is_dump_complete = false;
    bool should_spill     = false;

    {
        std::lock_guard<std::mutex> guard(m_recorded.mutex);

        is_dump_complete = (m_recorded.n_frames_dumped >= m_settings.n_frames_to_dump);
        should_spill     = (get_n_unwritten_bytes()    >= m_settings.n_bytes_before_spill);
    }

    /* The dump is complete: write it now, so the process need not exit gracefully. Otherwise, frame boundaries are
     * the one place where no call is half-recorded, so the dump can be cut there.
     */
    if (is_dump_complete)
    {
        cut_segment(true); /* in_is_last */
    }
    else
    if (should_spill)
    {
        cut_segment(false); /* in_is_last */
    }
}

void APIDumper::on_post_callback(APIInterceptor::APIFunction                in_api_func,
                                 void*                                      in_user_arg_ptr,
                                 uint32_t                                   in_n_arguments_out,
                                 const APIInterceptor::APIFunctionArgument* in_arguments_out_ptr,
                                 const APIInterceptor::APIFunctionArgument* in_returned_value_ptr)
{
    bool       is_frame_presented = false;
    APIDumper* this_ptr           = reinterpret_cast<APIDumper*>(in_user_arg_ptr);

    {
        std::lock_guard<std::mutex> guard(this_ptr->m_recorded.mutex);

        /* Ignore this callback if we've already dumped sufficient number of frames! */
        if (this_ptr->m_recorded.n_frames_dumped < this_ptr->m_settings.n_frames_to_dump)
        {
            /* Update the cached API call's out args and returned value.
             *
             * In cases where OS DLL implementing the API function calls intercepted API functions, the relevant item
             * may be a few items back. Calls from other threads may be in between, too, so look for the latest call of
             * this function made by this thread which is still waiting for its results.
             *
             * A call which is not there was recorded before the dump was completed, and is already written.
             */
            const auto this_thread_id = static_cast<uint32_t>(::GetCurrentThreadId() );

            auto deque_iterator = std::find_if(this_ptr->m_recorded.api_call_deque.rbegin(),
                                               this_ptr->m_recorded.api_call_deque.rend  (),
                                               [&](const DumpedAPICall& in_api_call)
                                               {
                                                  return (in_api_call.api_func     == in_api_func)    &&
                                                         (in_api_call.thread_id    == this_thread_id) &&
                                                         (in_api_call.is_completed == false);
                                               });

            if (deque_iterator != this_ptr->m_recorded.api_call_deque.rend() )
            {
                if (in_n_arguments_out > APIInterceptor::MAX_N_FUNCTION_ARGUMENTS)
                {
                    AI_FAIL_UNSUPPORTED(in_n_arguments_out);
                }

                deque_iterator->is_completed    =  true;
                deque_iterator->n_arguments_out =  in_n_arguments_out;
                deque_iterator->returned_value  = *in_returned_value_ptr;

                for (uint32_t n_arg = 0;
                              n_arg < in_n_arguments_out;
                            ++n_arg)
                {
                    deque_iterator->arguments_out[n_arg] = in_arguments_out_ptr[n_arg];
                }
            }
        }

        /* If this is a frame present call, increment internal counter.
         *
         * TODO: This will break down badly for apps that do NOT use back buffer..
         */
        if (APIInterceptor::is_frame_boundary(in_api_func,
                                              in_n_arguments_out,
                                              in_arguments_out_ptr) )
        {
            this_ptr->m_recorded.n_frames_dumped++;

            is_frame_presented = true;
        }
    }

    if (is_frame_presented)
    {
        this_ptr->on_frame_presented();
    }
}

void APIDumper::on_pre_callback(APIInterceptor::APIFunction                in_api_func,
                                uint32_t                                   in_n_arguments_in,
                                const APIInterceptor::APIFunctionArgument* in_arguments_in_ptr,
                                void*                                      in_user_arg_ptr,
                                bool*                                      out_should_pass_through_ptr)
{
    APIDumper* this_ptr(reinterpret_cast<APIDumper*>(in_user_arg_ptr) );

    /* Not an assert: a call with more arguments than the dump has room for must never be written past the end of its arrays. */
    if (in_n_arguments_in > APIInterceptor::MAX_N_FUNCTION_ARGUMENTS)
    {
        AI_FAIL_UNSUPPORTED(in_n_arguments_in);
    }

    if (this_ptr->m_recorded.n_frames_dumped < this_ptr->m_settings.n_frames_to_dump &&
        this_ptr->m_settings.dump_swapchain_on_present)
    {
        DumpedSurface new_surface;

        if (read_frame_surface(in_api_func,
                               in_n_arguments_in,
                               in_arguments_in_ptr,
                              &new_surface) )
        {
            this_ptr->store_surface(std::move(new_surface) );
        }
    }

    /* Do NOT dump the API call if we've already dumped sufficient number of frames! */
    if (this_ptr->m_recorded.n_frames_dumped < this_ptr->m_settings.n_frames_to_dump)
    {
        /* Cache API call's properties.
         *
         * TODO: This code totally ignores the fact that pointers passed to API calls may go out of scope
         *       as soon as the API call is handled. This works fine for Q1 but will fail massively for
         *       any more complex workload!
         */
        {
            DumpedAPICall new_item;
            LARGE_INTEGER qpc_timestamp;

            ::QueryPerformanceCounter(&qpc_timestamp);

            new_item.api_func      = in_api_func;
            new_item.n_arguments_in     = in_n_arguments_in;
            new_item.thread_id     = static_cast<uint32_t>(::GetCurrentThreadId() );
            new_item.timestamp_qpc = static_cast<uint64_t>(qpc_timestamp.QuadPart);

            for (uint32_t n_arg = 0;
                          n_arg < in_n_arguments_in;
                        ++n_arg)
            {
                new_item.arguments_in[n_arg] = in_arguments_in_ptr[n_arg];
            }

            {
                std::lock_guard<std::mutex> guard(this_ptr->m_recorded.mutex);

                this_ptr->m_recorded.api_call_deque.emplace_back(new_item);
            }
        }
    }

    /* Always pass through any of the intercepted calls */
    *out_should_pass_through_ptr = true;
}

void APIDumper::on_process_exiting(void* in_user_arg_ptr)
{
    APIDumper* this_ptr = reinterpret_cast<APIDumper*>(in_user_arg_ptr);

    /* The process is about to be taken down, and a running writer thread with it. Hand over what is left, and wait.
     * A cut which is under way finishes first.
     */
    {
        std::lock_guard<std::mutex> cut_guard(this_ptr->m_cut.mutex);

        {
            std::lock_guard<std::mutex> guard(this_ptr->m_recorded.mutex);

            this_ptr->write_workload();
        }
    }

    this_ptr->wait_for_writer();
}

void APIDumper::perform_cut(const bool& in_is_last)
{
    /* How long to wait for other threads to leave their API calls, before giving up on this cut. */
    constexpr uint32_t QUIESCE_TIMEOUT_MS = 100;
    bool               is_quiescent       = false;

    /* Waiting for the previous segment to be written must not hold back the other threads. */
    wait_for_writer();

    is_quiescent = APIInterceptor::try_quiesce_api_calls(QUIESCE_TIMEOUT_MS);

    /* Some thread is stuck in a call. A spill can wait for the next frame, but the last segment cannot. */
    if (is_quiescent == false &&
        in_is_last    == false)
    {
        goto end;
    }

    {
        std::lock_guard<std::mutex> guard(m_recorded.mutex);

        if (in_is_last)
        {
            write_workload();
        }
        else
        {
            submit_segment(false); /* in_is_last */
        }
    }

    if (is_quiescent)
    {
        APIInterceptor::resume_api_calls();
    }

end:
    ;
}

bool APIDumper::read_frame_surface(const APIInterceptor::APIFunction&         in_api_func,
                                   const uint32_t&                            in_n_arguments_in,
                                   const APIInterceptor::APIFunctionArgument* in_arguments_in_ptr,
                                   DumpedSurface*                             out_surface_ptr)
{
    typedef std::unique_ptr<std::vector<uint8_t> > RGBAUniquePtr;

    RGBAUniquePtr         rgba_u8_vec_ptr(new std::vector<uint8_t>() );
    std::vector<uint8_t>* rgba_ptr = rgba_u8_vec_ptr.get();
    bool                  result   = false;

    /* The frame is read before the call which presents it. */
    switch (in_api_func)
    {
        case APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAWSURFACE7_BLT:
        case APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAWSURFACE7_BLTFAST:
        {
            /* The surface which is blitted from, in the arguments of the method (the surface which is blitted to is the first). */
            constexpr uint32_t BLT_SOURCE_ARGUMENT     = 2;
            constexpr uint32_t BLT_FAST_SOURCE_ARGUMENT = 3;

            const bool     is_presenting   = APIInterceptor::is_frame_boundary(in_api_func,
                                                                               in_n_arguments_in,
                                                                               in_arguments_in_ptr);
            const uint32_t source_argument = (in_api_func == APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAWSURFACE7_BLT) ? BLT_SOURCE_ARGUMENT
                                                                                                                       : BLT_FAST_SOURCE_ARGUMENT;

            /* Only a blit to the primary surface ends a frame. */
            if (is_presenting)
            {
                void* const source_ptr = const_cast<void*>(in_arguments_in_ptr[source_argument].get_ptr() );

                if (source_ptr != nullptr)
                {
                    result = Capture::APIDumperDLL::D3D7SwapchainReader::read_surface(source_ptr,
                                                                                     &out_surface_ptr->extents_u32vec2,
                                                                                      rgba_ptr);
                }
            }

            break;
        }

        case APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAWSURFACE7_FLIP:
        {
            /* The surface which is flipped is the first argument, and the one that is flipped to is the second, or else the back buffer. */
            void* const primary_ptr = const_cast<void*>(in_arguments_in_ptr[0].get_ptr() );
            void* const target_ptr  = const_cast<void*>(in_arguments_in_ptr[1].get_ptr() );

            if (target_ptr != nullptr)
            {
                result = Capture::APIDumperDLL::D3D7SwapchainReader::read_surface(target_ptr,
                                                                                 &out_surface_ptr->extents_u32vec2,
                                                                                  rgba_ptr);
            }
            else
            {
                result = Capture::APIDumperDLL::D3D7SwapchainReader::read_back_buffer(primary_ptr,
                                                                                     &out_surface_ptr->extents_u32vec2,
                                                                                      rgba_ptr);
            }

            break;
        }

        case APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_PRESENT:
        {
            /* The device is the first argument of the call. */
            void* const device_ptr = const_cast<void*>(in_arguments_in_ptr[0].get_ptr() );

            result = Capture::APIDumperDLL::D3D8SwapchainReader::read(device_ptr,
                                                                     &out_surface_ptr->extents_u32vec2,
                                                                      rgba_ptr);

            break;
        }

        case APIInterceptor::APIFUNCTION_GDI32_SWAPBUFFERS:
        {
            /* The device context is the first argument of the call. */
            void* const device_context_ptr = const_cast<void*>(in_arguments_in_ptr[0].get_ptr() );

            result = Capture::APIDumperDLL::OpenGLSwapchainReader::read(device_context_ptr,
                                                                       &out_surface_ptr->extents_u32vec2,
                                                                        rgba_ptr);

            break;
        }

        default:
        {
            /* A call which does not present a frame of an API the dumper can read. */
            break;
        }
    }

    if (result)
    {
        out_surface_ptr->u8_vec_ptr = std::move(rgba_u8_vec_ptr);
    }

    return result;
}

void APIDumper::store_surface(DumpedSurface in_surface)
{
    {
        std::lock_guard<std::mutex> guard(m_recorded.mutex);

        m_recorded.n_surface_bytes += in_surface.u8_vec_ptr->size();

        m_recorded.surface_vec.emplace_back(std::move(in_surface) );
    }
}


void APIDumper::submit_segment(const bool& in_is_last)
{
    SegmentJobUniquePtr job_ptr(new SegmentJob() );

    /* Blocks only if the writer is still busy with the previous segment. */
    wait_for_writer();

    {
        const uint32_t first_data_chunk = m_recorded.n_data_chunks_written;
        const uint32_t n_data_chunks    = APIInterceptor::get_n_data_chunks() - first_data_chunk;

        /* The render thread only moves the data around; serializing and writing it is up to the writer. */
        job_ptr->api_call_deque.swap(m_recorded.api_call_deque);

        job_ptr->file_handle       = m_recorded.file_handle;
        job_ptr->should_close_file = in_is_last;

        job_ptr->surface_vec.swap(m_recorded.surface_vec);

        APIInterceptor::take_data_chunks(first_data_chunk,
                                         n_data_chunks,
                                        &job_ptr->data_chunk_vec);

        m_recorded.chunk_scan_cursor     = first_data_chunk + n_data_chunks;
        m_recorded.n_chunk_bytes_counted = 0;
        m_recorded.n_data_chunks_written = first_data_chunk + n_data_chunks;
        m_recorded.n_surface_bytes       = 0;
    }

    /* The writer owns the file from now on. */
    if (in_is_last)
    {
        m_recorded.file_handle = nullptr;
    }

    m_cut.writer_thread = std::thread(&APIDumper::write_segment,
                                  std::move(job_ptr) );
}

void APIDumper::wait_for_writer()
{
    if (m_cut.writer_thread.joinable() )
    {
        m_cut.writer_thread.join();
    }
}

void APIDumper::write_segment(SegmentJobUniquePtr in_job_ptr)
{
    /* Compression happens on the writer thread, which runs at a low priority; this level keeps up with the app. */
    constexpr int    COMPRESSION_LEVEL       = 3;
    constexpr size_t N_SEGMENT_COUNTS        = 3; /* API calls, data chunks, surfaces */
    constexpr size_t N_SURFACE_HEADER_FIELDS = 3; /* width, height, n bytes           */

    FILE* const                                    file_handle = in_job_ptr->file_handle;
    Capture::APIDumperDLL::ZstdFileWriterUniquePtr writer_ptr;

    /* The writer must not disturb the app, nor be recorded. */
    ::SetThreadPriority(::GetCurrentThread(),
                        THREAD_PRIORITY_BELOW_NORMAL);

    APIInterceptor::disable_callbacks_for_this_thread();

    if (file_handle != nullptr)
    {
        writer_ptr = Capture::APIDumperDLL::ZstdFileWriter::create(file_handle,
                                                                   COMPRESSION_LEVEL);
    }

    if (writer_ptr != nullptr)
    {
        const uint32_t       n_api_calls       = static_cast<uint32_t>(in_job_ptr->api_call_deque.size() );
        const uint32_t       n_data_chunks     = static_cast<uint32_t>(in_job_ptr->data_chunk_vec.size() );
        const uint32_t       n_dumped_surfaces = static_cast<uint32_t>(in_job_ptr->surface_vec.size   () );
        std::vector<uint8_t> helper_u8_vec;

        /* Items are written out as they are put together, so that a big segment need not exist in memory twice. */
        const auto flush_func = [&]()
        {
            if (helper_u8_vec.empty() == false)
            {
                writer_ptr->write(helper_u8_vec.data(),
                                  helper_u8_vec.size() );

                helper_u8_vec.clear();
            }
        };

        /* Segment props come first.  */
        {
            helper_u8_vec.resize(sizeof(uint32_t) * N_SEGMENT_COUNTS);

            *(reinterpret_cast<uint32_t*>(helper_u8_vec.data() ) + 0) = n_api_calls;
            *(reinterpret_cast<uint32_t*>(helper_u8_vec.data() ) + 1) = n_data_chunks;
            *(reinterpret_cast<uint32_t*>(helper_u8_vec.data() ) + 2) = n_dumped_surfaces;
        }

        flush_func();

        /* Follow with API calls ..*/
        for (const auto& current_api_call : in_job_ptr->api_call_deque)
        {
            uint8_t*   helper_u8_ptr          =  nullptr;
            const auto helper_u8_vec_pre_size =  helper_u8_vec.size();

            helper_u8_vec.resize(helper_u8_vec_pre_size + APIInterceptor::WorkloadFormat::CALL_HEADER_N_BYTES);

            helper_u8_ptr = &helper_u8_vec.at(helper_u8_vec_pre_size);

            *reinterpret_cast<APIInterceptor::APIFunction*>(helper_u8_ptr)  = current_api_call.api_func;
             helper_u8_ptr                                                 += sizeof(APIInterceptor::APIFunction);

            *reinterpret_cast<uint32_t*>(helper_u8_ptr)  = current_api_call.n_arguments_in;
             helper_u8_ptr                              += sizeof(uint32_t);
            *reinterpret_cast<uint32_t*>(helper_u8_ptr)  = current_api_call.n_arguments_out;
             helper_u8_ptr                              += sizeof(uint32_t);
            *reinterpret_cast<uint32_t*>(helper_u8_ptr)  = current_api_call.thread_id;
             helper_u8_ptr                              += sizeof(uint32_t);

            memcpy(helper_u8_ptr,
                  &current_api_call.timestamp_qpc,
                   sizeof(uint64_t) );

            for (uint32_t n_api_call_arg = 0;
                          n_api_call_arg < current_api_call.n_arguments_in;
                        ++n_api_call_arg)
            {
                current_api_call.arguments_in[n_api_call_arg].serialize_to_u8_vec(&helper_u8_vec);
            }

            for (uint32_t n_api_call_arg = 0;
                          n_api_call_arg < current_api_call.n_arguments_out;
                        ++n_api_call_arg)
            {
                current_api_call.arguments_out[n_api_call_arg].serialize_to_u8_vec(&helper_u8_vec);
            }

            current_api_call.returned_value.serialize_to_u8_vec(&helper_u8_vec);

            flush_func();
        }

        /* ..through data chunks (a chunk which was not available is stored empty, so that chunk IDs keep matching) */
        for (const auto& current_data_chunk_u8_vec : in_job_ptr->data_chunk_vec)
        {
            const uint32_t data_chunk_size = static_cast<uint32_t>(current_data_chunk_u8_vec.size() );

            helper_u8_vec.resize(sizeof(uint32_t) );

            *reinterpret_cast<uint32_t*>(helper_u8_vec.data() ) = data_chunk_size;

            flush_func();

            if (data_chunk_size > 0)
            {
                writer_ptr->write(current_data_chunk_u8_vec.data(),
                                  data_chunk_size);
            }
        }

        /* ..finishing off with dumped surfaces, if any */
        for (const auto& current_surface : in_job_ptr->surface_vec)
        {
            helper_u8_vec.resize(sizeof(uint32_t) * N_SURFACE_HEADER_FIELDS);

            *(reinterpret_cast<uint32_t*>(helper_u8_vec.data() ) + 0) = current_surface.extents_u32vec2.at(0);
            *(reinterpret_cast<uint32_t*>(helper_u8_vec.data() ) + 1) = current_surface.extents_u32vec2.at(1);
            *(reinterpret_cast<uint32_t*>(helper_u8_vec.data() ) + 2) = static_cast<uint32_t>                (current_surface.u8_vec_ptr->size() );

            flush_func();

            writer_ptr->write(current_surface.u8_vec_ptr->data(),
                              current_surface.u8_vec_ptr->size() );
        }

        /* Ends the frame of the segment. */
        writer_ptr->finish();

        ::fflush(file_handle);
    }

    if (file_handle != nullptr)
    {
        if (in_job_ptr->should_close_file)
        {
            ::fclose(file_handle);
        }
    }
}

void APIDumper::write_workload()
{
    /* The last segment is written once, even if both the frame limit and the process exit ask for it. */
    if (m_recorded.is_workload_written == false)
    {
        m_recorded.is_workload_written = true;

        /* The writer closes the file once it is done with the last segment. */
        submit_segment(true); /* in_is_last */

        /* Nothing more will be recorded. Without callbacks, the interceptors skip capturing the arguments, too, so the
         * app keeps running without piling up data which would be thrown away.
         */
        for (uint32_t n_api_func = 0;
                      n_api_func < APIInterceptor::APIFUNCTION_COUNT;
                    ++n_api_func)
        {
            APIInterceptor::register_for_post_callback(static_cast<APIInterceptor::APIFunction>(n_api_func),
                                                       nullptr,
                                                       nullptr);
            APIInterceptor::register_for_pre_callback (static_cast<APIInterceptor::APIFunction>(n_api_func),
                                                       nullptr,
                                                       nullptr);
        }
    }
}
