/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * What the common hook (see Common/generic_hook.h) needs to know about D3D7.
 */
#ifndef D3D7_HOOK_TRAITS_H
#define D3D7_HOOK_TRAITS_H

#include "Interception/Hooks/D3D7/argument_capture.h"
#include "Interception/Hooks/D3D7/hook_policy.h"
#include "Interception/Hooks/D3D7/object_patcher.h"

namespace Interception
{
    namespace Hooks
    {
        namespace D3D7
        {
            struct HookTraits
            {
                template<typename T>
                using ArgumentCapture = Interception::Hooks::D3D7::ArgumentCapture<T>;

                template<APIInterceptor::APIFunction function>
                using HookPolicy = Interception::Hooks::D3D7::HookPolicy<function>;

                template<typename T>
                using ObjectPatcher = Interception::Hooks::D3D7::ObjectPatcher<T>;

                /* Flipping the surfaces ends the frame of a program that has the screen to itself. The copy of a frame into a
                 * window (a Blt to the primary surface) is not recognized yet.
                 */
                static constexpr bool is_frame_boundary(const APIInterceptor::APIFunction& in_function)
                {
                    return in_function == APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAWSURFACE7_FLIP;
                }
            };
        }
    }
}

#endif /* D3D7_HOOK_TRAITS_H */
