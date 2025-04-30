/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/globals.h"
#include "WGL/entrypoints/WGL_ARB_create_context/wgl_create_context_attribs_arb.h"
#include "WGL/globals.h"
#include "WGL/utils_trace.h"

HGLRC WINAPI WGL::create_context_attribs_arb(HDC        in_hdc,
                                             HGLRC      in_share_context_handle,
                                             const int* in_attrib_list_ptr)
{
    void*                               callback_func_arg   = nullptr;
    APIInterceptor::PFNCALLBACKFUNCPROC callback_func_ptr   = nullptr;
    HGLRC                               result              = nullptr;
    bool                                should_pass_through = true;

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

    if (APIInterceptor::get_callback_for_function(APIInterceptor::APIFUNCTION_WGL_WGLCREATECONTEXTATTRIBSARB,
                                                  &callback_func_ptr,
                                                  &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_void_ptr(in_hdc),
            APIInterceptor::APIFunctionArgument::create_void_ptr(in_share_context_handle),
            APIInterceptor::APIFunctionArgument::create_void_ptr(in_attrib_list_ptr),
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_WGL_WGLCREATECONTEXTATTRIBSARB,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg,
                         &should_pass_through);
    }

    if (should_pass_through)
    {
        result = reinterpret_cast<PFNWGLCREATECONTEXTATTRIBSARBPROC>(WGL::g_cached_create_context_attribs_arb_func_ptr)(in_hdc,
                                                                                                                        in_share_context_handle,
                                                                                                                        in_attrib_list_ptr);
    }

    return result;
}
