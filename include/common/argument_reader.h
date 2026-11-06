/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Reading the value of an argument of a call, whatever the size or the kind of the number is: a call that was made, or one that was dumped,
 * has its numbers as the type of the argument in the API says, which is not always what the reader wants (a flag is a 32-bit unsigned in one
 * method and a signed one in another).
 */
#ifndef COMMON_ARGUMENT_READER_H
#define COMMON_ARGUMENT_READER_H

#include "common/api_function_argument.h"
#include "common/types.h"

namespace APIInterceptor
{
    /* Reads a number of any size or kind from an argument. Returns false if the argument is of another kind (a pointer, a chunk). */
    template<typename T>
    bool read_number(const APIFunctionArgument& in_argument,
                     T*                         out_value_ptr)
    {
        bool result = true;

        switch (in_argument.type)
        {
            case ARGTYPE_F32:        *out_value_ptr = static_cast<T>(in_argument.get_fp32      () ); break;
            case ARGTYPE_F64:        *out_value_ptr = static_cast<T>(in_argument.get_fp64      () ); break;
            case ARGTYPE_I8:         *out_value_ptr = static_cast<T>(in_argument.get_i8        () ); break;
            case ARGTYPE_I16:        *out_value_ptr = static_cast<T>(in_argument.get_i16       () ); break;
            case ARGTYPE_I32:        *out_value_ptr = static_cast<T>(in_argument.get_i32       () ); break;
            case ARGTYPE_I32_GLENUM: *out_value_ptr = static_cast<T>(in_argument.get_i32_glenum() ); break;
            case ARGTYPE_I64:        *out_value_ptr = static_cast<T>(in_argument.get_i64       () ); break;
            case ARGTYPE_U8:         *out_value_ptr = static_cast<T>(in_argument.get_u8        () ); break;
            case ARGTYPE_U16:        *out_value_ptr = static_cast<T>(in_argument.get_u16       () ); break;
            case ARGTYPE_U32:        *out_value_ptr = static_cast<T>(in_argument.get_u32       () ); break;
            case ARGTYPE_U32_GLENUM: *out_value_ptr = static_cast<T>(in_argument.get_u32_glenum() ); break;
            case ARGTYPE_U64:        *out_value_ptr = static_cast<T>(in_argument.get_u64       () ); break;

            default:
            {
                result = false;

                break;
            }
        }

        return result;
    }
}

#endif /* COMMON_ARGUMENT_READER_H */
