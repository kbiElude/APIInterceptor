/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include <Windows.h>
#include "interception/hooks/User32/globals.h"

void* Interception::Hooks::User32::g_cached_adjust_window_rect_ex_func_ptr = AdjustWindowRectEx;
void* Interception::Hooks::User32::g_cached_create_dc_a_func_ptr           = CreateDCA;
void* Interception::Hooks::User32::g_cached_create_dc_w_func_ptr           = CreateDCW;
void* Interception::Hooks::User32::g_cached_create_window_ex_a_func_ptr    = CreateWindowExA;
void* Interception::Hooks::User32::g_cached_create_window_ex_w_func_ptr    = CreateWindowExW;
void* Interception::Hooks::User32::g_cached_get_dc_func_ptr                = GetDC;
void* Interception::Hooks::User32::g_cached_release_dc_func_ptr            = ReleaseDC;
