/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include <Windows.h>
#include "Common/callbacks.h"
#include "GL/gl.h"
#include "Kernel32/callbacks.h"
#include "OpenGL/types.h"
#include "APIDumper.h"
#include "d3d8_swapchain_reader.h"
#include <algorithm>
#include <cassert>
#include <mutex>

static std::mutex g_mutex;

/* Used by the constructor's initializer list. */
static constexpr uint64_t DEFAULT_N_BYTES_BEFORE_SPILL = 128ull * 1024 * 1024;

APIDumper::APIDumper()
    :m_chunk_scan_cursor        (0),
     m_dump_swapchain_on_present(false),
     m_is_workload_written      (false),
     m_n_bytes_before_spill     (DEFAULT_N_BYTES_BEFORE_SPILL),
     m_n_chunk_bytes_counted    (0),
     m_n_data_chunks_written    (0),
     m_n_frames_dumped          (0),
     m_n_frames_to_dump         (UINT32_MAX),
     m_n_surface_bytes          (0),
     m_workload_file_handle     (nullptr)
{
    /* Stub */
}

APIDumper::~APIDumper()
{
    write_workload();
    wait_for_writer();
}

APIDumperUniquePtr APIDumper::create()
{
    APIDumperUniquePtr result_ptr(new APIDumper() );

    if (result_ptr != nullptr)
    {
        if (!result_ptr->init() )
        {
            result_ptr.reset();
        }
    }

    return result_ptr;
}

uint64_t APIDumper::get_n_unwritten_bytes()
{
    const uint32_t n_data_chunks = APIInterceptor::get_n_data_chunks();

    /* Data chunks are counted once, as they show up. */
    for (;
         m_chunk_scan_cursor < n_data_chunks;
         m_chunk_scan_cursor++)
    {
        const void* data_chunk_ptr  = nullptr;
        uint32_t    data_chunk_size = 0;

        if (APIInterceptor::get_data_chunk(m_chunk_scan_cursor,
                                          &data_chunk_ptr,
                                          &data_chunk_size) )
        {
            m_n_chunk_bytes_counted += data_chunk_size;
        }
    }

    return m_dumped_api_call_deque.size() * sizeof(DumpedAPICall) + m_n_chunk_bytes_counted + m_n_surface_bytes;
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

        m_n_frames_to_dump          = *reinterpret_cast<const uint32_t*>(settings_data_raw_u8vec12 + 0 * sizeof(uint32_t) );
        m_dump_swapchain_on_present = *reinterpret_cast<const uint32_t*>(settings_data_raw_u8vec12 + 1 * sizeof(uint32_t) ) != 0;
        m_n_bytes_before_spill      = static_cast<uint64_t>(*reinterpret_cast<const uint32_t*>(settings_data_raw_u8vec12 + 2 * sizeof(uint32_t) ) ) * N_BYTES_PER_MB;

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
    m_workload_file_handle = ::fopen("result_dump.workload",
                                     "wb");

    if (m_workload_file_handle == nullptr)
    {
        assert(m_workload_file_handle != nullptr);

        goto end;
    }

    /* The writer thread would not survive the process being taken down, so the app's exit gives it time to finish. */
    Kernel32::register_for_process_exiting_callback(on_process_exiting,
                                                    this);

    result = true;
end:
    return result;
}

