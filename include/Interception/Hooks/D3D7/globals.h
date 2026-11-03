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
            /* The functions which ddraw.dll exports. This DLL does not link against it: they are found, and hooked, once ddraw.dll
             * is loaded.
             */
            extern Interception::Hooks::Common::ExportHook g_direct_draw_create_clipper_export_hook;
            extern Interception::Hooks::Common::ExportHook g_direct_draw_create_export_hook;
            extern Interception::Hooks::Common::ExportHook g_direct_draw_create_ex_export_hook;
            extern Interception::Hooks::Common::ExportHook g_direct_draw_enumerate_a_export_hook;
            extern Interception::Hooks::Common::ExportHook g_direct_draw_enumerate_ex_a_export_hook;
            extern Interception::Hooks::Common::ExportHook g_direct_draw_enumerate_ex_w_export_hook;
            extern Interception::Hooks::Common::ExportHook g_direct_draw_enumerate_w_export_hook;
        }
    }
}

#endif /* D3D7_GLOBALS_H */
