/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef D3D7UTILS_ARGUMENT_TRAITS_H
#define D3D7UTILS_ARGUMENT_TRAITS_H

#include "Interception/Core/Common/argument_traits.h"
#include "Interception/Core/D3D7Utils/types.h"

namespace Interception
{
    namespace Core
    {
        namespace D3D7Utils
        {
            /* How the types of D3D7 are read (see Common/argument_traits.h). */
            struct ApiTraits
            {
                typedef Interception::Hooks::D3D7::ValueKind ValueKind;
                typedef D3D7Utils::ObjectType                ObjectType;

                template<typename T> using ArgumentCategoryOf = D3D7Utils::ArgumentCategoryOf<T>;
                template<typename T> using InterfaceTraits    = D3D7Utils::InterfaceTraits<T>;
                template<typename T> using StructTraits       = D3D7Utils::StructTraits<T>;
                template<typename T> using ValueKindOf        = D3D7Utils::ValueKindOf<T>;
            };

            /* Meaning of an argument or of a returned value (void is allowed), and the interface it refers to. */
            template<typename T>
            using ArgumentTraits = Interception::Core::Common::ArgumentTraits<ApiTraits, T>;
        }
    }
}

#endif /* D3D7UTILS_ARGUMENT_TRAITS_H */
