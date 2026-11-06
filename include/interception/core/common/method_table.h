/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * The lookups in the table of the methods of a COM-like API (what a method is by its place in the table of an interface, by its API function,
 * how many an interface has): the same for every API that has such a table; what is in the table, and what it is called, is the API's.
 *
 * The traits type of the API has:
 *   Interface                                   the enum of the interfaces
 *   MethodInfo                                  with interface_type, function and vtable_index
 *   get_method_info_array_ptr(uint32_t*)        all the methods, in the order of their API functions
 *   get_first_function(), get_last_function()   the API functions that the methods are of
 */
#ifndef CORE_COMMON_METHOD_TABLE_H
#define CORE_COMMON_METHOD_TABLE_H

#include "common/types.h"
#include <assert.h>

namespace Interception
{
    namespace Core
    {
        namespace Common
        {
            template<typename Traits>
            class MethodTable
            {
            public:
                typedef typename Traits::Interface  Interface;
                typedef typename Traits::MethodInfo MethodInfo;

                /* APIFUNCTION_UNKNOWN if the slot has no function. */
                static APIInterceptor::APIFunction get_api_function(const Interface& in_interface,
                                                                    const uint32_t&  in_vtable_index)
                {
                    uint32_t                    n_methods   = 0;
                    const MethodInfo*           methods_ptr = Traits::get_method_info_array_ptr(&n_methods);
                    APIInterceptor::APIFunction result      = APIInterceptor::APIFUNCTION_UNKNOWN;

                    for (uint32_t n_method = 0;
                                  n_method < n_methods;
                                ++n_method)
                    {
                        if (methods_ptr[n_method].interface_type == in_interface &&
                            methods_ptr[n_method].vtable_index   == in_vtable_index)
                        {
                            result = methods_ptr[n_method].function;

                            break;
                        }
                    }

                    return result;
                }

                /* nullptr if the API function is not a method of the API. */
                static const MethodInfo* get_method_info_ptr(const APIInterceptor::APIFunction& in_function)
                {
                    uint32_t          n_methods   = 0;
                    const MethodInfo* methods_ptr = Traits::get_method_info_array_ptr(&n_methods);
                    const MethodInfo* result_ptr  = nullptr;

                    if (in_function >= Traits::get_first_function() &&
                        in_function <= Traits::get_last_function ())
                    {
                        result_ptr = methods_ptr + (in_function - Traits::get_first_function() );

                        assert(result_ptr->function == in_function);
                    }

                    return result_ptr;
                }

                static uint32_t get_n_methods(const Interface& in_interface)
                {
                    uint32_t          n_methods   = 0;
                    const MethodInfo* methods_ptr = Traits::get_method_info_array_ptr(&n_methods);
                    uint32_t          result      = 0;

                    for (uint32_t n_method = 0;
                                  n_method < n_methods;
                                ++n_method)
                    {
                        if (methods_ptr[n_method].interface_type == in_interface)
                        {
                            result++;
                        }
                    }

                    return result;
                }
            };
        }
    }
}

#endif /* CORE_COMMON_METHOD_TABLE_H */
