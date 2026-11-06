/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * What is stored for an argument, by its category (see common/types.h). The post-call argument may reuse the pre-call
 * one, so that unchanged data is stored once.
 *
 * The traits type of the API has StructTraits<S>, which tells if a structure is captured as input/output (is_input_output).
 */
#ifndef HOOKS_COMMON_ARGUMENT_CAPTURE_SELECTOR_H
#define HOOKS_COMMON_ARGUMENT_CAPTURE_SELECTOR_H

#include "interception/hooks/common/argument_factory.h"
#include "interception/hooks/common/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace Common
        {
            template<typename Traits, typename T, ArgumentCategory category>
            struct ArgumentCaptureSelector;

            template<typename Traits, typename T>
            struct ArgumentCaptureSelector<Traits, T, ArgumentCategory::CONST_STRUCT>
            {
                typedef typename PointeeOf<T>::type StructType;

                static APIInterceptor::APIFunctionArgument create_post_argument(const T&                                   in_value,
                                                                                const APIInterceptor::APIFunctionArgument& in_pre_argument,
                                                                                const bool&                                in_is_pre_argument_valid);
                static APIInterceptor::APIFunctionArgument create_pre_argument (const T&                                   in_value);
            };

            template<typename Traits, typename T>
            struct ArgumentCaptureSelector<Traits, T, ArgumentCategory::GUID>
            {
                static APIInterceptor::APIFunctionArgument create_post_argument(const T&                                   in_value,
                                                                                const APIInterceptor::APIFunctionArgument& in_pre_argument,
                                                                                const bool&                                in_is_pre_argument_valid);
                static APIInterceptor::APIFunctionArgument create_pre_argument (const T&                                   in_value);
            };

            template<typename Traits, typename T>
            struct ArgumentCaptureSelector<Traits, T, ArgumentCategory::MUTABLE_STRUCT>
            {
                typedef typename PointeeOf<T>::type StructType;

                static APIInterceptor::APIFunctionArgument create_post_argument(const T&                                   in_value,
                                                                                const APIInterceptor::APIFunctionArgument& in_pre_argument,
                                                                                const bool&                                in_is_pre_argument_valid);
                static APIInterceptor::APIFunctionArgument create_pre_argument (const T&                                   in_value);
            };

            template<typename Traits, typename T>
            struct ArgumentCaptureSelector<Traits, T, ArgumentCategory::OBJECT>
            {
                static APIInterceptor::APIFunctionArgument create_post_argument(const T&                                   in_value,
                                                                                const APIInterceptor::APIFunctionArgument& in_pre_argument,
                                                                                const bool&                                in_is_pre_argument_valid);
                static APIInterceptor::APIFunctionArgument create_pre_argument (const T&                                   in_value);
            };

            template<typename Traits, typename T>
            struct ArgumentCaptureSelector<Traits, T, ArgumentCategory::OBJECT_OUT>
            {
                static APIInterceptor::APIFunctionArgument create_post_argument(const T&                                   in_value,
                                                                                const APIInterceptor::APIFunctionArgument& in_pre_argument,
                                                                                const bool&                                in_is_pre_argument_valid);
                static APIInterceptor::APIFunctionArgument create_pre_argument (const T&                                   in_value);
            };

            /* The pointer is captured as the one of an interface: before the call, the address; after it, the value written. */
            template<typename Traits, typename T>
            struct ArgumentCaptureSelector<Traits, T, ArgumentCategory::POINTER_OUT> : public ArgumentCaptureSelector<Traits, T, ArgumentCategory::OBJECT_OUT>
            {
                /* Stub */
            };

            template<typename Traits, typename T>
            struct ArgumentCaptureSelector<Traits, T, ArgumentCategory::SCALAR>
            {
                typedef typename ScalarConversion<T>::type ScalarType;

                static APIInterceptor::APIFunctionArgument create_post_argument(const T&                                   in_value,
                                                                                const APIInterceptor::APIFunctionArgument& in_pre_argument,
                                                                                const bool&                                in_is_pre_argument_valid);
                static APIInterceptor::APIFunctionArgument create_pre_argument (const T&                                   in_value);
            };

            template<typename Traits, typename T>
            struct ArgumentCaptureSelector<Traits, T, ArgumentCategory::SCALAR_OUT>
            {
                static APIInterceptor::APIFunctionArgument create_post_argument(const T&                                   in_value,
                                                                                const APIInterceptor::APIFunctionArgument& in_pre_argument,
                                                                                const bool&                                in_is_pre_argument_valid);
                static APIInterceptor::APIFunctionArgument create_pre_argument (const T&                                   in_value);
            };
        }
    }
}

