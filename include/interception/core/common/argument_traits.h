/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * What an argument or a returned value of a method of a COM-based API means, from its type: the kind of value, and the kind of
 * object it refers to. The API tells how to read its types in its traits type, which has:
 *   ValueKind                  the enum of the kinds of values of the API (with GUID, OBJECT and OBJECT_OUT)
 *   ObjectType                 the enum of the kinds of objects of the API (with NONE)
 *   ArgumentCategoryOf<T>      how an argument is captured (see Hooks/common/types.h)
 *   InterfaceTraits<I>         the object_type of an interface
 *   StructTraits<S>            the kind of a structure
 *   ValueKindOf<T>             the kind of a scalar
 */
#ifndef CORE_COMMON_ARGUMENT_TRAITS_H
#define CORE_COMMON_ARGUMENT_TRAITS_H

#include "interception/hooks/common/types.h"

namespace Interception
{
    namespace Core
    {
        namespace Common
        {
            template<typename ApiTraits, typename T>
            struct ArgumentTraits
            {
                typedef typename ApiTraits::ValueKind                                             ValueKind;
                typedef typename ApiTraits::ObjectType                                            ObjectType;
                typedef typename Interception::Hooks::Common::PointeeOf<T>::type                  PointeeType;
                typedef typename Interception::Hooks::Common::PointeeOf<PointeeType>::type       PointeePointeeType;

                static const Interception::Hooks::Common::ArgumentCategory category = ApiTraits::template ArgumentCategoryOf<T>::value;

                static const ValueKind kind =
                    (category == Interception::Hooks::Common::ArgumentCategory::CONST_STRUCT)   ? ApiTraits::template StructTraits<PointeeType>::kind
                  : (category == Interception::Hooks::Common::ArgumentCategory::GUID)           ? ValueKind::GUID
                  : (category == Interception::Hooks::Common::ArgumentCategory::MUTABLE_STRUCT) ? ApiTraits::template StructTraits<PointeeType>::kind
                  : (category == Interception::Hooks::Common::ArgumentCategory::OBJECT)         ? ValueKind::OBJECT
                  : (category == Interception::Hooks::Common::ArgumentCategory::OBJECT_OUT)     ? ValueKind::OBJECT_OUT
                  : (category == Interception::Hooks::Common::ArgumentCategory::SCALAR_OUT)     ? ApiTraits::template ValueKindOf<PointeeType>::kind
                                                                                                : ApiTraits::template ValueKindOf<T>::kind;

                static const ObjectType object_type =
                    (category == Interception::Hooks::Common::ArgumentCategory::OBJECT)     ? ApiTraits::template InterfaceTraits<PointeeType>::object_type
                  : (category == Interception::Hooks::Common::ArgumentCategory::OBJECT_OUT) ? ApiTraits::template InterfaceTraits<PointeePointeeType>::object_type
                                                                                            : ObjectType::NONE;
            };
        }
    }
}

#endif /* CORE_COMMON_ARGUMENT_TRAITS_H */
