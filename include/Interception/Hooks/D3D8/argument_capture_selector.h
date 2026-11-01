/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * What is stored for an argument, by its category (see D3D8Utils/types.h). The post-call argument may reuse the pre-call
 * one, so that unchanged data is stored once.
 */
#ifndef D3D8_ARGUMENT_CAPTURE_SELECTOR_H
#define D3D8_ARGUMENT_CAPTURE_SELECTOR_H

#include "Interception/Hooks/D3D8/argument_factory.h"
#include "Interception/Core/D3D8Utils/types.h"

namespace D3D8
{
    template<typename T, Utils::ArgumentCategory category>
    struct ArgumentCaptureSelector;

    template<typename T>
    struct ArgumentCaptureSelector<T, Utils::ArgumentCategory::CONST_STRUCT>
    {
        typedef typename Utils::PointeeOf<T>::type StructType;

        static APIInterceptor::APIFunctionArgument create_post_argument(const T&                                   in_value,
                                                                        const APIInterceptor::APIFunctionArgument& in_pre_argument,
                                                                        const bool&                                in_is_pre_argument_valid);
        static APIInterceptor::APIFunctionArgument create_pre_argument (const T&                                   in_value);
    };

    template<typename T>
    struct ArgumentCaptureSelector<T, Utils::ArgumentCategory::GUID>
    {
        static APIInterceptor::APIFunctionArgument create_post_argument(const T&                                   in_value,
                                                                        const APIInterceptor::APIFunctionArgument& in_pre_argument,
                                                                        const bool&                                in_is_pre_argument_valid);
        static APIInterceptor::APIFunctionArgument create_pre_argument (const T&                                   in_value);
    };

    template<typename T>
    struct ArgumentCaptureSelector<T, Utils::ArgumentCategory::MUTABLE_STRUCT>
    {
        typedef typename Utils::PointeeOf<T>::type StructType;

        static APIInterceptor::APIFunctionArgument create_post_argument(const T&                                   in_value,
                                                                        const APIInterceptor::APIFunctionArgument& in_pre_argument,
                                                                        const bool&                                in_is_pre_argument_valid);
        static APIInterceptor::APIFunctionArgument create_pre_argument (const T&                                   in_value);
    };

    template<typename T>
    struct ArgumentCaptureSelector<T, Utils::ArgumentCategory::OBJECT>
    {
        static APIInterceptor::APIFunctionArgument create_post_argument(const T&                                   in_value,
                                                                        const APIInterceptor::APIFunctionArgument& in_pre_argument,
                                                                        const bool&                                in_is_pre_argument_valid);
        static APIInterceptor::APIFunctionArgument create_pre_argument (const T&                                   in_value);
    };

    template<typename T>
    struct ArgumentCaptureSelector<T, Utils::ArgumentCategory::OBJECT_OUT>
    {
        static APIInterceptor::APIFunctionArgument create_post_argument(const T&                                   in_value,
                                                                        const APIInterceptor::APIFunctionArgument& in_pre_argument,
                                                                        const bool&                                in_is_pre_argument_valid);
        static APIInterceptor::APIFunctionArgument create_pre_argument (const T&                                   in_value);
    };

    /* The pointer is captured as the one of an interface: before the call, the address; after it, the value written. */
    template<typename T>
    struct ArgumentCaptureSelector<T, Utils::ArgumentCategory::POINTER_OUT> : public ArgumentCaptureSelector<T, Utils::ArgumentCategory::OBJECT_OUT>
    {
        /* Stub */
    };

    template<typename T>
    struct ArgumentCaptureSelector<T, Utils::ArgumentCategory::SCALAR>
    {
        typedef typename ScalarConversion<T>::type ScalarType;

        static APIInterceptor::APIFunctionArgument create_post_argument(const T&                                   in_value,
                                                                        const APIInterceptor::APIFunctionArgument& in_pre_argument,
                                                                        const bool&                                in_is_pre_argument_valid);
        static APIInterceptor::APIFunctionArgument create_pre_argument (const T&                                   in_value);
    };

    template<typename T>
    struct ArgumentCaptureSelector<T, Utils::ArgumentCategory::SCALAR_OUT>
    {
        static APIInterceptor::APIFunctionArgument create_post_argument(const T&                                   in_value,
                                                                        const APIInterceptor::APIFunctionArgument& in_pre_argument,
                                                                        const bool&                                in_is_pre_argument_valid);
        static APIInterceptor::APIFunctionArgument create_pre_argument (const T&                                   in_value);
    };
}

template<typename T>
APIInterceptor::APIFunctionArgument D3D8::ArgumentCaptureSelector<T, D3D8::Utils::ArgumentCategory::CONST_STRUCT>::create_post_argument(const T&                                   in_value,
                                                                                                                                       const APIInterceptor::APIFunctionArgument& in_pre_argument,
                                                                                                                                       const bool&                                in_is_pre_argument_valid)
{
    return (in_is_pre_argument_valid) ? in_pre_argument
                                      : create_pre_argument(in_value);
}

