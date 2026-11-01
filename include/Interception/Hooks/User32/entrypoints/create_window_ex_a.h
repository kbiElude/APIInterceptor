/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_CREATE_WINDOW_EX_A_H
#define AI_CREATE_WINDOW_EX_A_H

#include <windows.h>

namespace User32
{
    HWND WINAPI create_window_ex_a(DWORD     in_ex_style,
                                   LPCSTR    in_class_name_ptr,
                                   LPCSTR    in_window_name_ptr,
                                   DWORD     in_style,
                                   int       in_x,
                                   int       in_y,
                                   int       in_width,
                                   int       in_height,
                                   HWND      in_hwnd_parent,
                                   HMENU     in_hmenu,
                                   HINSTANCE in_hinstance,
                                   LPVOID    in_lp_param_ptr);
}

#endif /* AI_CREATE_WINDOW_EX_A_H */