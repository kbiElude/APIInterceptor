/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/globals.h"
#include "Common/logger.h"
#include "Common/tracker.h"
#include "WGL/globals.h"
#include "WGL/entrypoints/wgl_copy_context.h"

BOOL WINAPI WGL::copy_context(HGLRC in_hglrc_source,
                              HGLRC in_hglrc_destination,
                              UINT  in_mask)
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
        AI_TRACE("wglCopyContext(in_hglrc_source=[%p] in_hglrc_destination=[%p] in_mask=[%d])",
                   in_hglrc_source,
                   in_hglrc_destination,
                   in_mask);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_WGL_WGLCOPYCONTEXT,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_void_ptr(in_hglrc_source),
                APIInterceptor::APIFunctionArgument::create_void_ptr(in_hglrc_destination),
                APIInterceptor::APIFunctionArgument::create_u32     (in_mask),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_WGL_WGLCOPYCONTEXT,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    if (should_pass_through)
    {
        result = reinterpret_cast<PFNWGLCOPYCONTEXTPROC>(WGL::g_cached_copy_context_func_ptr)(in_hglrc_source,
                                                                                              in_hglrc_destination,
                                                                                              in_mask);
    }

    if (tracker.is_top_level_api_call() )
    {
        if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_WGL_WGLCOPYCONTEXT,
                                                          &post_callback_func_ptr,
                                                          &post_callback_func_arg) )
        {
            const auto result_arg = APIInterceptor::APIFunctionArgument::create_i32(result);

            post_callback_func_ptr(APIInterceptor::APIFUNCTION_WGL_WGLCOPYCONTEXT,
                                   post_callback_func_arg,
                                   0,       /* in_n_args_out   */
                               nullptr, /* in_args_out_ptr */
                                  &result_arg);
        }
    }

    return result;
}
