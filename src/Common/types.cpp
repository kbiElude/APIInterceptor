/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/types.h"
#include <assert.h>

const float& APIInterceptor::APIFunctionArgument::get_fp32() const
{
    assert(type == APIFunctionArgumentType::ARGTYPE_F32);

    return value.value_fp32;
}

const float* APIInterceptor::APIFunctionArgument::get_fp32_ptr() const
{
    assert(type == APIFunctionArgumentType::ARGTYPE_F32_PTR);

    return value.value_fp32_ptr;
}

const double& APIInterceptor::APIFunctionArgument::get_fp64() const
{
    assert(type == APIFunctionArgumentType::ARGTYPE_F64);

    return value.value_fp64;
}

const double* APIInterceptor::APIFunctionArgument::get_fp64_ptr() const
{
    assert(type == APIFunctionArgumentType::ARGTYPE_F64_PTR);

    return value.value_fp64_ptr;
}

const char& APIInterceptor::APIFunctionArgument::get_i8() const
{
    assert(type == APIFunctionArgumentType::ARGTYPE_I8);

    return value.value_i8;
}

const char* APIInterceptor::APIFunctionArgument::get_i8_ptr() const
{
    assert(type == APIFunctionArgumentType::ARGTYPE_I8_PTR);

    return value.value_i8_ptr;
}

const short& APIInterceptor::APIFunctionArgument::get_i16() const
{
    assert(type == APIFunctionArgumentType::ARGTYPE_I16);

    return value.value_i16;
}

const short* APIInterceptor::APIFunctionArgument::get_i16_ptr() const
{
    assert(type == APIFunctionArgumentType::ARGTYPE_I16_PTR);

    return value.value_i16_ptr;
}

const int& APIInterceptor::APIFunctionArgument::get_i32() const
{
    assert(type == APIFunctionArgumentType::ARGTYPE_I32);

    return value.value_i32;
}

const int* APIInterceptor::APIFunctionArgument::get_i32_ptr() const
{
    assert(type == APIFunctionArgumentType::ARGTYPE_I32_PTR);

    return value.value_i32_ptr;
}

const unsigned char& APIInterceptor::APIFunctionArgument::get_u8() const
{
    assert(type == APIFunctionArgumentType::ARGTYPE_U8);

    return value.value_u8;
}

const unsigned char* APIInterceptor::APIFunctionArgument::get_u8_ptr() const
{
    assert(type == APIFunctionArgumentType::ARGTYPE_U8_PTR);

    return value.value_u8_ptr;
}

const unsigned short& APIInterceptor::APIFunctionArgument::get_u16() const
{
    assert(type == APIFunctionArgumentType::ARGTYPE_U16);

    return value.value_u16;
}

const unsigned short* APIInterceptor::APIFunctionArgument::get_u16_ptr() const
{
    assert(type == APIFunctionArgumentType::ARGTYPE_U16_PTR);

    return value.value_u16_ptr;
}

const unsigned int& APIInterceptor::APIFunctionArgument::get_u32() const
{
    assert(type == APIFunctionArgumentType::ARGTYPE_U32);

    return value.value_u32;
}

const unsigned int* APIInterceptor::APIFunctionArgument::get_u32_ptr() const
{
    assert(type == APIFunctionArgumentType::ARGTYPE_U32_PTR);

    return value.value_u32_ptr;
}

const void* APIInterceptor::APIFunctionArgument::get_ptr() const
{
    assert(type == APIFunctionArgumentType::ARGTYPE_VOID_PTR);

    return value.value_ptr;
}