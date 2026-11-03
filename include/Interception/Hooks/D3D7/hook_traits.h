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

                /* The surface an argument is, if it is one. */
                static IDirectDrawSurface7* as_surface_ptr(IDirectDrawSurface7* in_surface_ptr)
                {
                    return in_surface_ptr;
                }

                template<typename Other>
                static IDirectDrawSurface7* as_surface_ptr(const Other&)
                {
                    return nullptr;
                }

                /* The flip of surfaces ends a frame, and so does the blit of one to the primary surface (for a program that draws in a
                 * window, and has nothing to flip): the policy of the blit tells the same, in an argument.
                 */
                template<typename First, typename... Rest>
                static bool is_frame_boundary(const APIInterceptor::APIFunction& in_function,
                                              const First&                       in_first_argument,
                                              const Rest&...)
                {
                    bool result = false;

                    if (in_function == APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAWSURFACE7_BLT     ||
                        in_function == APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAWSURFACE7_BLTFAST)
                    {
                        /* The first argument of a method is its object. */
                        result = HookPolicyHelper::is_primary_surface(as_surface_ptr(in_first_argument) );
                    }
                    else
                    {
                        result = APIInterceptor::is_frame_boundary(in_function,
                                                                   0,
                                                                   nullptr);
                    }

                    return result;
                }
            };
        }
    }
}

#endif /* D3D7_HOOK_TRAITS_H */
