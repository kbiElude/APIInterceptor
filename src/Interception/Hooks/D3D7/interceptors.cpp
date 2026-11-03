/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Interception/Hooks/D3D7/globals.h"
#include "Interception/Hooks/D3D7/interceptors.h"

void Interception::Hooks::D3D7::on_attach()
{
    g_direct_draw_create_ex_export_hook.on_attach();
}

void Interception::Hooks::D3D7::on_detach()
{
    /* Patched vtables are left as is (see Common/vtable_registry.h). */
    g_direct_draw_create_ex_export_hook.on_detach();
}
