/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/globals.h"
#include "WGL/globals.h"
#include "WGL/entrypoints/wgl_make_current.h"

BOOL WINAPI WGL::make_current(HDC   in_hdc,
                              HGLRC in_hglrc)
{
    void*                               callback_func_arg = nullptr;
    APIInterceptor::PFNCALLBACKFUNCPROC callback_func_ptr = nullptr;

    AI_TRACE("wglMakeCurrent(in_hdc=[%p] in_hglrc=[%p])",
               in_hdc,
               in_hglrc);

    if (APIInterceptor::get_callback_for_function(APIInterceptor::APIFUNCTION_WGL_WGLMAKECURRENT,
                                                 &callback_func_ptr,
                                                 &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_void_ptr(in_hdc),
            APIInterceptor::APIFunctionArgument::create_void_ptr(in_hglrc),
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_WGL_WGLMAKECURRENT,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg);
    }


    return reinterpret_cast<PFNWGLMAKECURRENTPROC>(WGL::g_cached_make_current_func_ptr)(in_hdc,
                                                                                        in_hglrc);
}
