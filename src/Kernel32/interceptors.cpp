/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Kernel32/entrypoints.h"
#include "Kernel32/globals.h"
#include "Kernel32/interceptors.h"

std::vector<APIInterceptor::FunctionInterceptor> Kernel32::get_function_interceptors()
{
    return std::vector<APIInterceptor::FunctionInterceptor>
    {
        APIInterceptor::FunctionInterceptor(&(PVOID&) Kernel32::g_cached_exit_process_function_ptr,      Kernel32::aiExitProcess),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Kernel32::g_cached_load_library_a_function_ptr,    Kernel32::aiLoadLibraryA),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Kernel32::g_cached_load_library_ex_a_function_ptr, Kernel32::aiLoadLibraryExA),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Kernel32::g_cached_load_library_ex_w_function_ptr, Kernel32::aiLoadLibraryExW),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Kernel32::g_cached_load_library_w_function_ptr,    Kernel32::aiLoadLibraryW),
    };
}
