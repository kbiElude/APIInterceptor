/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef D3D7UTILS_SIGNATURE_INFO_H
#define D3D7UTILS_SIGNATURE_INFO_H

#include "Interception/Core/Common/signature_info.h"
#include "Interception/Core/D3D7Utils/argument_traits.h"
#include "Interception/Core/D3D7Utils/methods.h"

namespace Interception
{
    namespace Core
    {
        namespace D3D7Utils
        {
            /* What the description of a signature needs to know of D3D7 (see Common/signature_info.h). */
            struct SignatureTraits
            {
                typedef Interception::Hooks::D3D7::ArgumentInfo ArgumentInfo;

                template<typename T> using ArgumentTraits = D3D7Utils::ArgumentTraits<T>;

                static const char* get_object_type_name_ptr(const ObjectType& in_object_type)
                {
                    return D3D7Utils::get_object_type_name_ptr(in_object_type);
                }
            };

            template<typename FunctionPtr>
            using SignatureInfo = Interception::Core::Common::SignatureInfo<SignatureTraits, FunctionPtr>;
        }
    }
}

#endif /* D3D7UTILS_SIGNATURE_INFO_H */
