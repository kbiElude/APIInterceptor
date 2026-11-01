/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/globals.h"
#include "Common/logger.h"
#include "Common/tracker.h"
#include "Interception/Hooks/WGL/entrypoints/WGL_EXT_swap_control/wgl_swap_interval_ext.h"
#include "Interception/Hooks/WGL/globals.h"
#include "Interception/Hooks/WGL/utils_trace.h"

BOOL WINAPI Interception::Hooks::WGL::swap_interval_ext(int in_interval)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    BOOL                                    result                 = false;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("wglSwapIntervalEXT(in_interval=[%d])\n",
                   in_interval);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_WGL_WGLSWAPINTERVALEXT,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_i32(in_interval),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_WGL_WGLSWAPINTERVALEXT,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    if (should_pass_through)
    {
        result = reinterpret_cast<PFNWGLSWAPINTERVALEXTPROC>(Interception::Hooks::WGL::g_cached_swap_interval_ext_func_ptr)(in_interval);
    }

    if (tracker.is_top_level_api_call() )
    {
        if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_WGL_WGLSWAPINTERVALEXT,
                                                          &post_callback_func_ptr,
                                                          &post_callback_func_arg) )
        {
            const auto result_arg = APIInterceptor::APIFunctionArgument::create_i32(result);

            post_callback_func_ptr(APIInterceptor::APIFUNCTION_WGL_WGLSWAPINTERVALEXT,
                                   post_callback_func_arg,
                                   0,       /* in_n_arguments_out   */
                               nullptr, /* in_arguments_out_ptr */
                                  &result_arg);
        }
    }

    return result;
}
