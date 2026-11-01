/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Interception/Hooks/Kernel32/callbacks.h"
#include "Interception/Hooks/Kernel32/entrypoints.h"
#include "Interception/Hooks/Kernel32/globals.h"

DECLSPEC_NORETURN void WINAPI Kernel32::aiExitProcess(UINT uExitCode)
{
    notify_process_exiting();

    reinterpret_cast<PFNEXITPROCESSPROC>(g_cached_exit_process_function_ptr)(uExitCode);

    /* Not reached. The original function never returns. */
    ::TerminateProcess(::GetCurrentProcess(),
                       uExitCode);
}
