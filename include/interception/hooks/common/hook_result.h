/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Value returned by a hooked method. How the value is stored as an argument is up to the API (see create_argument()).
 */
#ifndef HOOKS_COMMON_HOOK_RESULT_H
#define HOOKS_COMMON_HOOK_RESULT_H

#include "common/api_function_argument.h"
#include "interception/hooks/common/argument_factory.h"
#include "interception/hooks/common/success_traits.h"
#include <utility>

namespace Interception
{
    namespace Hooks
    {
        namespace Common
        {
            template<typename ReturnType>
            struct HookResult
            {
                ReturnType value;

                HookResult();

                template<typename Function, typename... Arguments>
                void call(Function in_function,
                          Arguments&&... in_arguments);

                /* Capture is the API's ArgumentCapture<ReturnType>. */
                template<typename Capture>
                APIInterceptor::APIFunctionArgument create_argument() const;
                ReturnType                          get            () const;
                bool                                is_success     () const;
            };

            template<>
            struct HookResult<void>
            {
                template<typename Function, typename... Arguments>
                void call(Function in_function,
                          Arguments&&... in_arguments);

                template<typename Capture>
                APIInterceptor::APIFunctionArgument create_argument() const;
                void                                get            () const;
                bool                                is_success     () const;
            };
        }
    }
}

template<typename ReturnType>
Interception::Hooks::Common::HookResult<ReturnType>::HookResult()
    :value()
{
    /* Stub */
}

template<typename ReturnType>
template<typename Function, typename... Arguments>
void Interception::Hooks::Common::HookResult<ReturnType>::call(Function in_function, Arguments&&... in_arguments)
{
    value = in_function(std::forward<Arguments>(in_arguments)...);
}

template<typename ReturnType>
template<typename Capture>
APIInterceptor::APIFunctionArgument Interception::Hooks::Common::HookResult<ReturnType>::create_argument() const
{
    return Capture::create_post_argument(value,
                                         APIInterceptor::APIFunctionArgument(),
                                         false); /* in_is_pre_argument_valid */
}

template<typename ReturnType>
ReturnType Interception::Hooks::Common::HookResult<ReturnType>::get() const
{
    return value;
}

template<typename ReturnType>
bool Interception::Hooks::Common::HookResult<ReturnType>::is_success() const
{
    return SuccessTraits<ReturnType>::is_success(value);
}

template<typename Function, typename... Arguments>
void Interception::Hooks::Common::HookResult<void>::call(Function in_function, Arguments&&... in_arguments)
{
    in_function(std::forward<Arguments>(in_arguments)...);
}

template<typename Capture>
APIInterceptor::APIFunctionArgument Interception::Hooks::Common::HookResult<void>::create_argument() const
{
    return ArgumentFactory::create_unknown();
}

#endif /* HOOKS_COMMON_HOOK_RESULT_H */
