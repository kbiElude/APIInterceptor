/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Types are in alphabetical order, except where a type depends on one that sorts later.
 */
#ifndef KERNEL32_TYPES_H
#define KERNEL32_TYPES_H

#include <Windows.h>

namespace Kernel32
{
    typedef void (WINAPI* PFNEXITPROCESSPROC)(UINT);

    /* Called after a library has been loaded into the process. */
    typedef void (*PFNLIBRARYLOADEDCALLBACKPROC)(HMODULE in_module,
                                                 void*   in_user_argument_ptr);

    struct LibraryLoadedCallback
    {
        PFNLIBRARYLOADEDCALLBACKPROC function_ptr;
        void*                        user_argument_ptr;
    };

    typedef HMODULE (WINAPI* PFNLOADLIBRARYAPROC)  (LPCSTR);
    typedef HMODULE (WINAPI* PFNLOADLIBRARYEXAPROC)(LPCSTR,
                                                    HANDLE,
                                                    DWORD);
    typedef HMODULE (WINAPI* PFNLOADLIBRARYEXWPROC)(LPCWSTR,
                                                    HANDLE,
                                                    DWORD);
    typedef HMODULE (WINAPI* PFNLOADLIBRARYWPROC)  (LPCWSTR);

    /* Called when the process is about to exit, on the thread which exits it. */
    typedef void (*PFNPROCESSEXITINGCALLBACKPROC)(void* in_user_argument_ptr);

    struct ProcessExitingCallback
    {
        PFNPROCESSEXITINGCALLBACKPROC function_ptr;
        void*                         user_argument_ptr;
    };
}

#endif /* KERNEL32_TYPES_H */