void APIDumper::on_post_callback(APIInterceptor::APIFunction                in_api_func,
                                 void*                                      in_user_arg_ptr,
                                 uint32_t                                   in_n_args_out,
                                 const APIInterceptor::APIFunctionArgument* in_args_out_ptr,
                                 const APIInterceptor::APIFunctionArgument* in_returned_value_ptr)
{
    {
        std::lock_guard<std::mutex> guard(g_mutex);

        DumpedAPICall* api_call_item_ptr = nullptr;
        APIDumper*     this_ptr          = reinterpret_cast<APIDumper*>(in_user_arg_ptr);

        /* Ignore this callback if we've already dumped sufficient number of frames! */
        if (this_ptr->m_n_frames_dumped < this_ptr->m_n_frames_to_dump)
        {
            /* Update the last cached API call's returned value.
             *
             * In cases where OS DLL implementing the API function calls intercepted API functions, the relevant item
             * may be a few items back.
             *
             * NOTE: This will totally break for multi-context apps!
             */
            assert(this_ptr->m_dumped_api_call_deque.size() > 0);

            api_call_item_ptr = &this_ptr->m_dumped_api_call_deque.back();

            if (this_ptr->m_dumped_api_call_deque.back().api_func != in_api_func)
            {
                const auto this_thread_id = std::this_thread::get_id();

                auto deque_iterator = std::find_if(this_ptr->m_dumped_api_call_deque.rbegin(),
                                                   this_ptr->m_dumped_api_call_deque.rend  (),
                                                   [&](const DumpedAPICall& in_api_call)
                                                   {
                                                      return (in_api_call.api_func  == in_api_func)    &&
                                                             (in_api_call.thread_id == this_thread_id);
                                                   });

                assert(deque_iterator != this_ptr->m_dumped_api_call_deque.rend() );
                if (deque_iterator != this_ptr->m_dumped_api_call_deque.rend() )
                {
                    api_call_item_ptr = &(*deque_iterator);
                }
                else
                {
                    api_call_item_ptr = nullptr;
                }
            }

            assert(api_call_item_ptr != nullptr);
            if (api_call_item_ptr != nullptr)
            {
                api_call_item_ptr->n_args_out     =  in_n_args_out;
                api_call_item_ptr->returned_value = *in_returned_value_ptr;

                for (uint32_t n_arg = 0;
                              n_arg < in_n_args_out;
                            ++n_arg)
                {
                    api_call_item_ptr->args_out[n_arg] = in_args_out_ptr[n_arg];
                }
            }
        }

        /* If this is a frame present call, increment internal counter.
         *
         * TODO: This will break down badly for apps that do NOT use back buffer..
         */
        if (in_api_func == APIInterceptor::APIFUNCTION_GDI32_SWAPBUFFERS           ||
            in_api_func == APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_PRESENT)
        {
            this_ptr->m_n_frames_dumped++;

            /* Frame boundaries are the one place where no call is half-recorded. */
            if (this_ptr->get_n_unwritten_bytes() >= this_ptr->m_n_bytes_before_spill)
            {
                this_ptr->submit_segment(false); /* in_is_last */
            }

            /* The dump is complete: write it now, so the process need not exit gracefully. */
            if (this_ptr->m_n_frames_dumped >= this_ptr->m_n_frames_to_dump)
            {
                this_ptr->write_workload();
            }
        }
    }
}

