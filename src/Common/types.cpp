/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/types.h"
#include <assert.h>

uint32_t APIInterceptor::APIFunctionArgument::deserialize_from_u8_ptr(const uint8_t* in_u8_ptr)
{
    uint32_t n_arg_value_bytes = 0;
    uint32_t result            = 0;

    type       = *reinterpret_cast<const APIFunctionArgumentType*>(in_u8_ptr);
    in_u8_ptr += sizeof(APIFunctionArgumentType);
    result    += sizeof(APIFunctionArgumentType);

    n_arg_value_bytes = get_n_arg_value_bytes();

    if (n_arg_value_bytes != 0)
    {
        memcpy(&value,
                in_u8_ptr,
                n_arg_value_bytes);

        in_u8_ptr += n_arg_value_bytes;
        result    += n_arg_value_bytes;
    }

    return result;
}

const APIInterceptor::DataChunkID& APIInterceptor::APIFunctionArgument::get_data_chunk_id() const
{
    assert(type == APIFunctionArgumentType::ARGTYPE_DATA_CHUNK_ID);

    return value.value_id;
}

const float& APIInterceptor::APIFunctionArgument::get_fp32() const
{
    assert(type == APIFunctionArgumentType::ARGTYPE_F32);

    return value.value_fp32;
}

const float* APIInterceptor::APIFunctionArgument::get_fp32_ptr() const
{
    assert(type == APIFunctionArgumentType::ARGTYPE_F32_PTR);

    return reinterpret_cast<const float*>(get_ptr_internal() );
}

const double& APIInterceptor::APIFunctionArgument::get_fp64() const
{
    assert(type == APIFunctionArgumentType::ARGTYPE_F64);

    return value.value_fp64;
}

const double* APIInterceptor::APIFunctionArgument::get_fp64_ptr() const
{
    assert(type == APIFunctionArgumentType::ARGTYPE_F64_PTR);

    return reinterpret_cast<const double*>(get_ptr_internal() );
}

const char& APIInterceptor::APIFunctionArgument::get_i8() const
{
    assert(type == APIFunctionArgumentType::ARGTYPE_I8);

    return value.value_i8;
}

const char* APIInterceptor::APIFunctionArgument::get_i8_ptr() const
{
    assert(type == APIFunctionArgumentType::ARGTYPE_I8_PTR);

    return reinterpret_cast<const char*>(get_ptr_internal() );
}

const short& APIInterceptor::APIFunctionArgument::get_i16() const
{
    assert(type == APIFunctionArgumentType::ARGTYPE_I16);

    return value.value_i16;
}

const short* APIInterceptor::APIFunctionArgument::get_i16_ptr() const
{
    assert(type == APIFunctionArgumentType::ARGTYPE_I16_PTR);

    return reinterpret_cast<const short*>(get_ptr_internal() );
}

const int& APIInterceptor::APIFunctionArgument::get_i32() const
{
    assert(type == APIFunctionArgumentType::ARGTYPE_I32);

    return value.value_i32;
}

const int* APIInterceptor::APIFunctionArgument::get_i32_ptr() const
{
    assert(type == APIFunctionArgumentType::ARGTYPE_I32_PTR);

    return reinterpret_cast<const int*>(get_ptr_internal() );
}

