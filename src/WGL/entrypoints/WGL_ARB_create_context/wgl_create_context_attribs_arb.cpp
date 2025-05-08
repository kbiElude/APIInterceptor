/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/globals.h"
#include "Common/logger.h"
#include "Common/tracker.h"
#include "WGL/entrypoints/WGL_ARB_create_context/wgl_create_context_attribs_arb.h"
#include "WGL/globals.h"
#include "WGL/utils_trace.h"

HGLRC WINAPI WGL::create_context_attribs_arb(HDC        in_hdc,
                                             HGLRC      in_share_context_handle,
                                             const int* in_attrib_list_ptr)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    HGLRC                                   result                 = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("wglCreateContextAttribsARB(\n"
                   " in_hdc                  = [%p]\n"
                   " in_share_context_handle = [%p]\n"
                   " in_attrib_list_ptr      = %s)",
                   in_hdc,
                   in_share_context_handle,
                   WGL::convert_context_attrib_list_to_raw_string(in_attrib_list_ptr) );

        if (WGL::g_cached_create_context_attribs_arb_func_ptr == nullptr)
        {
            WGL::g_cached_create_context_attribs_arb_func_ptr = reinterpret_cast<PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("wglCreateContextAttribsARB");

            AI_ASSERT(WGL::g_cached_create_context_attribs_arb_func_ptr != nullptr);
        }

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_WGL_WGLCREATECONTEXTATTRIBSARB,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_void_ptr(in_hdc),
                APIInterceptor::APIFunctionArgument::create_void_ptr(in_share_context_handle),
                APIInterceptor::APIFunctionArgument::create_void_ptr(in_attrib_list_ptr),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_WGL_WGLCREATECONTEXTATTRIBSARB,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    if (should_pass_through)
    {
        result = reinterpret_cast<PFNWGLCREATECONTEXTATTRIBSARBPROC>(WGL::g_cached_create_context_attribs_arb_func_ptr)(in_hdc,
                                                                                                                        in_share_context_handle,
                                                                                                                        in_attrib_list_ptr);
    }

    if (tracker.is_top_level_api_call() )
    {
        if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_WGL_WGLCREATECONTEXTATTRIBSARB,
                                                          &post_callback_func_ptr,
                                                          &post_callback_func_arg) )
        {
            const auto result_arg = APIInterceptor::APIFunctionArgument::create_void_ptr(result);

            post_callback_func_ptr(APIInterceptor::APIFUNCTION_WGL_WGLCREATECONTEXTATTRIBSARB,
                                   post_callback_func_arg,
                                  &result_arg);
        }
    }

    return result;
}
