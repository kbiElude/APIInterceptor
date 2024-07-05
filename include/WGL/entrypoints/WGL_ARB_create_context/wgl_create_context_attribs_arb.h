/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef WGL_CREATE_CONTEXT_ATTRIBS_ARB_H
#define WGL_CREATE_CONTEXT_ATTRIBS_ARB_H

#include <windows.h>

namespace WGL
{
    HGLRC WINAPI create_context_attribs_arb(HDC        in_hdc,
                                            HGLRC      in_share_context_handle,
                                            const int* in_attrib_list_ptr);
}

#endif /* WGL_CREATE_CONTEXT_ATTRIBS_ARB_H */