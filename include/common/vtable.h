/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Calling a method of an object of a COM-like API (DirectDraw, Direct3D 7 and 8) through its virtual table, which is what the code that must not
 * be seen by the hooks does, and the code that calls a method by the position of it in the table: the first word of the object is the pointer to
 * the table.
 */
#ifndef COMMON_VTABLE_H
#define COMMON_VTABLE_H

#include <stdint.h>

namespace APIInterceptor
{
    /* The virtual table of the object. */
    inline void** get_vtable_ptr(void* in_object_ptr)
    {
        return *reinterpret_cast<void***>(in_object_ptr);
    }

    /* A method by its position in a virtual table that is at hand, with the type of the method (see the PFN_ types of the hooks). */
    template<typename FunctionPointer>
    inline FunctionPointer get_method_ptr(void** in_vtable_ptr,
                                          const uint32_t& in_vtable_index)
    {
        return reinterpret_cast<FunctionPointer>(in_vtable_ptr[in_vtable_index]);
    }

    /* A method of the object by its position in the virtual table. */
    template<typename FunctionPointer>
    inline FunctionPointer get_method_ptr(void*           in_object_ptr,
                                          const uint32_t& in_vtable_index)
    {
        void** const vtable_ptr = get_vtable_ptr(in_object_ptr);

        return get_method_ptr<FunctionPointer>(vtable_ptr,
                                               in_vtable_index);
    }
}

#endif /* COMMON_VTABLE_H */
