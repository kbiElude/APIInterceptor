/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef D3D8_GLOBALS_H
#define D3D8_GLOBALS_H

#include "Interception/Hooks/Common/export_hook.h"

namespace Interception
{
    namespace Hooks
    {
        namespace D3D8
        {
            /* Direct3DCreate8 of d3d8.dll, which this DLL does not link against: found, and hooked, once d3d8.dll is loaded. */
            extern Interception::Hooks::Common::ExportHook g_direct3d_create8_export_hook;
        }
    }
}

#endif /* D3D8_GLOBALS_H */
