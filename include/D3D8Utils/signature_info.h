/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Describes the arguments and the returned value of a D3D8 method, given its function pointer type.
 */
#ifndef D3D8UTILS_SIGNATURE_INFO_H
#define D3D8UTILS_SIGNATURE_INFO_H

#include "D3D8Utils/argument_traits.h"
#include "D3D8Utils/methods.h"
#include <vector>

namespace D3D8
{
    namespace Utils
    {
        template<typename FunctionPtr>
        struct SignatureInfo;

        template<typename ReturnType, typename... Arguments>
        struct SignatureInfo<ReturnType (__stdcall*)(Arguments...)>
        {
            static const std::vector<ArgumentInfo>& get_argument_info_vec();
            static ArgumentInfo                     get_return_info();
        };
    }
}

template<typename ReturnType, typename... Arguments>
const std::vector<D3D8::ArgumentInfo>& D3D8::Utils::SignatureInfo<ReturnType (__stdcall*)(Arguments...)>::get_argument_info_vec()
{
    static const std::vector<ArgumentInfo> result_vec =
    {
        {ArgumentTraits<Arguments>::kind,
         get_object_type_name_ptr(static_cast<ObjectType>(ArgumentTraits<Arguments>::object_type) )}...
    };

    return result_vec;
}

template<typename ReturnType, typename... Arguments>
D3D8::ArgumentInfo D3D8::Utils::SignatureInfo<ReturnType (__stdcall*)(Arguments...)>::get_return_info()
{
    return {ArgumentTraits<ReturnType>::kind,
            get_object_type_name_ptr(static_cast<ObjectType>(ArgumentTraits<ReturnType>::object_type) )};
}

#endif /* D3D8UTILS_SIGNATURE_INFO_H */
