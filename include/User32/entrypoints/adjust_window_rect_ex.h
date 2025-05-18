/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_ADJUST_WINDOW_RECT_EX_H
#define AI_ADJUST_WINDOW_RECT_EX_H

#include <windows.h>

namespace User32
{
    BOOL WINAPI adjust_window_rect_ex(LPRECT, DWORD, BOOL, DWORD);
}

#endif /* AI_ADJUST_WINDOW_RECT_EX_H */