template<typename T>
APIInterceptor::APIFunctionArgument D3D8::ArgumentCaptureSelector<T, D3D8::Utils::ArgumentCategory::CONST_STRUCT>::create_pre_argument(const T& in_value)
{
    return ArgumentFactory::create_chunk(in_value,
                                         static_cast<uint32_t>(sizeof(StructType) ));
}

template<typename T>
APIInterceptor::APIFunctionArgument D3D8::ArgumentCaptureSelector<T, D3D8::Utils::ArgumentCategory::GUID>::create_post_argument(const T&                                   in_value,
                                                                                                                                const APIInterceptor::APIFunctionArgument& in_pre_argument,
                                                                                                                                const bool&                                in_is_pre_argument_valid)
{
    return (in_is_pre_argument_valid) ? in_pre_argument
                                      : create_pre_argument(in_value);
}

template<typename T>
APIInterceptor::APIFunctionArgument D3D8::ArgumentCaptureSelector<T, D3D8::Utils::ArgumentCategory::GUID>::create_pre_argument(const T& in_value)
{
    return ArgumentFactory::create_chunk(&in_value,
                                         static_cast<uint32_t>(sizeof(GUID) ));
}

template<typename T>
APIInterceptor::APIFunctionArgument D3D8::ArgumentCaptureSelector<T, D3D8::Utils::ArgumentCategory::MUTABLE_STRUCT>::create_post_argument(const T&                                   in_value,
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
APIInterceptor::APIFunctionArgument D3D8::ArgumentCaptureSelector<T, D3D8::Utils::ArgumentCategory::MUTABLE_STRUCT>::create_pre_argument(const T& in_value)
{
    const void* const value_ptr = in_value;

    return (Utils::StructTraits<StructType>::is_input_output) ? ArgumentFactory::create_chunk(in_value,
                                                                                              static_cast<uint32_t>(sizeof(StructType) ))
                                                              : ArgumentFactory::create_scalar(value_ptr);
}

template<typename T>
APIInterceptor::APIFunctionArgument D3D8::ArgumentCaptureSelector<T, D3D8::Utils::ArgumentCategory::OBJECT>::create_post_argument(const T&                                   in_value,
                                                                                                                                  const APIInterceptor::APIFunctionArgument& in_pre_argument,
                                                                                                                                  const bool&                                in_is_pre_argument_valid)
{
    (void) in_pre_argument;
    (void) in_is_pre_argument_valid;

    return create_pre_argument(in_value);
}

template<typename T>
APIInterceptor::APIFunctionArgument D3D8::ArgumentCaptureSelector<T, D3D8::Utils::ArgumentCategory::OBJECT>::create_pre_argument(const T& in_value)
{
    const void* const value_ptr = in_value;

    return ArgumentFactory::create_scalar(value_ptr);
}

template<typename T>
APIInterceptor::APIFunctionArgument D3D8::ArgumentCaptureSelector<T, D3D8::Utils::ArgumentCategory::OBJECT_OUT>::create_post_argument(const T&                                   in_value,
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
APIInterceptor::APIFunctionArgument D3D8::ArgumentCaptureSelector<T, D3D8::Utils::ArgumentCategory::OBJECT_OUT>::create_pre_argument(const T& in_value)
{
    const void* const value_ptr = in_value;

    return ArgumentFactory::create_scalar(value_ptr);
}

template<typename T>
APIInterceptor::APIFunctionArgument D3D8::ArgumentCaptureSelector<T, D3D8::Utils::ArgumentCategory::SCALAR>::create_post_argument(const T&                                   in_value,
                                                                                                                                 const APIInterceptor::APIFunctionArgument& in_pre_argument,
                                                                                                                                 const bool&                                in_is_pre_argument_valid)
{
    (void) in_pre_argument;
    (void) in_is_pre_argument_valid;

    return create_pre_argument(in_value);
}

template<typename T>
APIInterceptor::APIFunctionArgument D3D8::ArgumentCaptureSelector<T, D3D8::Utils::ArgumentCategory::SCALAR>::create_pre_argument(const T& in_value)
{
    const ScalarType scalar_value = static_cast<ScalarType>(in_value);

    return ArgumentFactory::create_scalar(scalar_value);
}

template<typename T>
APIInterceptor::APIFunctionArgument D3D8::ArgumentCaptureSelector<T, D3D8::Utils::ArgumentCategory::SCALAR_OUT>::create_post_argument(const T&                                   in_value,
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
APIInterceptor::APIFunctionArgument D3D8::ArgumentCaptureSelector<T, D3D8::Utils::ArgumentCategory::SCALAR_OUT>::create_pre_argument(const T& in_value)
{
    const void* const value_ptr = in_value;

    return ArgumentFactory::create_scalar(value_ptr);
}

#endif /* D3D8_ARGUMENT_CAPTURE_SELECTOR_H */
