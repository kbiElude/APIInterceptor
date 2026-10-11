/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef KERNEL32_CALLBACKS_H
#define KERNEL32_CALLBACKS_H

#include "Kernel32/types.h"

namespace Kernel32
{
    /* Calls the registered callbacks. Does nothing for a null module. */
    void notify_library_loaded(HMODULE in_module);

    /* Calls the registered callbacks, the first time it is called only. */
    void notify_process_exiting();

    void register_for_library_loaded_callback(PFNLIBRARYLOADEDCALLBACKPROC in_function_ptr,
                                              void*                        in_user_argument_ptr);

    /* The callbacks run before ExitProcess() takes the process down, while other threads are still alive. */
    void register_for_process_exiting_callback(PFNPROCESSEXITINGCALLBACKPROC in_function_ptr,
                                               void*                         in_user_argument_ptr);
}

#endif /* KERNEL32_CALLBACKS_H */
