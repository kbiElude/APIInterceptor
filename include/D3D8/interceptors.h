/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef D3D8_INTERCEPTORS_H
#define D3D8_INTERCEPTORS_H

#include <Windows.h>

namespace D3D8
{
    /* Hooks Direct3DCreate8 of the given d3d8.dll, unless already hooked. */
    void attach_to_module(HMODULE in_d3d8_module);

    /* Call after the interceptors are attached. Hooks D3D8 now if d3d8.dll is loaded, otherwise once it gets loaded. */
    void on_attach();

    /* Call before the interceptors are detached. */
    void on_detach();

    /* Kernel32::PFNLIBRARYLOADEDCALLBACKPROC */
    void on_library_loaded(HMODULE in_module,
                           void*   in_user_argument_ptr);
}

#endif /* D3D8_INTERCEPTORS_H */
