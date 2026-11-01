/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Interception/Hooks/Kernel32/globals.h"

void* Interception::Hooks::Kernel32::g_cached_exit_process_function_ptr      = ExitProcess;
void* Interception::Hooks::Kernel32::g_cached_load_library_a_function_ptr    = LoadLibraryA;
void* Interception::Hooks::Kernel32::g_cached_load_library_ex_a_function_ptr = LoadLibraryExA;
void* Interception::Hooks::Kernel32::g_cached_load_library_ex_w_function_ptr = LoadLibraryExW;
void* Interception::Hooks::Kernel32::g_cached_load_library_w_function_ptr    = LoadLibraryW;

std::mutex                                   Interception::Hooks::Kernel32::g_library_loaded_callback_mutex;
std::vector<Interception::Hooks::Kernel32::LibraryLoadedCallback> Interception::Hooks::Kernel32::g_library_loaded_callback_vec;

std::mutex                                    Interception::Hooks::Kernel32::g_process_exiting_callback_mutex;
std::vector<Interception::Hooks::Kernel32::ProcessExitingCallback> Interception::Hooks::Kernel32::g_process_exiting_callback_vec;
bool                                          Interception::Hooks::Kernel32::g_is_process_exiting_notified = false;
