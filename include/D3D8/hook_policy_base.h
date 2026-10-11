/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * What a method gets from HookPolicy when it has no specialization: nothing.
 */
#ifndef D3D8_HOOK_POLICY_BASE_H
#define D3D8_HOOK_POLICY_BASE_H

#include "D3D8/types.h"

namespace D3D8
{
    struct HookPolicyBase
    {
        static const uint32_t n_extra_arguments = 0;

        template<typename... Arguments>
        static void create_extra_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                           const Arguments&...                  in_arguments);

        template<typename... Arguments>
        static void on_call_finished(const bool&         in_is_success,
                                     const Arguments&... in_arguments);
    };
}

template<typename... Arguments>
void D3D8::HookPolicyBase::create_extra_arguments(APIInterceptor::APIFunctionArgument*,
                                                  const Arguments&...)
{
    /* Stub */
}

template<typename... Arguments>
void D3D8::HookPolicyBase::on_call_finished(const bool&,
                                            const Arguments&...)
{
    /* Stub */
}

#endif /* D3D8_HOOK_POLICY_BASE_H */
