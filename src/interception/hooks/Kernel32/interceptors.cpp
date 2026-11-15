/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "interception/hooks/Kernel32/entrypoints.h"
#include "interception/hooks/Kernel32/globals.h"
#include "interception/hooks/Kernel32/interceptors.h"

std::vector<APIInterceptor::FunctionHookTarget> Interception::Hooks::Kernel32::get_function_interceptors()
{
    return std::vector<APIInterceptor::FunctionHookTarget>
    {
        APIInterceptor::FunctionHookTarget(&(PVOID&) Interception::Hooks::Kernel32::g_cached_exit_process_function_ptr,       Interception::Hooks::Kernel32::aiExitProcess),
        APIInterceptor::FunctionHookTarget(&(PVOID&) Interception::Hooks::Kernel32::g_cached_load_library_a_function_ptr,     Interception::Hooks::Kernel32::aiLoadLibraryA),
        APIInterceptor::FunctionHookTarget(&(PVOID&) Interception::Hooks::Kernel32::g_cached_load_library_ex_a_function_ptr, Interception::Hooks::Kernel32::aiLoadLibraryExA),
        APIInterceptor::FunctionHookTarget(&(PVOID&) Interception::Hooks::Kernel32::g_cached_load_library_ex_w_function_ptr, Interception::Hooks::Kernel32::aiLoadLibraryExW),
        APIInterceptor::FunctionHookTarget(&(PVOID&) Interception::Hooks::Kernel32::g_cached_load_library_w_function_ptr,     Interception::Hooks::Kernel32::aiLoadLibraryW),
    };
}
