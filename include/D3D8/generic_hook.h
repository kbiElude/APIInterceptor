/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Hook of a D3D8 method, generated from the method's function pointer type. It reports the call to the registered
 * callbacks, forwards it to the original method, and hooks the interfaces which the call has handed out.
 */
#ifndef D3D8_GENERIC_HOOK_H
#define D3D8_GENERIC_HOOK_H

#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "D3D8/argument_capture.h"
#include "D3D8/hook_policy.h"
#include "D3D8/hook_result.h"
#include "D3D8/hook_table.h"
#include "D3D8/object_patcher.h"
#include "D3D8/vtable_registry.h"
#include <algorithm>
#include <array>
#include <utility>

namespace D3D8
{
    template<typename FunctionPtr, APIInterceptor::APIFunction function, uint32_t vtable_index>
    struct GenericHook;

    template<typename ReturnType, typename... Arguments, APIInterceptor::APIFunction function, uint32_t vtable_index>
    struct GenericHook<ReturnType (__stdcall*)(Arguments...), function, vtable_index>
    {
        typedef std::array<APIInterceptor::APIFunctionArgument, sizeof...(Arguments) + HookPolicy<function>::n_extra_arguments> ArgumentArray;
        typedef std::array<APIInterceptor::APIFunctionArgument, sizeof...(Arguments)>                                           HeadArray;

        static ReturnType __stdcall invoke(Arguments... in_arguments);

    private:
        template<size_t... Indices>
        static HeadArray create_post_arguments(const ArgumentArray&  in_pre_argument_array,
                                               const bool&           in_is_pre_argument_valid,
                                               std::index_sequence<Indices...>,
                                               const Arguments&...   in_arguments);

        template<typename Self, typename... Rest>
        static const void* get_object_ptr(const Self& in_self,
                                          const Rest&...);
    };
}

template<typename ReturnType, typename... Arguments, APIInterceptor::APIFunction function, uint32_t vtable_index>
template<size_t... Indices>
typename D3D8::GenericHook<ReturnType (__stdcall*)(Arguments...), function, vtable_index>::HeadArray
D3D8::GenericHook<ReturnType (__stdcall*)(Arguments...), function, vtable_index>::create_post_arguments(const ArgumentArray&  in_pre_argument_array,
                                                                                                        const bool&           in_is_pre_argument_valid,
                                                                                                        std::index_sequence<Indices...>,
                                                                                                        const Arguments&...   in_arguments)
{
    return {{ArgumentCapture<Arguments>::create_post_argument(in_arguments,
                                                              in_pre_argument_array.at(Indices),
                                                              in_is_pre_argument_valid)...}};
}

template<typename ReturnType, typename... Arguments, APIInterceptor::APIFunction function, uint32_t vtable_index>
template<typename Self, typename... Rest>
const void* D3D8::GenericHook<ReturnType (__stdcall*)(Arguments...), function, vtable_index>::get_object_ptr(const Self& in_self,
                                                                                                             const Rest&...)
{
    return in_self;
}

template<typename ReturnType, typename... Arguments, APIInterceptor::APIFunction function, uint32_t vtable_index>
ReturnType __stdcall D3D8::GenericHook<ReturnType (__stdcall*)(Arguments...), function, vtable_index>::invoke(Arguments... in_arguments)
{
    typedef ReturnType (__stdcall* OriginalFunctionPtr)(Arguments...);

    const uint32_t                          n_arguments                     = static_cast<uint32_t>(sizeof...(Arguments) + HookPolicy<function>::n_extra_arguments);
    void*                                   post_callback_function_argument = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_function_ptr      = nullptr;
    void*                                   pre_callback_function_argument  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_function_ptr       = nullptr;
    HookResult<ReturnType>                  result;
    bool                                    should_pass_through             = true;
    ArgumentArray                           pre_argument_array;
    bool                                    is_pre_argument_valid           = false;
    APIInterceptor::Tracker                 tracker;

    OriginalFunctionPtr original_function_ptr = reinterpret_cast<OriginalFunctionPtr>(
                                                    VTableRegistry::get_ptr()->get_original_function_ptr(get_object_ptr(in_arguments...),
                                                                                                         vtable_index) );

    if (tracker.is_top_level_api_call() )
    {
        if (APIInterceptor::get_pre_callback_for_function(function,
                                                         &pre_callback_function_ptr,
                                                         &pre_callback_function_argument) )
        {
            const HeadArray head_argument_array = {{ArgumentCapture<Arguments>::create_pre_argument(in_arguments)...}};

            std::copy(head_argument_array.begin(),
                      head_argument_array.end  (),
                      pre_argument_array.begin() );

            HookPolicy<function>::create_extra_arguments(pre_argument_array.data() + sizeof...(Arguments),
                                                         in_arguments...);

            is_pre_argument_valid = true;

            pre_callback_function_ptr(function,
                                      n_arguments,
                                      pre_argument_array.data(),
                                      pre_callback_function_argument,
                                     &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);
    AI_ASSERT(original_function_ptr != nullptr);

    /* The device's Present call ends the frame. */
    if (function == APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_PRESENT)
    {
        APIInterceptor::g_logger_ptr->on_frame_presented();
    }

    if (should_pass_through &&
        original_function_ptr != nullptr)
    {
        result.call(original_function_ptr,
                    in_arguments...);
    }

    /* Hook the interfaces handed out by the call. */
    if (result.is_success() )
    {
        const int patched_dummy_i32vec[] = {0, (ObjectPatcher<Arguments>::patch(in_arguments), 0)...};

        (void) patched_dummy_i32vec;
    }

    HookPolicy<function>::on_call_finished(result.is_success(),
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
            const auto      result_argument     = result.create_argument();

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

#endif /* D3D8_GENERIC_HOOK_H */