template<typename Traits, typename T>
APIInterceptor::APIFunctionArgument Interception::Hooks::Common::ArgumentCaptureSelector<Traits, T, Interception::Hooks::Common::ArgumentCategory::CONST_STRUCT>::create_post_argument(const T&                                   in_value,
                                                                                                                                                                                      const APIInterceptor::APIFunctionArgument& in_pre_argument,
                                                                                                                                                                                      const bool&                                in_is_pre_argument_valid)
{
    return (in_is_pre_argument_valid) ? in_pre_argument
                                      : create_pre_argument(in_value);
}

template<typename Traits, typename T>
APIInterceptor::APIFunctionArgument Interception::Hooks::Common::ArgumentCaptureSelector<Traits, T, Interception::Hooks::Common::ArgumentCategory::CONST_STRUCT>::create_pre_argument(const T& in_value)
{
    return ArgumentFactory::create_chunk(in_value,
                                         static_cast<uint32_t>(sizeof(StructType) ));
}

template<typename Traits, typename T>
APIInterceptor::APIFunctionArgument Interception::Hooks::Common::ArgumentCaptureSelector<Traits, T, Interception::Hooks::Common::ArgumentCategory::GUID>::create_post_argument(const T&                                   in_value,
                                                                                                                                                                               const APIInterceptor::APIFunctionArgument& in_pre_argument,
                                                                                                                                                                               const bool&                                in_is_pre_argument_valid)
{
    return (in_is_pre_argument_valid) ? in_pre_argument
                                      : create_pre_argument(in_value);
}

template<typename Traits, typename T>
APIInterceptor::APIFunctionArgument Interception::Hooks::Common::ArgumentCaptureSelector<Traits, T, Interception::Hooks::Common::ArgumentCategory::GUID>::create_pre_argument(const T& in_value)
{
    return ArgumentFactory::create_chunk(&in_value,
                                         static_cast<uint32_t>(sizeof(GUID) ));
}

template<typename Traits, typename T>
APIInterceptor::APIFunctionArgument Interception::Hooks::Common::ArgumentCaptureSelector<Traits, T, Interception::Hooks::Common::ArgumentCategory::MUTABLE_STRUCT>::create_post_argument(const T&                                   in_value,
                                                                                                                                                                                        const APIInterceptor::APIFunctionArgument& in_pre_argument,
                                                                                                                                                                                        const bool&                                in_is_pre_argument_valid)
{
    (void) in_pre_argument;
    (void) in_is_pre_argument_valid;

    return ArgumentFactory::create_chunk(in_value,
                                         static_cast<uint32_t>(sizeof(StructType) ));
}

/* Output structures hold nothing meaningful before the call. */
template<typename Traits, typename T>
APIInterceptor::APIFunctionArgument Interception::Hooks::Common::ArgumentCaptureSelector<Traits, T, Interception::Hooks::Common::ArgumentCategory::MUTABLE_STRUCT>::create_pre_argument(const T& in_value)
{
    const void* const value_ptr = in_value;

    return (Traits::template StructTraits<StructType>::is_input_output) ? ArgumentFactory::create_chunk(in_value,
                                                                                                        static_cast<uint32_t>(sizeof(StructType) ))
                                                                        : ArgumentFactory::create_scalar(value_ptr);
}

