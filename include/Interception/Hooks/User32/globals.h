/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef USER332_GLOBALS_H
#define USER332_GLOBALS_H

#include <Windows.h>

namespace User32
{
    typedef BOOL (WINAPI *PFNADJUSTWINDOWRECTEXPROC)(LPRECT,  DWORD,   BOOL,    DWORD);
    typedef HDC  (WINAPI *PFNCREATEDCAPROC)         (LPCSTR,  LPCSTR,  LPCSTR,  const DEVMODEA*);
    typedef HDC  (WINAPI *PFNCREATEDCWPROC)         (LPCWSTR, LPCWSTR, LPCWSTR, const DEVMODEW*);
    typedef HWND (WINAPI *PFNCREATEWINDOWEXAPROC)   (DWORD,   LPCSTR,  LPCSTR,  DWORD,            int, int, int, int, HWND, HMENU, HINSTANCE, LPVOID);
    typedef HWND (WINAPI *PFNCREATEWINDOWEXWPROC)   (DWORD,   LPCWSTR, LPCWSTR, DWORD,            int, int, int, int, HWND, HMENU, HINSTANCE, LPVOID);
    typedef HDC  (WINAPI *PFNGETDCPROC)             (HWND);
    typedef int  (WINAPI *PFNRELEASEDCPROC)         (HWND, HDC);

    extern void* g_cached_adjust_window_rect_ex_func_ptr;
    extern void* g_cached_create_dc_a_func_ptr;
    extern void* g_cached_create_dc_w_func_ptr;
    extern void* g_cached_create_window_ex_a_func_ptr;
    extern void* g_cached_create_window_ex_w_func_ptr;
    extern void* g_cached_get_dc_func_ptr;
    extern void* g_cached_release_dc_func_ptr;
}

#endif /* USER32_GLOBALS_H */