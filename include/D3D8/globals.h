/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef D3D8_GLOBALS_H
#define D3D8_GLOBALS_H

#include "D3D8/types.h"
#include <mutex>

namespace D3D8
{
    /* Real Direct3DCreate8. Resolved at runtime, as this DLL does not link against d3d8. */
    extern void* g_cached_direct3d_create8_function_ptr;

    /* g_is_direct3d_create8_hooked is set once Direct3DCreate8 has been hooked. Guarded by g_hook_mutex. */
    extern std::mutex g_hook_mutex;
    extern bool       g_is_direct3d_create8_hooked;
}

#endif /* D3D8_GLOBALS_H */
