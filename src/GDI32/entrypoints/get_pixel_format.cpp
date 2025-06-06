/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/globals.h"
#include "Common/logger.h"
#include "Common/tracker.h"
#include "GDI32/entrypoints/get_pixel_format.h"
#include "GDI32/globals.h"

int WINAPI GDI32::get_pixel_format(HDC in_hdc)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    int                                     result                 = 0;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    AI_TRACE("GetPixelFormat(in_hdc=[%p])",
             in_hdc);

    if (tracker.is_top_level_api_call() )
    {
        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GDI32_GETPIXELFORMAT,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_void_ptr(in_hdc),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GDI32_GETPIXELFORMAT,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    if (should_pass_through)
    {
        result = reinterpret_cast<GDI32::PFNGETPIXELFORMATPROC>(GDI32::g_cached_get_pixel_format_func_ptr)(in_hdc);
    }

    if (tracker.is_top_level_api_call() )
    {
        if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GDI32_GETPIXELFORMAT,
                                                          &post_callback_func_ptr,
                                                          &post_callback_func_arg) )
        {
            const auto result_arg = APIInterceptor::APIFunctionArgument::create_i32(result);

            post_callback_func_ptr(APIInterceptor::APIFUNCTION_GDI32_GETPIXELFORMAT,
                                   post_callback_func_arg,
                                   0,       /* in_n_args_out   */
                                   nullptr, /* in_args_out_ptr */
                                  &result_arg);
        }
    }

    return result;
}