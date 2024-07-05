/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef WGL_GET_CURRENT_DC_H
#define WGL_GET_CURRENT_DC_H

#include <windows.h>

namespace WGL
{
    HDC WINAPI get_current_dc();
}

#endif /* WGL_GET_CURRENT_DC_H */