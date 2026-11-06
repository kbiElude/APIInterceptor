/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "interception/hooks/Kernel32/entrypoints.h"
#include "interception/hooks/Kernel32/globals.h"
#include "interception/hooks/Kernel32/interceptors.h"

std::vector<APIInterceptor::FunctionInterceptor> Interception::Hooks::Kernel32::get_function_interceptors()
{
    return std::vector<APIInterceptor::FunctionInterceptor>
    {
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::Kernel32::g_cached_exit_process_function_ptr,      Interception::Hooks::Kernel32::aiExitProcess),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::Kernel32::g_cached_load_library_a_function_ptr,    Interception::Hooks::Kernel32::aiLoadLibraryA),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::Kernel32::g_cached_load_library_ex_a_function_ptr, Interception::Hooks::Kernel32::aiLoadLibraryExA),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::Kernel32::g_cached_load_library_ex_w_function_ptr, Interception::Hooks::Kernel32::aiLoadLibraryExW),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::Kernel32::g_cached_load_library_w_function_ptr,    Interception::Hooks::Kernel32::aiLoadLibraryW),
    };
}
