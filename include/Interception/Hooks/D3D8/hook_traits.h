/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * What the common hook (see Common/generic_hook.h) needs to know about D3D8.
 */
#ifndef D3D8_HOOK_TRAITS_H
#define D3D8_HOOK_TRAITS_H

#include "Interception/Hooks/D3D8/argument_capture.h"
#include "Interception/Hooks/D3D8/hook_policy.h"
#include "Interception/Hooks/D3D8/object_patcher.h"

namespace Interception
{
    namespace Hooks
    {
        namespace D3D8
        {
            struct HookTraits
            {
                template<typename T>
                using ArgumentCapture = Interception::Hooks::D3D8::ArgumentCapture<T>;

                template<APIInterceptor::APIFunction function>
                using HookPolicy = Interception::Hooks::D3D8::HookPolicy<function>;

                template<typename T>
                using ObjectPatcher = Interception::Hooks::D3D8::ObjectPatcher<T>;

                /* The device's Present call ends the frame. */
                static constexpr bool is_frame_boundary(const APIInterceptor::APIFunction& in_function)
                {
                    return in_function == APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_PRESENT;
                }
            };
        }
    }
}

#endif /* D3D8_HOOK_TRAITS_H */
