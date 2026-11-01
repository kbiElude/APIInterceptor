/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Interception/Hooks/D3D8/argument_modifier.h"
#include <algorithm>
#include <vector>

/* The modifiers which have been added, in that order. */
static std::vector<Interception::Hooks::D3D8::IArgumentModifier*> g_argument_modifier_ptr_vec;

void Interception::Hooks::D3D8::add_argument_modifier(IArgumentModifier* in_modifier_ptr)
{
    g_argument_modifier_ptr_vec.push_back(in_modifier_ptr);
}

void Interception::Hooks::D3D8::IArgumentModifier::on_create_device(IDirect3D8*,
                                                                    UINT,
                                                                    HWND,
                                                                    D3DPRESENT_PARAMETERS*)
{
    /* Stub */
}

void Interception::Hooks::D3D8::IArgumentModifier::on_set_viewport(IDirect3DDevice8*,
                                                                   const D3DVIEWPORT8**)
{
    /* Stub */
}

void Interception::Hooks::D3D8::remove_argument_modifier(IArgumentModifier* in_modifier_ptr)
{
    g_argument_modifier_ptr_vec.erase(std::remove(g_argument_modifier_ptr_vec.begin(),
                                                  g_argument_modifier_ptr_vec.end  (),
                                                  in_modifier_ptr),
                                      g_argument_modifier_ptr_vec.end() );
}

void Interception::Hooks::D3D8::tell_create_device(IDirect3D8*            in_direct3d_ptr,
                                                   UINT                   in_adapter,
                                                   HWND                   in_focus_window,
                                                   D3DPRESENT_PARAMETERS* inout_parameters_ptr)
{
    for (auto* modifier_ptr : g_argument_modifier_ptr_vec)
    {
        modifier_ptr->on_create_device(in_direct3d_ptr,
                                       in_adapter,
                                       in_focus_window,
                                       inout_parameters_ptr);
    }
}

void Interception::Hooks::D3D8::tell_set_viewport(IDirect3DDevice8*    in_device_ptr,
                                                  const D3DVIEWPORT8** inout_viewport_ptr_ptr)
{
    for (auto* modifier_ptr : g_argument_modifier_ptr_vec)
    {
        modifier_ptr->on_set_viewport(in_device_ptr,
                                      inout_viewport_ptr_ptr);
    }
}