uint32_t APIInterceptor::APIFunctionArgument::get_n_arg_value_bytes() const
{
    uint32_t result = 0;

    switch (type)
    {
        case ARGTYPE_DATA_CHUNK_ID: result = static_cast<uint32_t>(sizeof(DataChunkID) ); break;

        case ARGTYPE_F32:      result = static_cast<uint32_t>(sizeof(float)    ); break;
        case ARGTYPE_F64:      result = static_cast<uint32_t>(sizeof(double)   ); break;
        case ARGTYPE_I8:       result = static_cast<uint32_t>(sizeof(int8_t)   ); break;
        case ARGTYPE_I16:      result = static_cast<uint32_t>(sizeof(int16_t)  ); break;
        case ARGTYPE_I32:      result = static_cast<uint32_t>(sizeof(int32_t)  ); break;
        case ARGTYPE_U8:       result = static_cast<uint32_t>(sizeof(uint8_t)  ); break;
        case ARGTYPE_U16:      result = static_cast<uint32_t>(sizeof(uint16_t) ); break;
        case ARGTYPE_U32:      result = static_cast<uint32_t>(sizeof(uint32_t) ); break;

        case ARGTYPE_F32_PTR:  /* fall-back */
        case ARGTYPE_F64_PTR:  /* fall-back */
        case ARGTYPE_I8_PTR:   /* fall-back */
        case ARGTYPE_I16_PTR:  /* fall-back */
        case ARGTYPE_I32_PTR:  /* fall-back */
        case ARGTYPE_U8_PTR:   /* fall-back */
        case ARGTYPE_U16_PTR:  /* fall-back */
        case ARGTYPE_U32_PTR:  /* fall-back */
        case ARGTYPE_VOID_PTR:
        {
            /* Always use 64 bits for ptr storage*/
            result = static_cast<uint32_t>(sizeof(uint64_t) );

            break;
        }

        case UNKNOWN:
        {
            break;
        }

        default:
        {
            assert(false);
        }
    }

    return result;
}

const unsigned char& APIInterceptor::APIFunctionArgument::get_u8() const
{
    assert(type == APIFunctionArgumentType::ARGTYPE_U8);

    return value.value_u8;
}

const unsigned char* APIInterceptor::APIFunctionArgument::get_u8_ptr() const
{
    assert(type == APIFunctionArgumentType::ARGTYPE_U8_PTR);

    return reinterpret_cast<const unsigned char*>(get_ptr_internal() );
}

const unsigned short& APIInterceptor::APIFunctionArgument::get_u16() const
{
    assert(type == APIFunctionArgumentType::ARGTYPE_U16);

    return value.value_u16;
}

const unsigned short* APIInterceptor::APIFunctionArgument::get_u16_ptr() const
{
    assert(type == APIFunctionArgumentType::ARGTYPE_U16_PTR);

    return reinterpret_cast<const unsigned short*>(get_ptr_internal() );
}

const unsigned int& APIInterceptor::APIFunctionArgument::get_u32() const
{
    assert(type == APIFunctionArgumentType::ARGTYPE_U32);

    return value.value_u32;
}

const unsigned int* APIInterceptor::APIFunctionArgument::get_u32_ptr() const
{
    assert(type == APIFunctionArgumentType::ARGTYPE_U32_PTR);

    return reinterpret_cast<const unsigned int*>(get_ptr_internal() );
}

const void* APIInterceptor::APIFunctionArgument::get_ptr() const
{
    assert(type == APIFunctionArgumentType::ARGTYPE_VOID_PTR);

    return get_ptr_internal();
}

const void* APIInterceptor::APIFunctionArgument::get_ptr_internal() const
{
    #if _WIN64
    {
        return reinterpret_cast<const float*>(value.value_ptr_as_u64);
    }
    #else
    {
        assert( (value.value_ptr_as_u64 >> 32) == 0);

        return reinterpret_cast<const float*>(static_cast<int32_t>(value.value_ptr_as_u64 & 0xFFFFFFFF) );
    }
    #endif
}

void APIInterceptor::APIFunctionArgument::set_ptr_internal(const void* in_ptr)
{
    value.value_ptr_as_u64 = static_cast<uint64_t>(reinterpret_cast<uintptr_t>(in_ptr) );
}

void APIInterceptor::APIFunctionArgument::serialize_to_u8_vec(std::vector<uint8_t>* inout_u8_vec_ptr) const
{
    const uint32_t n_arg_value_bytes = get_n_arg_value_bytes ();
    const auto     pre_u8_vec_size   = inout_u8_vec_ptr->size();
    uint8_t*       u8_ptr            = nullptr;

    inout_u8_vec_ptr->resize(pre_u8_vec_size + sizeof(APIFunctionArgumentType) + n_arg_value_bytes);

    u8_ptr = &inout_u8_vec_ptr->at(pre_u8_vec_size);

    *reinterpret_cast<APIFunctionArgumentType*>(u8_ptr)  = type;
     u8_ptr                                             += sizeof(APIFunctionArgumentType);

    if (n_arg_value_bytes != 0)
    {
        memcpy(u8_ptr,
              &value,
               n_arg_value_bytes);
    }
}