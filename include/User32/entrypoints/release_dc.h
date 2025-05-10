/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_RELEASE_DC_H
#define AI_RELEASE_DC_H

#include <windows.h>

namespace User32
{
    int WINAPI release_dc(HWND in_hwnd,
                          HDC  in_hdc);
}

#endif /* AI_GET_DC_H */