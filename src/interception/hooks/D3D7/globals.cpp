/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "interception/hooks/common/generic_hook.h"
#include "interception/hooks/D3D7/globals.h"
#include "interception/hooks/D3D7/hook_traits.h"

/* The hook of an export is the generic hook of its function, which gets the original function from the export hook itself. */
#define D3D7_EXPORT_HOOK(variable_name, export_name, function_ptr_type, function) \
    Interception::Hooks::Common::ExportHook Interception::Hooks::D3D7::variable_name(L"ddraw.dll", \
                                                                                     export_name, \
                                                                                     reinterpret_cast<void*>(&Interception::Hooks::Common::GenericHook<Interception::Hooks::D3D7::HookTraits, \
                                                                                                                                                       Interception::Hooks::D3D7::function_ptr_type, \
                                                                                                                                                       function, \
                                                                                                                                                       Interception::Hooks::Common::ExportOriginalFunction<&Interception::Hooks::D3D7::variable_name> >::invoke) );

D3D7_EXPORT_HOOK(g_direct_draw_create_clipper_export_hook,  "DirectDrawCreateClipper", PFNDIRECTDRAWCREATECLIPPERPROC, APIInterceptor::APIFUNCTION_D3D7_DIRECTDRAWCREATECLIPPER)
D3D7_EXPORT_HOOK(g_direct_draw_create_export_hook,          "DirectDrawCreate",        PFNDIRECTDRAWCREATEPROC,        APIInterceptor::APIFUNCTION_D3D7_DIRECTDRAWCREATE)
D3D7_EXPORT_HOOK(g_direct_draw_create_ex_export_hook,       "DirectDrawCreateEx",      PFNDIRECTDRAWCREATEEXPROC,      APIInterceptor::APIFUNCTION_D3D7_DIRECTDRAWCREATEEX)
D3D7_EXPORT_HOOK(g_direct_draw_enumerate_a_export_hook,     "DirectDrawEnumerateA",    PFNDIRECTDRAWENUMERATEPROC,     APIInterceptor::APIFUNCTION_D3D7_DIRECTDRAWENUMERATEA)
D3D7_EXPORT_HOOK(g_direct_draw_enumerate_ex_a_export_hook,  "DirectDrawEnumerateExA",  PFNDIRECTDRAWENUMERATEEXPROC,   APIInterceptor::APIFUNCTION_D3D7_DIRECTDRAWENUMERATEEXA)
D3D7_EXPORT_HOOK(g_direct_draw_enumerate_ex_w_export_hook,  "DirectDrawEnumerateExW",  PFNDIRECTDRAWENUMERATEEXPROC,   APIInterceptor::APIFUNCTION_D3D7_DIRECTDRAWENUMERATEEXW)
D3D7_EXPORT_HOOK(g_direct_draw_enumerate_w_export_hook,     "DirectDrawEnumerateW",    PFNDIRECTDRAWENUMERATEPROC,     APIInterceptor::APIFUNCTION_D3D7_DIRECTDRAWENUMERATEW)

#undef D3D7_EXPORT_HOOK
