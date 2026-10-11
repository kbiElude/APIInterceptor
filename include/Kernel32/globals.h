/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef KERNEL32_GLOBALS_H
#define KERNEL32_GLOBALS_H

#include "Kernel32/types.h"
#include <mutex>
#include <vector>

namespace Kernel32
{
    extern void* g_cached_exit_process_function_ptr;
    extern void* g_cached_load_library_a_function_ptr;
    extern void* g_cached_load_library_ex_a_function_ptr;
    extern void* g_cached_load_library_ex_w_function_ptr;
    extern void* g_cached_load_library_w_function_ptr;

    extern std::mutex                         g_library_loaded_callback_mutex;
    extern std::vector<LibraryLoadedCallback> g_library_loaded_callback_vec;

    extern std::mutex                          g_process_exiting_callback_mutex;
    extern std::vector<ProcessExitingCallback> g_process_exiting_callback_vec;
    extern bool                                g_is_process_exiting_notified; /* guarded by the mutex above */
}

#endif /* KERNEL32_GLOBALS_H */
