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
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    HGLRC                                   result                 = nullptr;
    bool                                    should_pass_through    = true;

    AI_TRACE("wglCreateContext(in_hdc=[%p])",
               in_hdc);

    if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_WGL_WGLCREATECONTEXT,
                                                     &pre_callback_func_ptr,
                                                     &pre_callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_void_ptr(in_hdc),
        };

        pre_callback_func_ptr(APIInterceptor::APIFUNCTION_WGL_WGLCREATECONTEXT,
                              sizeof(args) / sizeof(args[0]),
                              args,
                              pre_callback_func_arg,
                             &should_pass_through);
    }

    if (should_pass_through)
    {
        result = reinterpret_cast<PFNWGLCREATECONTEXTPROC>(WGL::g_cached_create_context_func_ptr)(in_hdc);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_WGL_WGLCREATECONTEXT,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        const auto result_arg = APIInterceptor::APIFunctionArgument::create_void_ptr(result);

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_WGL_WGLCREATECONTEXT,
                               post_callback_func_arg,
                              &result_arg);
    }

    return result;
}
