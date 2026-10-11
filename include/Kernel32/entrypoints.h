/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Hooks of kernel32 functions. They only notify about loaded libraries and about the process exiting; they are not
 * recorded.
 */
#ifndef KERNEL32_ENTRYPOINTS_H
#define KERNEL32_ENTRYPOINTS_H

#include <Windows.h>

namespace Kernel32
{
    DECLSPEC_NORETURN void WINAPI aiExitProcess(UINT uExitCode);

    HMODULE WINAPI aiLoadLibraryA  (LPCSTR  lpLibFileName);
    HMODULE WINAPI aiLoadLibraryExA(LPCSTR  lpLibFileName,
                                    HANDLE  hFile,
                                    DWORD   dwFlags);
    HMODULE WINAPI aiLoadLibraryExW(LPCWSTR lpLibFileName,
                                    HANDLE  hFile,
                                    DWORD   dwFlags);
    HMODULE WINAPI aiLoadLibraryW  (LPCWSTR lpLibFileName);
}

#endif /* KERNEL32_ENTRYPOINTS_H */