void APIDumper::on_pre_callback(APIInterceptor::APIFunction                in_api_func,
                                uint32_t                                   in_n_args_in,
                                const APIInterceptor::APIFunctionArgument* in_args_in_ptr,
                                void*                                      in_user_arg_ptr,
                                bool*                                      out_should_pass_through_ptr)
{
    APIDumper* this_ptr(reinterpret_cast<APIDumper*>(in_user_arg_ptr) );

    assert(sizeof(DumpedAPICall::args_in) / sizeof(DumpedAPICall::args_in[0]) >= in_n_args_in);

    if (in_api_func                 == APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_PRESENT &&
        this_ptr->m_n_frames_dumped <  this_ptr->m_n_frames_to_dump                              &&
        this_ptr->m_dump_swapchain_on_present)
    {
        DumpedSurface new_surface;
        auto          rgba_u8_vec_ptr = std::unique_ptr<std::vector<uint8_t> >(new std::vector<uint8_t>() );

        /* The device is the first argument of the call. */
        if (APIDumperDLL::D3D8SwapchainReader::read(const_cast<void*>(in_args_in_ptr[0].get_ptr() ),
                                                   &new_surface.extents_u32vec2,
                                                    rgba_u8_vec_ptr.get() ))
        {
            new_surface.u8_vec_ptr = std::move(rgba_u8_vec_ptr);

            {
                std::lock_guard<std::mutex> guard(g_mutex);

                this_ptr->m_n_surface_bytes += new_surface.u8_vec_ptr->size();

                this_ptr->m_dumped_surface_vec.emplace_back(std::move(new_surface) );
            }
        }
    }

    if (in_api_func                           == APIInterceptor::APIFUNCTION_GDI32_SWAPBUFFERS &&
        this_ptr->m_n_frames_dumped           <  this_ptr->m_n_frames_to_dump                  &&
        this_ptr->m_dump_swapchain_on_present)
    {
        std::unique_ptr<std::vector<uint8_t> > swapchain_data_u8_vec_ptr;
        std::array<uint32_t, 2>                swapchain_extents_u32vec2 = {640, 480};
        RECT                                   window_client_rect        = {};
        const auto                             window_handle             = ::WindowFromDC(reinterpret_cast<HDC>(const_cast<void*>(in_args_in_ptr[0].get_ptr() )));

        ::GetClientRect(window_handle,
                       &window_client_rect);

        swapchain_extents_u32vec2[0] = window_client_rect.right  - window_client_rect.left;
        swapchain_extents_u32vec2[1] = window_client_rect.bottom - window_client_rect.top;

        swapchain_data_u8_vec_ptr.reset(
            new std::vector<uint8_t>(swapchain_extents_u32vec2[0] * swapchain_extents_u32vec2[1] * 4 /* rgba8_unorm */)
        );

        /* Read color buffer */
        ::glReadPixels(0, /* x */
                       0, /* y */
                       swapchain_extents_u32vec2[0],
                       swapchain_extents_u32vec2[1],
                       GL_RGBA,
                       GL_UNSIGNED_BYTE,
                       swapchain_data_u8_vec_ptr->data() );
        ::glFinish    ();

        /* Store for later use */
        {
            std::lock_guard<std::mutex> guard      (g_mutex);
            DumpedSurface               new_surface;

            new_surface.extents_u32vec2 = swapchain_extents_u32vec2;
            new_surface.u8_vec_ptr      = std::move(swapchain_data_u8_vec_ptr);

            this_ptr->m_n_surface_bytes += new_surface.u8_vec_ptr->size();

            this_ptr->m_dumped_surface_vec.emplace_back(
                std::move(new_surface)
            );
        }
    }

    /* Do NOT dump the API call if we've already dumped sufficient number of frames! */
    if (this_ptr->m_n_frames_dumped < this_ptr->m_n_frames_to_dump)
    {
        /* Cache API call's properties.
         *
         * TODO: This code totally ignores the fact that pointers passed to API calls may go out of scope
         *       as soon as the API call is handled. This works fine for Q1 but will fail massively for
         *       any more complex workload!
         */
        {
            DumpedAPICall new_item;

            new_item.api_func  = in_api_func;
            new_item.n_args_in = in_n_args_in;
            new_item.thread_id = std::this_thread::get_id();

            for (uint32_t n_arg = 0;
                          n_arg < in_n_args_in;
                        ++n_arg)
            {
                new_item.args_in[n_arg] = in_args_in_ptr[n_arg];
            }

            {
                std::lock_guard<std::mutex> guard(g_mutex);

                this_ptr->m_dumped_api_call_deque.emplace_back(new_item);
            }
        }
    }

    /* Always pass through any of the intercepted calls */
    *out_should_pass_through_ptr = true;
}

void APIDumper::on_process_exiting(void* in_user_arg_ptr)
{
    APIDumper* this_ptr = reinterpret_cast<APIDumper*>(in_user_arg_ptr);

    /* The process is about to be taken down, and a running writer thread with it. Hand over what is left, and wait. */
    {
        std::lock_guard<std::mutex> guard(g_mutex);

        this_ptr->write_workload();
    }

    this_ptr->wait_for_writer();
}

void APIDumper::submit_segment(const bool& in_is_last)
{
    SegmentJobUniquePtr job_ptr(new SegmentJob() );

    /* Blocks only if the writer is still busy with the previous segment. */
    wait_for_writer();

    {
        const uint32_t first_data_chunk = m_n_data_chunks_written;
        const uint32_t n_data_chunks    = APIInterceptor::get_n_data_chunks() - first_data_chunk;

        /* The render thread only moves the data around; serializing and writing it is up to the writer. */
        job_ptr->api_call_deque.swap(m_dumped_api_call_deque);
        job_ptr->file_handle       = m_workload_file_handle;
        job_ptr->should_close_file = in_is_last;
        job_ptr->surface_vec.swap(m_dumped_surface_vec);

        APIInterceptor::take_data_chunks(first_data_chunk,
                                         n_data_chunks,
                                        &job_ptr->data_chunk_vec);

        m_chunk_scan_cursor     = first_data_chunk + n_data_chunks;
        m_n_chunk_bytes_counted = 0;
        m_n_data_chunks_written = first_data_chunk + n_data_chunks;
        m_n_surface_bytes       = 0;
    }

    /* The writer owns the file from now on. */
    if (in_is_last)
    {
        m_workload_file_handle = nullptr;
    }

    m_writer_thread = std::thread(&APIDumper::write_segment,
                                  std::move(job_ptr) );
}

