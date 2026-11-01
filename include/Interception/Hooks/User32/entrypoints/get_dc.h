/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GET_DC_H
#define AI_GET_DC_H

#include <windows.h>

namespace User32
{
    HDC WINAPI get_dc(HWND in_hwnd);
}

#endif /* AI_GET_DC_H */