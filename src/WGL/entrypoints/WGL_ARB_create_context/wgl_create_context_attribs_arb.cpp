/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/globals.h"
#include "WGL/entrypoints/WGL_ARB_create_context/wgl_create_context_attribs_arb.h"
#include "WGL/globals.h"
#include "WGL/utils_trace.h"

HGLRC WINAPI WGL::create_context_attribs_arb(HDC        in_hdc,
                                             HGLRC      in_share_context_handle,
                                             const int* in_attrib_list_ptr)
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

    return reinterpret_cast<PFNWGLCREATECONTEXTATTRIBSARBPROC>(WGL::g_cached_create_context_attribs_arb_func_ptr)(in_hdc,
                                                                                                                  in_share_context_handle,
                                                                                                                  in_attrib_list_ptr);
}
