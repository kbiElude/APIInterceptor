/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/globals.h"
#include "WGL/entrypoints/WGL_EXT_swap_control/wgl_swap_interval_ext.h"
#include "WGL/globals.h"
#include "WGL/utils_trace.h"

BOOL WINAPI WGL::swap_interval_ext(int in_interval)
{
    void*                               callback_func_arg   = nullptr;
    APIInterceptor::PFNCALLBACKFUNCPROC callback_func_ptr   = nullptr;
    BOOL                                result              = false;
    bool                                should_pass_through = true;

    AI_TRACE("wglSwapIntervalEXT(in_interval=[%d])\n",
               in_interval);

    if (APIInterceptor::get_callback_for_function(APIInterceptor::APIFUNCTION_WGL_WGLSWAPINTERVALEXT,
                                                  &callback_func_ptr,
                                                  &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_i32(in_interval),
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_WGL_WGLSWAPINTERVALEXT,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg,
                         &should_pass_through);
    }

    if (should_pass_through)
    {
        result = reinterpret_cast<PFNWGLSWAPINTERVALEXTPROC>(WGL::g_cached_swap_interval_ext_func_ptr)(in_interval);
    }

    return result;
}