void APIDumper::wait_for_writer()
{
    if (m_writer_thread.joinable() )
    {
        m_writer_thread.join();
    }
}

void APIDumper::write_segment(SegmentJobUniquePtr in_job_ptr)
{
    constexpr size_t N_SEGMENT_COUNTS        = 3; /* API calls, data chunks, surfaces */
    constexpr size_t N_SURFACE_HEADER_FIELDS = 3; /* width, height, n bytes */

    FILE* const file_handle = in_job_ptr->file_handle;

    /* The writer must not disturb the app, nor be recorded. */
    ::SetThreadPriority(::GetCurrentThread(),
                        THREAD_PRIORITY_BELOW_NORMAL);

    APIInterceptor::disable_callbacks_for_this_thread();

    if (file_handle != nullptr)
    {
        const uint32_t       n_api_calls       = static_cast<uint32_t>(in_job_ptr->api_call_deque.size() );
        const uint32_t       n_data_chunks     = static_cast<uint32_t>(in_job_ptr->data_chunk_vec.size() );
        const uint32_t       n_dumped_surfaces = static_cast<uint32_t>(in_job_ptr->surface_vec.size() );
        std::vector<uint8_t> helper_u8_vec;

        /* Items are written out as they are put together, so that a big segment need not exist in memory twice. */
        const auto flush_func = [&]()
        {
            if (helper_u8_vec.empty() == false)
            {
                ::fwrite(helper_u8_vec.data(),
                         helper_u8_vec.size(),
                         1,
                         file_handle);

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

            helper_u8_vec.resize(helper_u8_vec_pre_size + sizeof(APIInterceptor::APIFunction) + sizeof(uint32_t) * 2);

            helper_u8_ptr = &helper_u8_vec.at(helper_u8_vec_pre_size);

            *reinterpret_cast<APIInterceptor::APIFunction*>(helper_u8_ptr)  = current_api_call.api_func;
             helper_u8_ptr                                                 += sizeof(APIInterceptor::APIFunction);

            *reinterpret_cast<uint32_t*>(helper_u8_ptr)  = current_api_call.n_args_in;
             helper_u8_ptr                              += sizeof(uint32_t);
            *reinterpret_cast<uint32_t*>(helper_u8_ptr)  = current_api_call.n_args_out;
             helper_u8_ptr                              += sizeof(uint32_t);

            for (uint32_t n_api_call_arg = 0;
                          n_api_call_arg < current_api_call.n_args_in;
                        ++n_api_call_arg)
            {
                current_api_call.args_in[n_api_call_arg].serialize_to_u8_vec(&helper_u8_vec);
            }

            for (uint32_t n_api_call_arg = 0;
                          n_api_call_arg < current_api_call.n_args_out;
                        ++n_api_call_arg)
            {
                current_api_call.args_out[n_api_call_arg].serialize_to_u8_vec(&helper_u8_vec);
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
                ::fwrite(current_data_chunk_u8_vec.data(),
                         data_chunk_size,
                         1,
                         file_handle);
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

            ::fwrite(current_surface.u8_vec_ptr->data(),
                     current_surface.u8_vec_ptr->size(),
                     1,
                     file_handle);
        }

        ::fflush(file_handle);

        if (in_job_ptr->should_close_file)
        {
            ::fclose(file_handle);
        }
    }
}

void APIDumper::write_workload()
{
    /* The last segment is written once, even if both the frame limit and the process exit ask for it. */
    if (m_is_workload_written == false)
    {
        m_is_workload_written = true;

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
