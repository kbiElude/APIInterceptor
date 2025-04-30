/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/globals.h"
#include "WGL/globals.h"
#include "WGL/entrypoints/wgl_create_context.h"

HGLRC WINAPI WGL::create_context(HDC in_hdc)
{
    void*                               callback_func_arg   = nullptr;
    APIInterceptor::PFNCALLBACKFUNCPROC callback_func_ptr   = nullptr;
    HGLRC                               result              = nullptr;
    bool                                should_pass_through = true;

    AI_TRACE("wglCreateContext(in_hdc=[%p])",
               in_hdc);

    if (APIInterceptor::get_callback_for_function(APIInterceptor::APIFUNCTION_WGL_WGLCREATECONTEXT,
                                                  &callback_func_ptr,
                                                  &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_void_ptr(in_hdc),
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_WGL_WGLCREATECONTEXT,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg,
                         &should_pass_through);
    }

    if (should_pass_through)
    {
        result = reinterpret_cast<PFNWGLCREATECONTEXTPROC>(WGL::g_cached_create_context_func_ptr)(in_hdc);
    }

    return result;
}
