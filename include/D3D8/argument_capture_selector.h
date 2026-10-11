/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * What is stored for an argument, by its category (see D3D8Utils/types.h). The post-call argument may reuse the pre-call
 * one, so that unchanged data is stored once.
 */
#ifndef D3D8_ARGUMENT_CAPTURE_SELECTOR_H
#define D3D8_ARGUMENT_CAPTURE_SELECTOR_H

#include "D3D8/argument_factory.h"
#include "D3D8Utils/types.h"

namespace D3D8
{
    template<typename T, Utils::ArgumentCategory category>
    struct ArgumentCaptureSelector;

    template<typename T>
    struct ArgumentCaptureSelector<T, Utils::ArgumentCategory::ConstStruct>
    {
        typedef typename Utils::PointeeOf<T>::type StructType;

        static APIInterceptor::APIFunctionArgument create_post_argument(const T&                                   in_value,
                                                                        const APIInterceptor::APIFunctionArgument& in_pre_argument,
                                                                        const bool&                                in_is_pre_argument_valid);
        static APIInterceptor::APIFunctionArgument create_pre_argument (const T&                                   in_value);
    };

    template<typename T>
    struct ArgumentCaptureSelector<T, Utils::ArgumentCategory::Guid>
    {
        static APIInterceptor::APIFunctionArgument create_post_argument(const T&                                   in_value,
                                                                        const APIInterceptor::APIFunctionArgument& in_pre_argument,
                                                                        const bool&                                in_is_pre_argument_valid);
        static APIInterceptor::APIFunctionArgument create_pre_argument (const T&                                   in_value);
    };

    template<typename T>
    struct ArgumentCaptureSelector<T, Utils::ArgumentCategory::MutableStruct>
    {
        typedef typename Utils::PointeeOf<T>::type StructType;

        static APIInterceptor::APIFunctionArgument create_post_argument(const T&                                   in_value,
                                                                        const APIInterceptor::APIFunctionArgument& in_pre_argument,
                                                                        const bool&                                in_is_pre_argument_valid);
        static APIInterceptor::APIFunctionArgument create_pre_argument (const T&                                   in_value);
    };

    template<typename T>
    struct ArgumentCaptureSelector<T, Utils::ArgumentCategory::Object>
    {
        static APIInterceptor::APIFunctionArgument create_post_argument(const T&                                   in_value,
                                                                        const APIInterceptor::APIFunctionArgument& in_pre_argument,
                                                                        const bool&                                in_is_pre_argument_valid);
        static APIInterceptor::APIFunctionArgument create_pre_argument (const T&                                   in_value);
    };

    template<typename T>
    struct ArgumentCaptureSelector<T, Utils::ArgumentCategory::ObjectOut>
    {
        static APIInterceptor::APIFunctionArgument create_post_argument(const T&                                   in_value,
                                                                        const APIInterceptor::APIFunctionArgument& in_pre_argument,
                                                                        const bool&                                in_is_pre_argument_valid);
        static APIInterceptor::APIFunctionArgument create_pre_argument (const T&                                   in_value);
    };

    template<typename T>
    struct ArgumentCaptureSelector<T, Utils::ArgumentCategory::Scalar>
    {
        typedef typename ScalarConversion<T>::type ScalarType;

        static APIInterceptor::APIFunctionArgument create_post_argument(const T&                                   in_value,
                                                                        const APIInterceptor::APIFunctionArgument& in_pre_argument,
                                                                        const bool&                                in_is_pre_argument_valid);
        static APIInterceptor::APIFunctionArgument create_pre_argument (const T&                                   in_value);
    };

    template<typename T>
    struct ArgumentCaptureSelector<T, Utils::ArgumentCategory::ScalarOut>
    {
        static APIInterceptor::APIFunctionArgument create_post_argument(const T&                                   in_value,
                                                                        const APIInterceptor::APIFunctionArgument& in_pre_argument,
                                                                        const bool&                                in_is_pre_argument_valid);
        static APIInterceptor::APIFunctionArgument create_pre_argument (const T&                                   in_value);
    };
}

template<typename T>
APIInterceptor::APIFunctionArgument D3D8::ArgumentCaptureSelector<T, D3D8::Utils::ArgumentCategory::ConstStruct>::create_post_argument(const T&                                   in_value,
                                                                                                                                       const APIInterceptor::APIFunctionArgument& in_pre_argument,
                                                                                                                                       const bool&                                in_is_pre_argument_valid)
{
    return (in_is_pre_argument_valid) ? in_pre_argument
                                      : create_pre_argument(in_value);
}

template<typename T>
APIInterceptor::APIFunctionArgument D3D8::ArgumentCaptureSelector<T, D3D8::Utils::ArgumentCategory::ConstStruct>::create_pre_argument(const T& in_value)
{
    return ArgumentFactory::create_chunk(in_value,
                                         static_cast<uint32_t>(sizeof(StructType) ));
}

template<typename T>
APIInterceptor::APIFunctionArgument D3D8::ArgumentCaptureSelector<T, D3D8::Utils::ArgumentCategory::Guid>::create_post_argument(const T&                                   in_value,
                                                                                                                                const APIInterceptor::APIFunctionArgument& in_pre_argument,
                                                                                                                                const bool&                                in_is_pre_argument_valid)
{
    return (in_is_pre_argument_valid) ? in_pre_argument
                                      : create_pre_argument(in_value);
}

