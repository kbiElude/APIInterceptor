/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef D3D8UTILS_ARGUMENT_TRAITS_H
#define D3D8UTILS_ARGUMENT_TRAITS_H

#include "Interception/Core/Common/argument_traits.h"
#include "Interception/Core/D3D8Utils/types.h"

namespace Interception
{
    namespace Core
    {
        namespace D3D8Utils
        {
            /* How the types of D3D8 are read (see Common/argument_traits.h). */
            struct ApiTraits
            {
                typedef Interception::Hooks::D3D8::ValueKind ValueKind;
                typedef D3D8Utils::ObjectType                ObjectType;

                template<typename T> using ArgumentCategoryOf = D3D8Utils::ArgumentCategoryOf<T>;
                template<typename T> using InterfaceTraits    = D3D8Utils::InterfaceTraits<T>;
                template<typename T> using StructTraits       = D3D8Utils::StructTraits<T>;
                template<typename T> using ValueKindOf        = D3D8Utils::ValueKindOf<T>;
            };

            /* Meaning of an argument or of a returned value (void is allowed), and the interface it refers to. */
            template<typename T>
            using ArgumentTraits = Interception::Core::Common::ArgumentTraits<ApiTraits, T>;
        }
    }
}

#endif /* D3D8UTILS_ARGUMENT_TRAITS_H */