template<typename Traits, typename T>
APIInterceptor::APIFunctionArgument Interception::Hooks::Common::ArgumentCaptureSelector<Traits, T, Interception::Hooks::Common::ArgumentCategory::OBJECT>::create_post_argument(const T&                                   in_value,
                                                                                                                                                                                const APIInterceptor::APIFunctionArgument& in_pre_argument,
                                                                                                                                                                                const bool&                                in_is_pre_argument_valid)
{
    (void) in_pre_argument;
    (void) in_is_pre_argument_valid;

    return create_pre_argument(in_value);
}

template<typename Traits, typename T>
APIInterceptor::APIFunctionArgument Interception::Hooks::Common::ArgumentCaptureSelector<Traits, T, Interception::Hooks::Common::ArgumentCategory::OBJECT>::create_pre_argument(const T& in_value)
{
    const void* const value_ptr = in_value;

    return ArgumentFactory::create_scalar(value_ptr);
}

template<typename Traits, typename T>
APIInterceptor::APIFunctionArgument Interception::Hooks::Common::ArgumentCaptureSelector<Traits, T, Interception::Hooks::Common::ArgumentCategory::OBJECT_OUT>::create_post_argument(const T&                                   in_value,
                                                                                                                                                                                    const APIInterceptor::APIFunctionArgument& in_pre_argument,
                                                                                                                                                                                    const bool&                                in_is_pre_argument_valid)
{
    const void* const object_ptr = (in_value != nullptr) ? *in_value
                                                         : nullptr;

    (void) in_pre_argument;
    (void) in_is_pre_argument_valid;

    return ArgumentFactory::create_scalar(object_ptr);
}

template<typename Traits, typename T>
APIInterceptor::APIFunctionArgument Interception::Hooks::Common::ArgumentCaptureSelector<Traits, T, Interception::Hooks::Common::ArgumentCategory::OBJECT_OUT>::create_pre_argument(const T& in_value)
{
    const void* const value_ptr = in_value;

    return ArgumentFactory::create_scalar(value_ptr);
}

template<typename Traits, typename T>
APIInterceptor::APIFunctionArgument Interception::Hooks::Common::ArgumentCaptureSelector<Traits, T, Interception::Hooks::Common::ArgumentCategory::SCALAR>::create_post_argument(const T&                                   in_value,
                                                                                                                                                                                const APIInterceptor::APIFunctionArgument& in_pre_argument,
                                                                                                                                                                                const bool&                                in_is_pre_argument_valid)
{
    (void) in_pre_argument;
    (void) in_is_pre_argument_valid;

    return create_pre_argument(in_value);
}

template<typename Traits, typename T>
APIInterceptor::APIFunctionArgument Interception::Hooks::Common::ArgumentCaptureSelector<Traits, T, Interception::Hooks::Common::ArgumentCategory::SCALAR>::create_pre_argument(const T& in_value)
{
    const ScalarType scalar_value = static_cast<ScalarType>(in_value);

    return ArgumentFactory::create_scalar(scalar_value);
}

template<typename Traits, typename T>
APIInterceptor::APIFunctionArgument Interception::Hooks::Common::ArgumentCaptureSelector<Traits, T, Interception::Hooks::Common::ArgumentCategory::SCALAR_OUT>::create_post_argument(const T&                                   in_value,
                                                                                                                                                                                    const APIInterceptor::APIFunctionArgument& in_pre_argument,
                                                                                                                                                                                    const bool&                                in_is_pre_argument_valid)
{
    const void* const value_ptr = in_value;

    (void) in_pre_argument;
    (void) in_is_pre_argument_valid;

    return (in_value != nullptr) ? ArgumentFactory::create_scalar(*in_value)
                                 : ArgumentFactory::create_scalar(value_ptr);
}

template<typename Traits, typename T>
APIInterceptor::APIFunctionArgument Interception::Hooks::Common::ArgumentCaptureSelector<Traits, T, Interception::Hooks::Common::ArgumentCategory::SCALAR_OUT>::create_pre_argument(const T& in_value)
{
    const void* const value_ptr = in_value;

    return ArgumentFactory::create_scalar(value_ptr);
}

#endif /* HOOKS_COMMON_ARGUMENT_CAPTURE_SELECTOR_H */
