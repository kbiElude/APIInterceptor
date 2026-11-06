/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * What the common hook (see common/generic_hook.h) needs to know about D3D8.
 */
#ifndef D3D8_HOOK_TRAITS_H
#define D3D8_HOOK_TRAITS_H

#include "common/frame_boundary.h"
#include "interception/hooks/D3D8/argument_capture.h"
#include "interception/hooks/D3D8/hook_policy.h"
#include "interception/hooks/D3D8/object_patcher.h"

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

                static constexpr bool repairs_vtables = false;

                /* The calls of D3D8 which end a frame do so whatever their arguments. */
                template<typename... Arguments>
                static bool is_frame_boundary(const APIInterceptor::APIFunction& in_function,
                                              const Arguments&...)
                {
                    return APIInterceptor::is_frame_boundary(in_function,
                                                             0,
                                                             nullptr);
                }
            };
        }
    }
}

#endif /* D3D8_HOOK_TRAITS_H */
