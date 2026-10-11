/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Kernel32/globals.h"

void* Kernel32::g_cached_exit_process_function_ptr      = ExitProcess;
void* Kernel32::g_cached_load_library_a_function_ptr    = LoadLibraryA;
void* Kernel32::g_cached_load_library_ex_a_function_ptr = LoadLibraryExA;
void* Kernel32::g_cached_load_library_ex_w_function_ptr = LoadLibraryExW;
void* Kernel32::g_cached_load_library_w_function_ptr    = LoadLibraryW;

std::mutex                                   Kernel32::g_library_loaded_callback_mutex;
std::vector<Kernel32::LibraryLoadedCallback> Kernel32::g_library_loaded_callback_vec;

std::mutex                                    Kernel32::g_process_exiting_callback_mutex;
std::vector<Kernel32::ProcessExitingCallback> Kernel32::g_process_exiting_callback_vec;
bool                                          Kernel32::g_is_process_exiting_notified = false;
