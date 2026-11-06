/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * An argument of an intercepted API function (or its returned value), as the hooks capture it and as the dump stores it.
 */
#ifndef COMMON_API_FUNCTION_ARGUMENT_H
#define COMMON_API_FUNCTION_ARGUMENT_H

#include <cstdint>
#include <vector>

namespace APIInterceptor
{
    enum APIFunctionArgumentType : uint8_t
    {
        ARGTYPE_F32,
        ARGTYPE_F32_PTR,
        ARGTYPE_F64,
        ARGTYPE_F64_PTR,
        ARGTYPE_I8,
        ARGTYPE_I8_PTR,
        ARGTYPE_I16,
        ARGTYPE_I16_PTR,
        ARGTYPE_I32,
        ARGTYPE_I32_PTR,
        ARGTYPE_U8,
        ARGTYPE_U8_PTR,
        ARGTYPE_U16,
        ARGTYPE_U16_PTR,
        ARGTYPE_U32,
        ARGTYPE_U32_PTR,
        ARGTYPE_VOID_PTR,

        ARGTYPE_DATA_CHUNK_ID,

        ARGTYPE_I32_GLENUM,
        ARGTYPE_U32_GLENUM,

        ARGTYPE_I64,
        ARGTYPE_U64,

        UNKNOWN
    };

    typedef uint32_t DataChunkID;

    /* The most arguments of an API function that a callback is given, the extra ones which a hook adds included. */
    constexpr uint32_t MAX_N_FUNCTION_ARGUMENTS = 14;

