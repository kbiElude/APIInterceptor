/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/globals.h"
#include "WGL/globals.h"
#include "WGL/entrypoints/wgl_get_current_context.h"

HGLRC WINAPI WGL::get_current_context()
{
    void*                               callback_func_arg   = nullptr;
    APIInterceptor::PFNCALLBACKFUNCPROC callback_func_ptr   = nullptr;
    HGLRC                               result              = nullptr;
    bool                                should_pass_through = true;

    AI_TRACE("wglGetCurrentContext()");

    if (APIInterceptor::get_callback_for_function(APIInterceptor::APIFUNCTION_WGL_WGLGETCURRENTCONTEXT,
                                                  &callback_func_ptr,
                                                  &callback_func_arg) )
    {
        callback_func_ptr(APIInterceptor::APIFUNCTION_WGL_WGLGETCURRENTCONTEXT,
                          0,       /* in_n_args   */
                          nullptr, /* in_args_ptr */
                          callback_func_arg,
                         &should_pass_through);
    }

    if (should_pass_through)
    {
        result = reinterpret_cast<PFNWGLGETCURRENTCONTEXTPROC>(WGL::g_cached_get_current_context_func_ptr)();
    }

    return result;
}
