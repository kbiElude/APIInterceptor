/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef D3D7_GLOBALS_H
#define D3D7_GLOBALS_H

#include "Interception/Hooks/Common/export_hook.h"

namespace Interception
{
    namespace Hooks
    {
        namespace D3D7
        {
            /* DirectDrawCreateEx of ddraw.dll, which this DLL does not link against: found, and hooked, once ddraw.dll is loaded. */
            extern Interception::Hooks::Common::ExportHook g_direct_draw_create_ex_export_hook;
        }
    }
}

#endif /* D3D7_GLOBALS_H */
