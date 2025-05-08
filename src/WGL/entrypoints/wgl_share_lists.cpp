/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/globals.h"
#include "Common/logger.h"
#include "Common/tracker.h"
#include "WGL/globals.h"
#include "WGL/entrypoints/wgl_share_lists.h"

BOOL WINAPI WGL::share_lists(HGLRC in_hglrc1,
                             HGLRC in_hglrc2)
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
        AI_TRACE("wglShareLists(in_hglrc1=[%p] in_hglrc2=[%p])",
                   in_hglrc1,
                   in_hglrc2);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_WGL_WGLSHARELISTS,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_void_ptr(in_hglrc1),
                APIInterceptor::APIFunctionArgument::create_void_ptr(in_hglrc2),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_WGL_WGLSHARELISTS,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    if (should_pass_through)
    {
        result = reinterpret_cast<PFNWGLSHARELISTSPROC>(WGL::g_cached_share_lists_func_ptr)(in_hglrc1,
                                                                                            in_hglrc2);
    }

    if (tracker.is_top_level_api_call() )
    {
        if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_WGL_WGLSHARELISTS,
                                                          &post_callback_func_ptr,
                                                          &post_callback_func_arg) )
        {
            const auto result_arg = APIInterceptor::APIFunctionArgument::create_i32(result);

            post_callback_func_ptr(APIInterceptor::APIFUNCTION_WGL_WGLSHARELISTS,
                                   post_callback_func_arg,
                                  &result_arg);
        }
    }

    return result;
}
