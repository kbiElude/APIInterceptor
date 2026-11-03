/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Interception/Hooks/D3D8/entrypoints.h"
#include "Interception/Hooks/D3D8/globals.h"

Interception::Hooks::Common::ExportHook Interception::Hooks::D3D8::g_direct3d_create8_export_hook(L"d3d8.dll",
                                                                                                  "Direct3DCreate8",
                                                                                                  reinterpret_cast<void*>(&Interception::Hooks::D3D8::aiDirect3DCreate8) );
