/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Kernel32/callbacks.h"
#include "Kernel32/entrypoints.h"
#include "Kernel32/globals.h"

HMODULE WINAPI Kernel32::aiLoadLibraryA(LPCSTR lpLibFileName)
{
    const HMODULE result = reinterpret_cast<PFNLOADLIBRARYAPROC>(g_cached_load_library_a_function_ptr)(lpLibFileName);

    notify_library_loaded(result);

    return result;
}

HMODULE WINAPI Kernel32::aiLoadLibraryExA(LPCSTR lpLibFileName,
                                          HANDLE hFile,
                                          DWORD  dwFlags)
{
    const HMODULE result = reinterpret_cast<PFNLOADLIBRARYEXAPROC>(g_cached_load_library_ex_a_function_ptr)(lpLibFileName,
                                                                                                            hFile,
                                                                                                            dwFlags);

    notify_library_loaded(result);

    return result;
}

HMODULE WINAPI Kernel32::aiLoadLibraryExW(LPCWSTR lpLibFileName,
                                          HANDLE  hFile,
                                          DWORD   dwFlags)
{
    const HMODULE result = reinterpret_cast<PFNLOADLIBRARYEXWPROC>(g_cached_load_library_ex_w_function_ptr)(lpLibFileName,
                                                                                                            hFile,
                                                                                                            dwFlags);

    notify_library_loaded(result);

    return result;
}

HMODULE WINAPI Kernel32::aiLoadLibraryW(LPCWSTR lpLibFileName)
{
    const HMODULE result = reinterpret_cast<PFNLOADLIBRARYWPROC>(g_cached_load_library_w_function_ptr)(lpLibFileName);

    notify_library_loaded(result);

    return result;
}
