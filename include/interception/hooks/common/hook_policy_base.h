/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * What a method gets from HookPolicy when it has no specialization: nothing.
 */
#ifndef HOOKS_COMMON_HOOK_POLICY_BASE_H
#define HOOKS_COMMON_HOOK_POLICY_BASE_H

#include "common/api_function_argument.h"
#include "interception/hooks/common/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace Common
        {
            struct HookPolicyBase
            {
                static const uint32_t n_extra_arguments = 0;

                template<typename... Arguments>
                static void create_extra_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                                   const Arguments&...                  in_arguments);

                template<typename... Arguments>
                static void on_call_finished(const bool& in_is_success,
                                             const Arguments&... in_arguments);

                /* Before the original method is called, with the arguments of the application, which it may change through the pointers. */
                template<typename... Arguments>
                static void on_call_starting(const Arguments&... in_arguments);
            };
        }
    }
}

template<typename... Arguments>
void Interception::Hooks::Common::HookPolicyBase::create_extra_arguments(APIInterceptor::APIFunctionArgument*,
                                                                         const Arguments&...)
{
    /* Stub */
}

template<typename... Arguments>
void Interception::Hooks::Common::HookPolicyBase::on_call_finished(const bool&,
                                                                   const Arguments&...)
{
    /* Stub */
}

template<typename... Arguments>
void Interception::Hooks::Common::HookPolicyBase::on_call_starting(const Arguments&...)
{
    /* Stub */
}

#endif /* HOOKS_COMMON_HOOK_POLICY_BASE_H */
