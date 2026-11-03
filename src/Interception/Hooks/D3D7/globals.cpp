/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Interception/Hooks/D3D7/entrypoints.h"
#include "Interception/Hooks/D3D7/globals.h"

Interception::Hooks::Common::ExportHook Interception::Hooks::D3D7::g_direct_draw_create_ex_export_hook(L"ddraw.dll",
                                                                                                       "DirectDrawCreateEx",
                                                                                                       reinterpret_cast<void*>(&Interception::Hooks::D3D7::aiDirectDrawCreateEx) );
