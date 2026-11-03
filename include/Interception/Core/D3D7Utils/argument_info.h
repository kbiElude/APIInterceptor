/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef D3D7UTILS_ARGUMENT_INFO_H
#define D3D7UTILS_ARGUMENT_INFO_H

#include "Interception/Hooks/D3D7/types.h"

namespace Interception
{
    namespace Core
    {
        namespace D3D7Utils
        {
            /* Returns false for functions which are not D3D7 methods, or for an argument which does not exist. The arguments are
             * numbered as the hooks give them: the object of a method is the first (0), and the extra arguments which a hook adds
             * follow those of the method.
             */
            bool get_argument_info(const APIInterceptor::APIFunction&       in_function,
                                   const uint32_t&                          in_n_argument,
                                   Interception::Hooks::D3D7::ArgumentInfo* out_argument_info_ptr);

            /* Returns 0 for functions which are not D3D7 methods. */
            uint32_t get_n_arguments(const APIInterceptor::APIFunction& in_function);

            bool get_return_info(const APIInterceptor::APIFunction&       in_function,
                                 Interception::Hooks::D3D7::ArgumentInfo* out_return_info_ptr);

            /* Returns nullptr for functions which are not D3D7 methods. */
            const Interception::Hooks::D3D7::SignatureEntry* get_signature_entry_ptr(const APIInterceptor::APIFunction& in_function);
        }
    }
}

#endif /* D3D7UTILS_ARGUMENT_INFO_H */
