/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Kernel32/callbacks.h"
#include "Kernel32/globals.h"

void Kernel32::notify_library_loaded(HMODULE in_module)
{
    std::vector<LibraryLoadedCallback> callback_vec;

    if (in_module != nullptr)
    {
        {
            std::lock_guard<std::mutex> lock(g_library_loaded_callback_mutex);

            callback_vec = g_library_loaded_callback_vec;
        }

        /* Called outside the lock, so that callbacks can register further callbacks. */
        for (const auto& callback : callback_vec)
        {
            callback.function_ptr(in_module,
                                  callback.user_argument_ptr);
        }
    }
}

void Kernel32::notify_process_exiting()
{
    std::vector<ProcessExitingCallback> callback_vec;

    {
        std::lock_guard<std::mutex> lock(g_process_exiting_callback_mutex);

        if (g_is_process_exiting_notified == false)
        {
            g_is_process_exiting_notified = true;
            callback_vec                  = g_process_exiting_callback_vec;
        }
    }

    /* Called outside the lock, as the callbacks may take a while. */
    for (const auto& callback : callback_vec)
    {
        callback.function_ptr(callback.user_argument_ptr);
    }
}

void Kernel32::register_for_library_loaded_callback(PFNLIBRARYLOADEDCALLBACKPROC in_function_ptr,
                                                    void*                        in_user_argument_ptr)
{
    {
        std::lock_guard<std::mutex> lock(g_library_loaded_callback_mutex);

        g_library_loaded_callback_vec.push_back({in_function_ptr, in_user_argument_ptr});
    }
}

void Kernel32::register_for_process_exiting_callback(PFNPROCESSEXITINGCALLBACKPROC in_function_ptr,
                                                     void*                         in_user_argument_ptr)
{
    {
        std::lock_guard<std::mutex> lock(g_process_exiting_callback_mutex);

        g_process_exiting_callback_vec.push_back({in_function_ptr, in_user_argument_ptr});
    }
}
