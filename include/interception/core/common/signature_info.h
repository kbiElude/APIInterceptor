/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * The description of what the arguments and the returned value of a method are, made from the type of the method, and the lookup of
 * it for a function with the overrides of the DWORD arguments whose meaning the type does not tell.
 *
 * The traits type of the API (see common/argument_traits.h) also has:
 *   ArgumentInfo                       {kind, object_type_name_ptr}
 *   ArgumentTraits<T>                  Common::ArgumentTraits<the traits type, T>
 *   get_object_type_name_ptr(type)     the name of a kind of object, nullptr for ObjectType::NONE
 */
#ifndef CORE_COMMON_SIGNATURE_INFO_H
#define CORE_COMMON_SIGNATURE_INFO_H

#include "common/types.h"
#include <vector>

namespace Interception
{
    namespace Core
    {
        namespace Common
        {
            template<typename ArgumentInfo>
            struct SignatureEntry
            {
                const std::vector<ArgumentInfo>& (*get_argument_info_vec_func_ptr)();
                ArgumentInfo                     (*get_return_info_func_ptr)();
            };

            template<typename ApiTraits, typename FunctionPtr>
            struct SignatureInfo;

            template<typename ApiTraits, typename ReturnType, typename... Arguments>
            struct SignatureInfo<ApiTraits, ReturnType (__stdcall*)(Arguments...)>
            {
                typedef typename ApiTraits::ArgumentInfo ArgumentInfo;

                static const std::vector<ArgumentInfo>& get_argument_info_vec()
                {
                    static const std::vector<ArgumentInfo> result_vec =
                    {
                        {ApiTraits::template ArgumentTraits<Arguments>::kind,
                         ApiTraits::get_object_type_name_ptr(ApiTraits::template ArgumentTraits<Arguments>::object_type)}...
                    };

                    return result_vec;
                }

                static ArgumentInfo get_return_info()
                {
                    return {ApiTraits::template ArgumentTraits<ReturnType>::kind,
                            ApiTraits::get_object_type_name_ptr(ApiTraits::template ArgumentTraits<ReturnType>::object_type)};
                }
            };

            /* Finds the description of an argument of a function. An override is of an argument of the function which has a kind
             * of its own, even one beyond the arguments of the method (the extra ones which the hooks add). Returns false if there is
             * neither a description in the signature nor an override.
             */
            template<typename ArgumentInfo, typename ArgumentOverride>
            bool find_argument_info(const SignatureEntry<ArgumentInfo>* in_signature_entry_ptr,
                                    const ArgumentOverride*             in_override_array_ptr,
                                    const size_t&                       in_n_overrides,
                                    const APIInterceptor::APIFunction&  in_function,
                                    const uint32_t&                     in_n_argument,
                                    ArgumentInfo*                       out_argument_info_ptr)
            {
                const ArgumentOverride* override_ptr = nullptr;
                bool                    result       = false;

                for (size_t n_override = 0;
                            n_override < in_n_overrides;
                          ++n_override)
                {
                    if (in_override_array_ptr[n_override].function   == in_function &&
                        in_override_array_ptr[n_override].n_argument == in_n_argument)
                    {
                        override_ptr = &in_override_array_ptr[n_override];

                        break;
                    }
                }

                if (in_signature_entry_ptr != nullptr)
                {
                    const auto& argument_info_vec = in_signature_entry_ptr->get_argument_info_vec_func_ptr();

                    if (in_n_argument < argument_info_vec.size() )
                    {
                        *out_argument_info_ptr = argument_info_vec.at(in_n_argument);

                        if (override_ptr != nullptr)
                        {
                            out_argument_info_ptr->kind = override_ptr->kind;
                        }

                        result = true;
                    }
                    else
                    if (override_ptr != nullptr)
                    {
                        out_argument_info_ptr->kind                 = override_ptr->kind;
                        out_argument_info_ptr->object_type_name_ptr = nullptr;

                        result = true;
                    }
                }

                return result;
            }
        }
    }
}

#endif /* CORE_COMMON_SIGNATURE_INFO_H */
