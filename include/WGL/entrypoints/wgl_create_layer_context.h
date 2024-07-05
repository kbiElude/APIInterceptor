/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef WGL_CREATE_LAYER_CONTEXT_H
#define WGL_CREATE_LAYER_CONTEXT_H

#include <windows.h>

namespace WGL
{
    HGLRC WINAPI create_layer_context(HDC in_hdc,
                                      int in_layer_plane_index);
}

#endif /* WGL_CREATE_LAYER_CONTEXT_H */