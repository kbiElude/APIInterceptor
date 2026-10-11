/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef D3D8UTILS_ARGUMENT_TRAITS_H
#define D3D8UTILS_ARGUMENT_TRAITS_H

#include "D3D8Utils/types.h"

namespace D3D8
{
    namespace Utils
    {
        /* Meaning of an argument or of a returned value (void is allowed), and the interface it refers to. */
        template<typename T>
        struct ArgumentTraits
        {
            typedef typename PointeeOf<T>::type                    PointeeType;
            typedef typename PointeeOf<PointeeType>::type          PointeePointeeType;

            static const ArgumentCategory category = ArgumentCategoryOf<T>::value;

            static const ValueKind kind =
                (category == ArgumentCategory::ConstStruct)   ? StructTraits<PointeeType>::kind
              : (category == ArgumentCategory::Guid)          ? ValueKind::Guid
              : (category == ArgumentCategory::MutableStruct) ? StructTraits<PointeeType>::kind
              : (category == ArgumentCategory::Object)        ? ValueKind::Object
              : (category == ArgumentCategory::ObjectOut)     ? ValueKind::ObjectOut
              : (category == ArgumentCategory::ScalarOut)     ? ValueKindOf<PointeeType>::kind
                                                              : ValueKindOf<T>::kind;

            static const ObjectType object_type =
                (category == ArgumentCategory::Object)    ? InterfaceTraits<PointeeType>::object_type
              : (category == ArgumentCategory::ObjectOut) ? InterfaceTraits<PointeePointeeType>::object_type
                                                          : ObjectType::None;
        };
    }
}

#endif /* D3D8UTILS_ARGUMENT_TRAITS_H */
