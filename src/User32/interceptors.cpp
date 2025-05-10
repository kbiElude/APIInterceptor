/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "User32/entrypoints/create_window_ex_a.h"
#include "User32/entrypoints/get_dc.h"
#include "User32/entrypoints/release_dc.h"
#include "User32/globals.h"
#include "User32/interceptors.h"

std::vector<APIInterceptor::FunctionInterceptor> User32::get_function_interceptors()
{
    return std::vector<APIInterceptor::FunctionInterceptor>
    {
        APIInterceptor::FunctionInterceptor(&(PVOID&)User32::g_cached_create_window_ex_a_func_ptr, User32::create_window_ex_a),
        APIInterceptor::FunctionInterceptor(&(PVOID&)User32::g_cached_get_dc_func_ptr,             User32::get_dc),
        APIInterceptor::FunctionInterceptor(&(PVOID&)User32::g_cached_release_dc_func_ptr,         User32::release_dc),
    };
}