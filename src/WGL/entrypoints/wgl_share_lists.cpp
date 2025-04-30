/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/globals.h"
#include "WGL/globals.h"
#include "WGL/entrypoints/wgl_share_lists.h"

BOOL WINAPI WGL::share_lists(HGLRC in_hglrc1,
                             HGLRC in_hglrc2)
{
    void*                               callback_func_arg   = nullptr;
    APIInterceptor::PFNCALLBACKFUNCPROC callback_func_ptr   = nullptr;
    BOOL                                result              = false;
    bool                                should_pass_through = true;

    AI_TRACE("wglShareLists(in_hglrc1=[%p] in_hglrc2=[%p])",
               in_hglrc1,
               in_hglrc2);

    if (APIInterceptor::get_callback_for_function(APIInterceptor::APIFUNCTION_WGL_WGLSHARELISTS,
                                                  &callback_func_ptr,
                                                  &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_void_ptr(in_hglrc1),
            APIInterceptor::APIFunctionArgument::create_void_ptr(in_hglrc2),
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_WGL_WGLSHARELISTS,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg,
                         &should_pass_through);
    }

    if (should_pass_through)
    {
        result = reinterpret_cast<PFNWGLSHARELISTSPROC>(WGL::g_cached_share_lists_func_ptr)(in_hglrc1,
                                                                                            in_hglrc2);
    }

    return result;
}
