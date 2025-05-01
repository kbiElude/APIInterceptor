/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/globals.h"
#include "WGL/entrypoints/WGL_EXT_swap_control/wgl_get_swap_interval_ext.h"
#include "WGL/globals.h"
#include "WGL/utils_trace.h"

int WINAPI WGL::get_swap_interval_ext()
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    int                                     result                 = 0;
    bool                                    should_pass_through    = true;

    AI_TRACE("wglGetSwapIntervalEXT()\n");

    if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_WGL_WGLGETSWAPINTERVALEXT,
                                                     &pre_callback_func_ptr,
                                                     &pre_callback_func_arg) )
    {
        pre_callback_func_ptr(APIInterceptor::APIFUNCTION_WGL_WGLGETSWAPINTERVALEXT,
                              0,       /* in_n_args   */
                              nullptr, /* in_args_ptr */
                              pre_callback_func_arg,
                             &should_pass_through);
    }

    if (should_pass_through)
    {
        result = reinterpret_cast<PFNWGLGETSWAPINTERVALEXTPROC>(WGL::g_cached_get_swap_interval_ext_func_ptr)();
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_WGL_WGLGETSWAPINTERVALEXT,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        const auto result_arg = APIInterceptor::APIFunctionArgument::create_i32(result);

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_WGL_WGLGETSWAPINTERVALEXT,
                               post_callback_func_arg,
                              &result_arg);
    }

    return result;
}
