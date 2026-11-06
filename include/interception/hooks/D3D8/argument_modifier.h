/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Lets a program that has the interceptor loaded change what an application passes to the device, as it passes it. The callbacks of
 * the interceptor only see a copy of the arguments (see D3D8/argument_capture_selector.h), so this is the way for what has to reach
 * the device changed: a modifier is told the arguments of a call, after the callbacks have seen the call as the application made it
 * and before the method is called.
 *
 * Only the calls of the application are modified. What a callback calls on the device is not: it knows what it passes.
 *
 * Modifiers are added before the application makes its device, and taken out after it is done; they are not guarded against being
 * changed while the application calls. Several can be added; each is told, in the order they were added.
 */
#ifndef D3D8_ARGUMENT_MODIFIER_H
#define D3D8_ARGUMENT_MODIFIER_H

#include "interception/hooks/D3D8/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace D3D8
        {
            class IArgumentModifier
            {
            public:
                virtual ~IArgumentModifier() = default;

                /* IDirect3D8::CreateDevice: the presentation parameters, which may be changed. */
                virtual void on_create_device(IDirect3D8*            in_direct3d_ptr,
                                              UINT                   in_adapter,
                                              HWND                   in_focus_window,
                                              D3DPRESENT_PARAMETERS* inout_parameters_ptr);

                /* IDirect3DDevice8::SetViewport: the viewport the application passes. To pass another one, the pointer is set to point at it,
                 * which has to last until the call returns.
                 */
                virtual void on_set_viewport(IDirect3DDevice8*    in_device_ptr,
                                             const D3DVIEWPORT8** inout_viewport_ptr_ptr);
            };

            void add_argument_modifier   (IArgumentModifier* in_modifier_ptr);
            void remove_argument_modifier(IArgumentModifier* in_modifier_ptr);

            /* What a hook calls, to tell all the modifiers. */
            void tell_create_device(IDirect3D8*            in_direct3d_ptr,
                                    UINT                   in_adapter,
                                    HWND                   in_focus_window,
                                    D3DPRESENT_PARAMETERS* inout_parameters_ptr);
            void tell_set_viewport (IDirect3DDevice8*      in_device_ptr,
                                    const D3DVIEWPORT8**   inout_viewport_ptr_ptr);
        }
    }
}

#endif /* D3D8_ARGUMENT_MODIFIER_H */