    typedef struct APIFunctionArgument
    {
        APIFunctionArgumentType type;

        static APIFunctionArgument create_data_chunk_id(const DataChunkID& in_id)
        {
            APIFunctionArgument result;

            result.type                      = ARGTYPE_DATA_CHUNK_ID;
            result.value.value_id = in_id;

            return result;
        }

        static APIFunctionArgument create_fp32(const float& in_value)
        {
            APIFunctionArgument result;

            result.type             = ARGTYPE_F32;
            result.value.value_fp32 = in_value;

            return result;
        }

        static APIFunctionArgument create_fp32_ptr(const float* in_value_ptr)
        {
            APIFunctionArgument result;

            result.type = ARGTYPE_F32_PTR;

            result.set_ptr_internal(in_value_ptr);
            return result;
        }

        static APIFunctionArgument create_fp64(const double& in_value)
        {
            APIFunctionArgument result;

            result.type             = ARGTYPE_F64;
            result.value.value_fp64 = in_value;

            return result;
        }

        static APIFunctionArgument create_fp64_ptr(const double* in_value_ptr)
        {
            APIFunctionArgument result;

            result.type = ARGTYPE_F64_PTR;

            result.set_ptr_internal(in_value_ptr);
            return result;
        }

        static APIFunctionArgument create_i8(const char& in_value)
        {
            APIFunctionArgument result;

            result.type           = ARGTYPE_I8;
            result.value.value_i8 = in_value;

            return result;
        }

        static APIFunctionArgument create_i8_ptr(const char* in_value_ptr)
        {
            APIFunctionArgument result;

            result.type = ARGTYPE_I8_PTR;

            result.set_ptr_internal(in_value_ptr);
            return result;
        }

        static APIFunctionArgument create_i16(const short& in_value)
        {
            APIFunctionArgument result;

            result.type            = ARGTYPE_I16;
            result.value.value_i16 = in_value;

            return result;
        }

        static APIFunctionArgument create_i16_ptr(const short* in_value_ptr)
        {
            APIFunctionArgument result;

            result.type = ARGTYPE_I16_PTR;

            result.set_ptr_internal(in_value_ptr);
            return result;
        }

        static APIFunctionArgument create_i32(const int& in_value)
        {
            APIFunctionArgument result;

            result.type            = ARGTYPE_I32;
            result.value.value_i32 = in_value;

            return result;
        }

        static APIFunctionArgument create_i32_glenum(const int& in_value)
        {
            APIFunctionArgument result;

            result.type            = ARGTYPE_I32_GLENUM;
            result.value.value_i32 = in_value;

            return result;
        }

        static APIFunctionArgument create_i32_ptr(const int* in_value_ptr)
        {
            APIFunctionArgument result;

            result.type = ARGTYPE_I32_PTR;

            result.set_ptr_internal(in_value_ptr);
            return result;
        }

        static APIFunctionArgument create_i64(const int64_t& in_value)
        {
            APIFunctionArgument result;

            result.type            = ARGTYPE_I64;
            result.value.value_i64 = in_value;

            return result;
        }

        static APIFunctionArgument create_u16(const unsigned short& in_value)
        {
            APIFunctionArgument result;

            result.type            = ARGTYPE_U16;
            result.value.value_u16 = in_value;

            return result;
        }

        static APIFunctionArgument create_u16_ptr(const unsigned short* in_value_ptr)
        {
            APIFunctionArgument result;

            result.type = ARGTYPE_U16_PTR;

            result.set_ptr_internal(in_value_ptr);
            return result;
        }

        static APIFunctionArgument create_u32(const unsigned int& in_value)
        {
            APIFunctionArgument result;

            result.type            = ARGTYPE_U32;
            result.value.value_u32 = in_value;

            return result;
        }

        static APIFunctionArgument create_u32_glenum(const unsigned int& in_value)
        {
            APIFunctionArgument result;

            result.type            = ARGTYPE_U32_GLENUM;
            result.value.value_u32 = in_value;

            return result;
        }

        static APIFunctionArgument create_u32_ptr(const unsigned int* in_value_ptr)
        {
            APIFunctionArgument result;

            result.type = ARGTYPE_U32_PTR;

            result.set_ptr_internal(in_value_ptr);
            return result;
        }

        static APIFunctionArgument create_u64(const uint64_t& in_value)
        {
            APIFunctionArgument result;

            result.type            = ARGTYPE_U64;
            result.value.value_u64 = in_value;

            return result;
        }

        static APIFunctionArgument create_u8(const unsigned char& in_value)
        {
            APIFunctionArgument result;

            result.type           = ARGTYPE_U8;
            result.value.value_u8 = in_value;

            return result;
        }

        static APIFunctionArgument create_u8_ptr(const unsigned char* in_value_ptr)
        {
            APIFunctionArgument result;

            result.type = ARGTYPE_U8_PTR;

            result.set_ptr_internal(in_value_ptr);
            return result;
        }

        static APIFunctionArgument create_void_ptr(const void* in_value_ptr)
        {
            APIFunctionArgument result;

            result.type = ARGTYPE_VOID_PTR;

            result.set_ptr_internal(in_value_ptr);
            return result;
        }

        const DataChunkID&    get_data_chunk_id() const;
        const float&          get_fp32         () const;
        const float*          get_fp32_ptr     () const;
        const double&         get_fp64         () const;
        const double*         get_fp64_ptr     () const;
        const char&           get_i8           () const;
        const char*           get_i8_ptr       () const;
        const short&          get_i16          () const;
        const short*          get_i16_ptr      () const;
        const int&            get_i32          () const;
        const int&            get_i32_glenum   () const;
        const int*            get_i32_ptr      () const;
        const int64_t&        get_i64          () const;
        const unsigned char&  get_u8           () const;
        const unsigned char*  get_u8_ptr       () const;
        const unsigned short& get_u16          () const;
        const unsigned short* get_u16_ptr      () const;
        const unsigned int&   get_u32          () const;
        const unsigned int&   get_u32_glenum   () const;
        const unsigned int*   get_u32_ptr      () const;
        const uint64_t&       get_u64          () const;
        const void*           get_ptr          () const;

        /* Value of any pointer-typed argument as recorded, whatever the pointer size of the process which was dumped.
         * Unlike get_ptr(), safe to call for a dump of the other architecture. Such a value is a handle, not an address.
         */
        uint64_t get_ptr_as_u64() const;

        const void* get_value_ptr() const
        {
            return &value;
        }

        uint32_t deserialize_from_u8_ptr(const uint8_t*        in_u8_ptr);
        void     serialize_to_u8_vec    (std::vector<uint8_t>* inout_u8_vec_ptr) const;

        APIFunctionArgument()
            :type(UNKNOWN)
        {
            /* Stub */
        }

        APIFunctionArgument(const APIFunctionArgument& in_argument) = default;

    private:

        union
        {
            float          value_fp32;
            double         value_fp64;
            char           value_i8;
            short          value_i16;
            int            value_i32;
            int64_t        value_i64;
            DataChunkID    value_id;
            unsigned char  value_u8;
            unsigned short value_u16;
            unsigned int   value_u32;
            uint64_t       value_u64;
            uint64_t       value_ptr_as_u64;
        } value;

        uint32_t    get_n_arg_value_bytes()                   const;
        const void* get_ptr_internal     ()                   const;
        void        set_ptr_internal     (const void* in_ptr);

    } APIFunctionArgument;
}

#endif /* COMMON_API_FUNCTION_ARGUMENT_H */
