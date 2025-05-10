/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include <Windows.h>
#include "User32/globals.h"

void* User32::g_cached_create_dc_a_func_ptr        = CreateDCA;
void* User32::g_cached_create_dc_w_func_ptr        = CreateDCW;
void* User32::g_cached_create_window_ex_a_func_ptr = CreateWindowExA;
void* User32::g_cached_create_window_ex_w_func_ptr = CreateWindowExW;
void* User32::g_cached_get_dc_func_ptr             = GetDC;
void* User32::g_cached_release_dc_func_ptr         = ReleaseDC;