template<typename T>
APIInterceptor::APIFunctionArgument D3D8::ArgumentCaptureSelector<T, D3D8::Utils::ArgumentCategory::Guid>::create_pre_argument(const T& in_value)
{
    return ArgumentFactory::create_chunk(&in_value,
                                         static_cast<uint32_t>(sizeof(GUID) ));
}

template<typename T>
APIInterceptor::APIFunctionArgument D3D8::ArgumentCaptureSelector<T, D3D8::Utils::ArgumentCategory::MutableStruct>::create_post_argument(const T&                                   in_value,
                                                                                                                                         const APIInterceptor::APIFunctionArgument& in_pre_argument,
                                                                                                                                         const bool&                                in_is_pre_argument_valid)
{
    (void) in_pre_argument;
    (void) in_is_pre_argument_valid;

    return ArgumentFactory::create_chunk(in_value,
                                         static_cast<uint32_t>(sizeof(StructType) ));
}

/* Output structures hold nothing meaningful before the call. */
template<typename T>
APIInterceptor::APIFunctionArgument D3D8::ArgumentCaptureSelector<T, D3D8::Utils::ArgumentCategory::MutableStruct>::create_pre_argument(const T& in_value)
{
    const void* const value_ptr = in_value;

    return (Utils::StructTraits<StructType>::is_input_output) ? ArgumentFactory::create_chunk(in_value,
                                                                                              static_cast<uint32_t>(sizeof(StructType) ))
                                                              : ArgumentFactory::create_scalar(value_ptr);
}

template<typename T>
APIInterceptor::APIFunctionArgument D3D8::ArgumentCaptureSelector<T, D3D8::Utils::ArgumentCategory::Object>::create_post_argument(const T&                                   in_value,
                                                                                                                                  const APIInterceptor::APIFunctionArgument& in_pre_argument,
                                                                                                                                  const bool&                                in_is_pre_argument_valid)
{
    (void) in_pre_argument;
    (void) in_is_pre_argument_valid;

    return create_pre_argument(in_value);
}

template<typename T>
APIInterceptor::APIFunctionArgument D3D8::ArgumentCaptureSelector<T, D3D8::Utils::ArgumentCategory::Object>::create_pre_argument(const T& in_value)
{
    const void* const value_ptr = in_value;

    return ArgumentFactory::create_scalar(value_ptr);
}

template<typename T>
APIInterceptor::APIFunctionArgument D3D8::ArgumentCaptureSelector<T, D3D8::Utils::ArgumentCategory::ObjectOut>::create_post_argument(const T&                                   in_value,
                                                                                                                                     const APIInterceptor::APIFunctionArgument& in_pre_argument,
                                                                                                                                     const bool&                                in_is_pre_argument_valid)
{
    const void* const object_ptr = (in_value != nullptr) ? *in_value
                                                         : nullptr;

    (void) in_pre_argument;
    (void) in_is_pre_argument_valid;

    return ArgumentFactory::create_scalar(object_ptr);
}

template<typename T>
APIInterceptor::APIFunctionArgument D3D8::ArgumentCaptureSelector<T, D3D8::Utils::ArgumentCategory::ObjectOut>::create_pre_argument(const T& in_value)
{
    const void* const value_ptr = in_value;

    return ArgumentFactory::create_scalar(value_ptr);
}

template<typename T>
APIInterceptor::APIFunctionArgument D3D8::ArgumentCaptureSelector<T, D3D8::Utils::ArgumentCategory::Scalar>::create_post_argument(const T&                                   in_value,
                                                                                                                                 const APIInterceptor::APIFunctionArgument& in_pre_argument,
                                                                                                                                 const bool&                                in_is_pre_argument_valid)
{
    (void) in_pre_argument;
    (void) in_is_pre_argument_valid;

    return create_pre_argument(in_value);
}

template<typename T>
APIInterceptor::APIFunctionArgument D3D8::ArgumentCaptureSelector<T, D3D8::Utils::ArgumentCategory::Scalar>::create_pre_argument(const T& in_value)
{
    const ScalarType scalar_value = static_cast<ScalarType>(in_value);

    return ArgumentFactory::create_scalar(scalar_value);
}

template<typename T>
APIInterceptor::APIFunctionArgument D3D8::ArgumentCaptureSelector<T, D3D8::Utils::ArgumentCategory::ScalarOut>::create_post_argument(const T&                                   in_value,
                                                                                                                                    const APIInterceptor::APIFunctionArgument& in_pre_argument,
                                                                                                                                    const bool&                                in_is_pre_argument_valid)
{
    const void* const value_ptr = in_value;

    (void) in_pre_argument;
    (void) in_is_pre_argument_valid;

    return (in_value != nullptr) ? ArgumentFactory::create_scalar(*in_value)
                                 : ArgumentFactory::create_scalar(value_ptr);
}

template<typename T>
APIInterceptor::APIFunctionArgument D3D8::ArgumentCaptureSelector<T, D3D8::Utils::ArgumentCategory::ScalarOut>::create_pre_argument(const T& in_value)
{
    const void* const value_ptr = in_value;

    return ArgumentFactory::create_scalar(value_ptr);
}

#endif /* D3D8_ARGUMENT_CAPTURE_SELECTOR_H */
