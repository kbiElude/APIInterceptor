/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * What the arguments and the returned value of each D3D8 method mean.
 */
#ifndef D3D8UTILS_ARGUMENT_INFO_H
#define D3D8UTILS_ARGUMENT_INFO_H

#include "D3D8/types.h"

namespace D3D8
{
    namespace Utils
    {
        /* Returns false for functions which are not D3D8 methods, or for an argument which does not exist. */
        bool get_argument_info(const APIInterceptor::APIFunction& in_function,
                               const uint32_t&                    in_n_argument,
                               ArgumentInfo*                      out_argument_info_ptr);

        /* Returns 0 for functions which are not D3D8 methods. */
        uint32_t get_n_arguments(const APIInterceptor::APIFunction& in_function);

        bool get_return_info(const APIInterceptor::APIFunction& in_function,
                             ArgumentInfo*                      out_return_info_ptr);

        /* Returns nullptr for functions which are not D3D8 methods. */
        const SignatureEntry* get_signature_entry_ptr(const APIInterceptor::APIFunction& in_function);
    }
}

#endif /* D3D8UTILS_ARGUMENT_INFO_H */
