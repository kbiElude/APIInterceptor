/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/globals.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "GDI32/globals.h"
#include "GDI32/entrypoints/choose_pixel_format.h"
#include "GDI32/utils_trace.h"

int WINAPI GDI32::choose_pixel_format(HDC                          in_hdc,
                                      CONST PIXELFORMATDESCRIPTOR* in_pixel_format_descriptor_ptr)
{
    void*                                   post_callback_func_arg  = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr  = nullptr;
    void*                                   pre_callback_func_arg   = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr   = nullptr;
    int                                     result                  = 0;
    bool                                    should_pass_through     = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("ChoosePixelFormat(\n"
                 " in_hdc                         = [%p]\n"
                 " in_pixel_format_descriptor_ptr = %s)",
                 in_hdc,
                 GDI32::convert_pixel_format_descriptor_to_raw_string(in_pixel_format_descriptor_ptr) );

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GDI32_CHOOSEPIXELFORMAT,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const auto pfd_data_chunk_id = APIInterceptor::register_data_chunk(in_pixel_format_descriptor_ptr,
                                                                               sizeof(*in_pixel_format_descriptor_ptr) );

            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_void_ptr     (in_hdc),
                APIInterceptor::APIFunctionArgument::create_data_chunk_id(pfd_data_chunk_id),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GDI32_CHOOSEPIXELFORMAT,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    if (should_pass_through)
    {
        result = reinterpret_cast<GDI32::PFNCHOOSEPIXELFORMATPROC>(GDI32::g_cached_choose_pixel_format_func_ptr)(in_hdc,
                                                                                                                 in_pixel_format_descriptor_ptr);
    }

    if (tracker.is_top_level_api_call() )
    {
        if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GDI32_CHOOSEPIXELFORMAT,
                                                          &post_callback_func_ptr,
                                                          &post_callback_func_arg) )
        {
            const auto result_arg = APIInterceptor::APIFunctionArgument::create_i32(result);

            post_callback_func_ptr(APIInterceptor::APIFUNCTION_GDI32_CHOOSEPIXELFORMAT,
                                   post_callback_func_arg,
                                  &result_arg);
        }
    }

    return result;
}
