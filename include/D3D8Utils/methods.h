/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Lookups between D3D8 API functions, names and vtable slots.
 */
#ifndef D3D8UTILS_METHODS_H
#define D3D8UTILS_METHODS_H

#include "D3D8Utils/types.h"

namespace D3D8
{
    namespace Utils
    {
        /* Returns APIFUNCTION_UNKNOWN if the slot has no function. */
        APIInterceptor::APIFunction get_api_function(const Interface& in_interface,
                                                     const uint32_t&  in_vtable_index);

        /* E.g. "IDirect3DDevice8::Present". Returns nullptr for non-D3D8 functions. */
        const char* get_function_name_ptr(const APIInterceptor::APIFunction& in_function);

        /* Returns "?" for interfaces which are not recognized. */
        const char* get_interface_name_ptr(const Interface& in_interface);

        /* Returns nullptr if the API function is not a D3D8 function. */
        const MethodInfo* get_method_info_ptr(const APIInterceptor::APIFunction& in_function);

        /* Returns all methods, ordered by API function. */
        const MethodInfo* get_method_info_array_ptr(uint32_t* out_n_methods_ptr);

        uint32_t get_n_methods(const Interface& in_interface);

        /* Returns nullptr for ObjectType::None. */
        const char* get_object_type_name_ptr(const ObjectType& in_object_type);
    }
}

#endif /* D3D8UTILS_METHODS_H */
