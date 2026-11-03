/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Method-specific additions to the common hook (see Common/generic_hook.h): extra arguments holding data which a call refers
 * to, and bookkeeping which follows a call.
 */
#ifndef D3D7_HOOK_POLICY_H
#define D3D7_HOOK_POLICY_H

#include "Interception/Hooks/Common/hook_policy_base.h"
#include "Interception/Hooks/D3D7/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace D3D7
        {
            typedef Interception::Hooks::Common::HookPolicyBase HookPolicyBase;

            template<APIInterceptor::APIFunction function>
            struct HookPolicy : public HookPolicyBase
            {
                /* Stub */
            };

            /* Direct3D 7 is made out of a DirectDraw 7 object: its interface is asked for with QueryInterface. */
            template<>
            struct HookPolicy<APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAW7_QUERYINTERFACE> : public HookPolicyBase
            {
                static void on_call_finished(const bool& in_is_success,
                                             IDirectDraw7* in_self,
                                             const GUID&   in_iid,
                                             void**        in_object_ptr_ptr);
            };
        }
    }
}

#endif /* D3D7_HOOK_POLICY_H */
