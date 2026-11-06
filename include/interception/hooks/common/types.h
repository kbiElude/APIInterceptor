/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Types shared by the hooks of the COM-based APIs (Direct3D 7, Direct3D 8...). Types are alphabetical.
 */
#ifndef HOOKS_COMMON_TYPES_H
#define HOOKS_COMMON_TYPES_H

#include "common/types.h"
#include <Windows.h>
#include <cstdint>
#include <type_traits>

namespace Interception
{
    namespace Hooks
    {
        namespace Common
        {
            /* How an argument is captured. */
            enum class ArgumentCategory
            {
                CONST_STRUCT,   /* const S*: input structure, captured before the call                       */
                GUID,           /* const GUID&                                                               */
                MUTABLE_STRUCT, /* S*: output structure, captured after the call (input/output: before, too) */
                OBJECT,         /* Pointer to an interface of the API                                        */
                OBJECT_OUT,     /* Pointer to a pointer to an interface of the API, written by the call      */
                POINTER_OUT,    /* void**: pointer written by the call, e.g. by QueryInterface               */
                SCALAR,         /* Integers, floats, enums and any other pointers                            */
                SCALAR_OUT      /* Pointer to an integer, written by the call                                */
            };

            /* A vtable slot to hook. */
            struct HookEntry
            {
                void*    hook_function_ptr;
                uint32_t vtable_index;
            };

            /* A locked region of a resource, as handed out to the application. */
            struct LockRecord
            {
                const uint8_t* data_ptr;
                uint32_t       flags;
                uint32_t       n_bytes;
            };

            /* The pointed-to type of a pointer argument, without cv-qualifiers. */
            template<typename T>
            struct PointeeOf
            {
                typedef typename std::remove_cv<typename std::remove_pointer<T>::type>::type type;
            };

            /* Enums are 32-bit in the APIs which use COM. */
            template<typename T, bool is_enum = std::is_enum<T>::value>
            struct ScalarConversion
            {
                typedef T type;
            };

            template<typename T>
            struct ScalarConversion<T, true>
            {
                typedef uint32_t type;
            };
        }
    }
}

#endif /* HOOKS_COMMON_TYPES_H */
