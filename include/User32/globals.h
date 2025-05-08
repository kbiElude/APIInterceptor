/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef USER332_GLOBALS_H
#define USER332_GLOBALS_H

#include <Windows.h>

namespace User32
{
    typedef HWND (WINAPI *PFNCREATEWINDOWEXAPROC) (DWORD, LPCSTR, LPCSTR, DWORD, int, int, int, int, HWND, HMENU, HINSTANCE, LPVOID);

    extern void* g_cached_create_window_ex_a_func_ptr;
}

#endif /* USER32_GLOBALS_H */