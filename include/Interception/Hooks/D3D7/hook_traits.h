/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * What the common hook (see Common/generic_hook.h) needs to know about D3D7.
 */
#ifndef D3D7_HOOK_TRAITS_H
#define D3D7_HOOK_TRAITS_H

#include "Common/frame_boundary.h"
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

                /* Direct3D 7 puts its own functions back into the slots of its draw calls when the first draw is made. */
                static constexpr bool repairs_vtables = true;

                static constexpr bool is_frame_boundary(const APIInterceptor::APIFunction& in_function)
                {
                    return APIInterceptor::is_frame_boundary(in_function);
                }
            };
        }
    }
}

#endif /* D3D7_HOOK_TRAITS_H */
