/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include <Windows.h>
#include "User32/globals.h"

void* User32::g_cached_create_window_ex_a_func_ptr = CreateWindowExA;
