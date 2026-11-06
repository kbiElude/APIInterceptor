/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "interception/hooks/User32/entrypoints/adjust_window_rect_ex.h"
#include "interception/hooks/User32/entrypoints/create_dc_a.h"
#include "interception/hooks/User32/entrypoints/create_dc_w.h"
#include "interception/hooks/User32/entrypoints/create_window_ex_a.h"
#include "interception/hooks/User32/entrypoints/create_window_ex_w.h"
#include "interception/hooks/User32/entrypoints/get_dc.h"
#include "interception/hooks/User32/entrypoints/release_dc.h"
#include "interception/hooks/User32/globals.h"
#include "interception/hooks/User32/interceptors.h"

std::vector<APIInterceptor::FunctionInterceptor> Interception::Hooks::User32::get_function_interceptors()
{
    return std::vector<APIInterceptor::FunctionInterceptor>
    {
        APIInterceptor::FunctionInterceptor(&(PVOID&)Interception::Hooks::User32::g_cached_adjust_window_rect_ex_func_ptr, Interception::Hooks::User32::adjust_window_rect_ex),
        APIInterceptor::FunctionInterceptor(&(PVOID&)Interception::Hooks::User32::g_cached_create_dc_a_func_ptr,           Interception::Hooks::User32::create_dc_a),
        APIInterceptor::FunctionInterceptor(&(PVOID&)Interception::Hooks::User32::g_cached_create_dc_w_func_ptr,           Interception::Hooks::User32::create_dc_w),
        APIInterceptor::FunctionInterceptor(&(PVOID&)Interception::Hooks::User32::g_cached_create_window_ex_a_func_ptr,    Interception::Hooks::User32::create_window_ex_a),
        APIInterceptor::FunctionInterceptor(&(PVOID&)Interception::Hooks::User32::g_cached_create_window_ex_w_func_ptr,    Interception::Hooks::User32::create_window_ex_w),
        APIInterceptor::FunctionInterceptor(&(PVOID&)Interception::Hooks::User32::g_cached_get_dc_func_ptr,                Interception::Hooks::User32::get_dc),
        APIInterceptor::FunctionInterceptor(&(PVOID&)Interception::Hooks::User32::g_cached_release_dc_func_ptr,            Interception::Hooks::User32::release_dc),
    };
}