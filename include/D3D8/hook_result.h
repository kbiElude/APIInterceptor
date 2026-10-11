/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Value returned by a hooked method.
 */
#ifndef D3D8_HOOK_RESULT_H
#define D3D8_HOOK_RESULT_H

#include "D3D8/argument_capture.h"
#include "D3D8/success_traits.h"
#include <utility>

namespace D3D8
{
    template<typename ReturnType>
    struct HookResult
    {
        ReturnType value;

        HookResult();

        template<typename Function, typename... Arguments>
        void call(Function in_function, Arguments&&... in_arguments);

        APIInterceptor::APIFunctionArgument create_argument() const;
        ReturnType                          get            () const;
        bool                                is_success     () const;
    };

    template<>
    struct HookResult<void>
    {
        template<typename Function, typename... Arguments>
        void call(Function in_function, Arguments&&... in_arguments);

        APIInterceptor::APIFunctionArgument create_argument() const;
        void                                get            () const;
        bool                                is_success     () const;
    };
}

template<typename ReturnType>
D3D8::HookResult<ReturnType>::HookResult()
    :value()
{
    /* Stub */
}

template<typename ReturnType>
template<typename Function, typename... Arguments>
void D3D8::HookResult<ReturnType>::call(Function in_function, Arguments&&... in_arguments)
{
    value = in_function(std::forward<Arguments>(in_arguments)...);
}

template<typename ReturnType>
APIInterceptor::APIFunctionArgument D3D8::HookResult<ReturnType>::create_argument() const
{
    return ArgumentCapture<ReturnType>::create_post_argument(value,
                                                             APIInterceptor::APIFunctionArgument(),
                                                             false); /* in_is_pre_argument_valid */
}

template<typename ReturnType>
ReturnType D3D8::HookResult<ReturnType>::get() const
{
    return value;
}

template<typename ReturnType>
bool D3D8::HookResult<ReturnType>::is_success() const
{
    return SuccessTraits<ReturnType>::is_success(value);
}

template<typename Function, typename... Arguments>
void D3D8::HookResult<void>::call(Function in_function, Arguments&&... in_arguments)
{
    in_function(std::forward<Arguments>(in_arguments)...);
}

#endif /* D3D8_HOOK_RESULT_H */
