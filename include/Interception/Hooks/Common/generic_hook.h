/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Hook of a COM method or of a function exported by a DLL, generated from the function pointer type. It reports the call to
 * the registered callbacks, forwards it to the original function, and hooks the interfaces which the call has handed out.
 * OriginalFunction tells where the original function is (see Common/original_function_providers.h).
 *
 * What is specific to an API comes from its traits type, which has:
 *   ArgumentCapture<T>      how an argument of type T is stored (create_pre_argument(), create_post_argument())
 *   HookPolicy<function>    the extra arguments and bookkeeping of a method (see HookPolicyBase)
 *   ObjectPatcher<T>        hooks the interface which an argument of type T hands out (patch())
 *   is_frame_boundary(f)    tells if a call of the function ends a frame
 *   repairs_vtables         true if the runtime of the API is known to overwrite the hooks in the vtables it hands out
 */
#ifndef HOOKS_COMMON_GENERIC_HOOK_H
#define HOOKS_COMMON_GENERIC_HOOK_H

#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "Interception/Hooks/Common/hook_result.h"
#include "Interception/Hooks/Common/original_function_providers.h"
#include <algorithm>
#include <array>
#include <utility>

namespace Interception
{
    namespace Hooks
    {
        namespace Common
        {
            template<typename Traits, typename FunctionPtr, APIInterceptor::APIFunction function, typename OriginalFunction>
            struct GenericHook;

            template<typename Traits, typename ReturnType, typename... Arguments, APIInterceptor::APIFunction function, typename OriginalFunction>
            struct GenericHook<Traits, ReturnType (__stdcall*)(Arguments...), function, OriginalFunction>
            {
                typedef typename Traits::template HookPolicy<function> Policy;

                static_assert(sizeof...(Arguments) + Policy::n_extra_arguments <= APIInterceptor::MAX_N_FUNCTION_ARGUMENTS,
                              "The callbacks are given more arguments than the dumper has room for");

                typedef std::array<APIInterceptor::APIFunctionArgument, sizeof...(Arguments) + Policy::n_extra_arguments> ArgumentArray;
                typedef std::array<APIInterceptor::APIFunctionArgument, sizeof...(Arguments)>                             HeadArray;

                static ReturnType __stdcall invoke(Arguments... in_arguments);

            private:
                template<size_t... Indices>
                static HeadArray create_post_arguments(const ArgumentArray& in_pre_argument_array,
                                                       const bool&          in_is_pre_argument_valid,
                                                       std::index_sequence<Indices...>,
                                                       const Arguments&...   in_arguments);
            };
        }
    }
}

template<typename Traits, typename ReturnType, typename... Arguments, APIInterceptor::APIFunction function, typename OriginalFunction>
template<size_t... Indices>
typename Interception::Hooks::Common::GenericHook<Traits, ReturnType (__stdcall*)(Arguments...), function, OriginalFunction>::HeadArray
Interception::Hooks::Common::GenericHook<Traits, ReturnType (__stdcall*)(Arguments...), function, OriginalFunction>::create_post_arguments(const ArgumentArray&  in_pre_argument_array,
                                                                                                                                         const bool&           in_is_pre_argument_valid,
                                                                                                                                         std::index_sequence<Indices...>,
                                                                                                                                         const Arguments&...   in_arguments)
{
    return {{Traits::template ArgumentCapture<Arguments>::create_post_argument(in_arguments,
                                                                               in_pre_argument_array.at(Indices),
                                                                               in_is_pre_argument_valid)...}};
}

template<typename Traits, typename ReturnType, typename... Arguments, APIInterceptor::APIFunction function, typename OriginalFunction>
ReturnType __stdcall Interception::Hooks::Common::GenericHook<Traits, ReturnType (__stdcall*)(Arguments...), function, OriginalFunction>::invoke(Arguments... in_arguments)
{
    typedef ReturnType (__stdcall* OriginalFunctionPtr)(Arguments...);

    const uint32_t                          n_arguments                     = static_cast<uint32_t>(sizeof...(Arguments) + Policy::n_extra_arguments);
    void*                                   post_callback_function_argument = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_function_ptr      = nullptr;
    void*                                   pre_callback_function_argument  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_function_ptr       = nullptr;
    HookResult<ReturnType>                  result;
    bool                                    should_pass_through             = true;
    ArgumentArray                           pre_argument_array;
    bool                                    is_pre_argument_valid           = false;
    APIInterceptor::Tracker                 tracker;

    OriginalFunctionPtr original_function_ptr = reinterpret_cast<OriginalFunctionPtr>(OriginalFunction::get_ptr(in_arguments...) );

    if (tracker.is_top_level_api_call() )
    {
        if (APIInterceptor::get_pre_callback_for_function(function,
                                                         &pre_callback_function_ptr,
                                                         &pre_callback_function_argument) )
        {
            const HeadArray head_argument_array = {{Traits::template ArgumentCapture<Arguments>::create_pre_argument(in_arguments)...}};

            std::copy(head_argument_array.begin(),
                      head_argument_array.end  (),
                      pre_argument_array.begin() );

            Policy::create_extra_arguments(pre_argument_array.data() + sizeof...(Arguments),
                                           in_arguments...);

            is_pre_argument_valid = true;

            pre_callback_function_ptr(function,
                                      n_arguments,
                                      pre_argument_array.data(),
                                      pre_callback_function_argument,
                                     &should_pass_through);
        }
    }

    /* A callback may have the call not made; the caller of the hook gets a default result then. */
    AI_ASSERT(original_function_ptr != nullptr);

    if (Traits::is_frame_boundary(function) )
    {
        APIInterceptor::g_logger_ptr->on_frame_presented();
    }

    if (should_pass_through &&
        original_function_ptr != nullptr)
    {
        /* What the callbacks of the interceptor call on the device is not for a modifier to change. */
        if (tracker.is_top_level_api_call() )
        {
            Policy::on_call_starting(in_arguments...);
        }

        result.call(original_function_ptr,
                    in_arguments...);

        /* The runtime may have taken the hooks out of the vtable while the call was made; the next call must be seen. */
        if (Traits::repairs_vtables)
        {
            OriginalFunction::repair_after_call(in_arguments...);
        }
    }

    /* Hook the interfaces handed out by the call. */
    if (result.is_success() )
    {
        const int patched_dummy_i32vec[] = {0, (Traits::template ObjectPatcher<Arguments>::patch(in_arguments), 0)...};

        (void) patched_dummy_i32vec;
    }

    Policy::on_call_finished(result.is_success(),
                             in_arguments...);

    if (tracker.is_top_level_api_call() )
    {
        if (APIInterceptor::get_post_callback_for_function(function,
                                                          &post_callback_function_ptr,
                                                          &post_callback_function_argument) )
        {
            ArgumentArray   argument_array      = pre_argument_array; /* the extra arguments are the pre-call ones */
            const HeadArray head_argument_array = create_post_arguments(pre_argument_array,
                                                                        is_pre_argument_valid,
                                                                        std::index_sequence_for<Arguments...>(),
                                                                        in_arguments...);
            const auto      result_argument     = result.template create_argument<typename Traits::template ArgumentCapture<ReturnType> >();

            std::copy(head_argument_array.begin(),
                      head_argument_array.end  (),
                      argument_array.begin() );

            post_callback_function_ptr(function,
                                       post_callback_function_argument,
                                       n_arguments,
                                       argument_array.data(),
                                      &result_argument);
        }
    }

    return result.get();
}

#endif /* HOOKS_COMMON_GENERIC_HOOK_H */
