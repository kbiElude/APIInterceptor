/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Interception/Hooks/GDI32/entrypoints/choose_pixel_format.h"
#include "Interception/Hooks/GDI32/entrypoints/describe_pixel_format.h"
#include "Interception/Hooks/GDI32/entrypoints/get_pixel_format.h"
#include "Interception/Hooks/GDI32/entrypoints/set_pixel_format.h"
#include "Interception/Hooks/GDI32/entrypoints/swap_buffers.h"
#include "Interception/Hooks/GDI32/globals.h"
#include "Interception/Hooks/GDI32/interceptors.h"

std::vector<APIInterceptor::FunctionInterceptor> Interception::Hooks::GDI32::get_function_interceptors()
{
    return std::vector<APIInterceptor::FunctionInterceptor>
    {
        APIInterceptor::FunctionInterceptor(&(PVOID&)Interception::Hooks::GDI32::g_cached_choose_pixel_format_func_ptr,   Interception::Hooks::GDI32::choose_pixel_format),
        APIInterceptor::FunctionInterceptor(&(PVOID&)Interception::Hooks::GDI32::g_cached_describe_pixel_format_func_ptr, Interception::Hooks::GDI32::describe_pixel_format),
        APIInterceptor::FunctionInterceptor(&(PVOID&)Interception::Hooks::GDI32::g_cached_get_pixel_format_func_ptr,      Interception::Hooks::GDI32::get_pixel_format),
        APIInterceptor::FunctionInterceptor(&(PVOID&)Interception::Hooks::GDI32::g_cached_set_pixel_format_func_ptr,      Interception::Hooks::GDI32::set_pixel_format),
        APIInterceptor::FunctionInterceptor(&(PVOID&)Interception::Hooks::GDI32::g_cached_swap_buffers_func_ptr,          Interception::Hooks::GDI32::swap_buffers)
    };
}