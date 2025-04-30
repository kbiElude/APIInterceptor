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
    void*                               callback_func_arg   = nullptr;
    APIInterceptor::PFNCALLBACKFUNCPROC callback_func_ptr   = nullptr;
    int                                 result              = 0;
    bool                                should_pass_through = true;

    AI_TRACE("wglGetSwapIntervalEXT()\n");

    if (APIInterceptor::get_callback_for_function(APIInterceptor::APIFUNCTION_WGL_WGLGETSWAPINTERVALEXT,
                                                  &callback_func_ptr,
                                                  &callback_func_arg) )
    {
        callback_func_ptr(APIInterceptor::APIFUNCTION_WGL_WGLGETSWAPINTERVALEXT,
                          0,       /* in_n_args   */
                          nullptr, /* in_args_ptr */
                          callback_func_arg,
                         &should_pass_through);
    }

    if (should_pass_through)
    {
        result = reinterpret_cast<PFNWGLGETSWAPINTERVALEXTPROC>(WGL::g_cached_get_swap_interval_ext_func_ptr)();
    }

    return result;
}
