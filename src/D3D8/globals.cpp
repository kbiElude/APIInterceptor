/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "D3D8/globals.h"

void* D3D8::g_cached_direct3d_create8_function_ptr = nullptr;

std::mutex D3D8::g_hook_mutex;
bool       D3D8::g_is_direct3d_create8_hooked = false;
