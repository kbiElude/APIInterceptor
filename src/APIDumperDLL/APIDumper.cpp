/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include <Windows.h>
#include "Common/callbacks.h"
#include "GL/gl.h"
#include "OpenGL/types.h"
#include "APIDumper.h"
#include <cassert>
#include <mutex>

static std::mutex g_mutex;


APIDumper::APIDumper()
    :m_dump_swapchain_on_present(false),
     m_n_frames_dumped          (0),
     m_n_frames_to_dump         (UINT32_MAX)
{
    /* Stub */
}

APIDumper::~APIDumper()
{
    /* Dump the stream.
     *
     * TODO: We should be dumping contents asynchronously every specified interval.. But this will have to do for now.
     */
    auto file_handle = ::fopen("result_dump.workload",
                               "wb");

    if (file_handle != nullptr)
    {
        const uint32_t       n_api_calls       = static_cast<uint32_t>            (m_dumped_api_call_vec.size() );
        const uint32_t       n_data_chunks     = APIInterceptor::get_n_data_chunks();
        const uint32_t       n_dumped_surfaces = static_cast<uint32_t>            (m_dumped_surface_vec.size() );
        std::vector<uint8_t> helper_u8_vec;

        /* Workload props come first.  */
        {
            helper_u8_vec.resize(sizeof(uint32_t) * 3 );

            *(reinterpret_cast<uint32_t*>(helper_u8_vec.data() ) + 0) = n_api_calls;
            *(reinterpret_cast<uint32_t*>(helper_u8_vec.data() ) + 1) = n_data_chunks;
            *(reinterpret_cast<uint32_t*>(helper_u8_vec.data() ) + 2) = n_dumped_surfaces;
        }

        /* Follow with API calls ..*/
        for (uint32_t n_api_call = 0;
                      n_api_call < n_api_calls;
                    ++n_api_call)
        {
            auto       current_api_call_ptr   = &m_dumped_api_call_vec.at(n_api_call);
            uint8_t*   helper_u8_ptr          =  nullptr;
            const auto helper_u8_vec_pre_size =  helper_u8_vec.size      ();

            helper_u8_vec.resize(helper_u8_vec_pre_size + sizeof(APIInterceptor::APIFunction) + sizeof(uint32_t) );

            helper_u8_ptr = &helper_u8_vec.at(helper_u8_vec_pre_size);

            *reinterpret_cast<APIInterceptor::APIFunction*>(helper_u8_ptr)  = current_api_call_ptr->api_func;
             helper_u8_ptr                                                 += sizeof(APIInterceptor::APIFunction);

            *reinterpret_cast<uint32_t*>(helper_u8_ptr)  = current_api_call_ptr->n_args_in;
             helper_u8_ptr                              += sizeof(uint32_t);

            for (uint32_t n_api_call_arg = 0;
                          n_api_call_arg < current_api_call_ptr->n_args_in;
                        ++n_api_call_arg)
            {
                current_api_call_ptr->args_in[n_api_call_arg].serialize_to_u8_vec(&helper_u8_vec);
            }

            current_api_call_ptr->returned_value.serialize_to_u8_vec(&helper_u8_vec);
        }

        /* ..through data chunks */
        for (uint32_t n_data_chunk = 0;
                      n_data_chunk < n_data_chunks;
                    ++n_data_chunk)
        {
            const void* data_chunk_ptr         = nullptr;
            uint32_t    data_chunk_size        = 0;
            uint8_t*    helper_u8_ptr          = nullptr;
            const auto  helper_u8_vec_pre_size = static_cast<uint32_t>(helper_u8_vec.size() );

            if (!APIInterceptor::get_data_chunk(n_data_chunk,
                                               &data_chunk_ptr,
                                               &data_chunk_size) )
            {
                assert(false);

                continue;
            }

            helper_u8_vec.resize(helper_u8_vec_pre_size + sizeof(uint32_t) + data_chunk_size);

            helper_u8_ptr = helper_u8_vec.data() + helper_u8_vec_pre_size;

            *reinterpret_cast<uint32_t*>(helper_u8_ptr)  = data_chunk_size;
            helper_u8_ptr                               += sizeof(uint32_t);

            if (data_chunk_size > 0)
            {
                memcpy(helper_u8_ptr,
                       data_chunk_ptr,
                       data_chunk_size);
            }
        }

        /* ..finishing off with dumped surfaces, if any */
        for (uint32_t n_surface = 0;
                      n_surface < n_dumped_surfaces;
                    ++n_surface)
        {
            uint8_t*   helper_u8_ptr          =  nullptr;
            const auto helper_u8_vec_pre_size =  helper_u8_vec.size     ();
            const auto surface_props_ptr      = &m_dumped_surface_vec.at(n_surface);

            helper_u8_vec.resize(helper_u8_vec_pre_size + sizeof(uint32_t) * 3 + surface_props_ptr->u8_vec_ptr->size() );

            helper_u8_ptr = helper_u8_vec.data() + helper_u8_vec_pre_size;

            *(reinterpret_cast<uint32_t*>(helper_u8_ptr) + 0) = surface_props_ptr->extents_u32vec2.at(0);
            *(reinterpret_cast<uint32_t*>(helper_u8_ptr) + 1) = surface_props_ptr->extents_u32vec2.at(1);
            *(reinterpret_cast<uint32_t*>(helper_u8_ptr) + 2) = surface_props_ptr->u8_vec_ptr->size  ();

            memcpy(helper_u8_ptr + sizeof(uint32_t) * 3,
                   surface_props_ptr->u8_vec_ptr->data(),
                   surface_props_ptr->u8_vec_ptr->size() );
        }

        ::fwrite(helper_u8_vec.data(),
                 helper_u8_vec.size(),
                 1,
                 file_handle);
        ::fclose(file_handle);
    }
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

bool APIDumper::init()
{
    bool result = false;

    /* Load settings */
    {
        uint8_t settings_data_raw_u8vec8[8] = {};
        FILE*   settings_file_handle        = ::fopen("apidumper_settings.bin",
                                                      "rb");

        if (settings_file_handle == nullptr)
        {
            assert(settings_file_handle != nullptr);

            goto end;
        }

        if (::fread(settings_data_raw_u8vec8,
                     sizeof(settings_data_raw_u8vec8),
                     1,
                     settings_file_handle) != 1)
        {
            assert(false);

            goto end;
        }

        m_n_frames_to_dump          = *reinterpret_cast<const uint32_t*>(settings_data_raw_u8vec8 + 0);
        m_dump_swapchain_on_present = *reinterpret_cast<const uint32_t*>(settings_data_raw_u8vec8 + 4) != 0;

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

    result = true;
end:
    return result;
}

void APIDumper::on_post_callback(APIInterceptor::APIFunction                in_api_func,
                                 void*                                      in_user_arg_ptr,
                                 const APIInterceptor::APIFunctionArgument* in_returned_value_ptr)
{
    std::lock_guard<std::mutex> guard(g_mutex);

    DumpedAPICall* api_call_item_ptr = nullptr;
    APIDumper*     this_ptr          = reinterpret_cast<APIDumper*>(in_user_arg_ptr);

    /* Ignore this callback if we've already dumped sufficient number of frames! */
    if (this_ptr->m_n_frames_dumped < this_ptr->m_n_frames_to_dump)
    {
        /* Update the last cached API call's returned value.
         *
         * In cases where OS DLL implementing the API function calls intercepted API functions, the relevant vec item
         * may be a few items back.
         *
         * NOTE: This will totally break for multi-context apps!
         */
        assert(this_ptr->m_dumped_api_call_vec.size() > 0);

        api_call_item_ptr = &this_ptr->m_dumped_api_call_vec.back();

        if (this_ptr->m_dumped_api_call_vec.back().api_func != in_api_func)
        {
            const auto this_thread_id = std::this_thread::get_id();

            auto vec_iterator = std::find_if(this_ptr->m_dumped_api_call_vec.rbegin(),
                                             this_ptr->m_dumped_api_call_vec.rend  (),
                                             [&](const DumpedAPICall& in_api_call)
                                             {
                                                return (in_api_call.api_func  == in_api_func)    &&
                                                       (in_api_call.thread_id == this_thread_id);
                                             });

            assert(vec_iterator != this_ptr->m_dumped_api_call_vec.rend() );
            if (vec_iterator != this_ptr->m_dumped_api_call_vec.rend() )
            {
                api_call_item_ptr = &(*vec_iterator);
            }
            else
            {
                api_call_item_ptr = nullptr;
            }
        }

        assert(api_call_item_ptr != nullptr);
        if (api_call_item_ptr != nullptr)
        {
            api_call_item_ptr->returned_value = *in_returned_value_ptr;
        }
    }

    /* If this is a frame present call, increment internal counter.
     *
     * TODO: This will break down badly for apps that do NOT use back buffer..
     */
    if (in_api_func == APIInterceptor::APIFUNCTION_GDI32_SWAPBUFFERS)
    {
        this_ptr->m_n_frames_dumped++;
    }
}

void APIDumper::on_pre_callback(APIInterceptor::APIFunction                in_api_func,
                                uint32_t                                   in_n_args_in,
                                const APIInterceptor::APIFunctionArgument* in_args_in_ptr,
                                void*                                      in_user_arg_ptr,
                                bool*                                      out_should_pass_through_ptr)
{
    std::lock_guard<std::mutex> guard   (g_mutex);
    APIDumper*                  this_ptr(reinterpret_cast<APIDumper*>(in_user_arg_ptr) );

    assert(sizeof(DumpedAPICall::args_in) / sizeof(DumpedAPICall::args_in[0]) >= in_n_args_in);

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
            DumpedSurface new_surface;

            new_surface.extents_u32vec2 = swapchain_extents_u32vec2;
            new_surface.u8_vec_ptr      = std::move(swapchain_data_u8_vec_ptr);

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

            this_ptr->m_dumped_api_call_vec.emplace_back(new_item);
        }
    }

    /* Always pass through any of the intercepted calls */
    *out_should_pass_through_ptr = true;
}