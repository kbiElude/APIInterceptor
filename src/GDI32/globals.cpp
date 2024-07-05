/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include <Windows.h>
#include "GDI32/globals.h"

void* GDI32::g_cached_choose_pixel_format_func_ptr   = ChoosePixelFormat;
void* GDI32::g_cached_describe_pixel_format_func_ptr = DescribePixelFormat;
void* GDI32::g_cached_get_pixel_format_func_ptr      = GetPixelFormat;
void* GDI32::g_cached_set_pixel_format_func_ptr      = SetPixelFormat;
void* GDI32::g_cached_swap_buffers_func_ptr          = SwapBuffers;
