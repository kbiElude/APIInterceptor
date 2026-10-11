/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "D3D8/argument_factory.h"

APIInterceptor::APIFunctionArgument D3D8::ArgumentFactory::create_chunk(const void*     in_data_ptr,
                                                                               const uint32_t& in_n_bytes)
{
    const uint32_t n_bytes = (in_data_ptr != nullptr) ? in_n_bytes
                                                      : 0;

    return APIInterceptor::APIFunctionArgument::create_data_chunk_id(APIInterceptor::register_data_chunk(in_data_ptr,
                                                                                                         n_bytes) );
}

APIInterceptor::APIFunctionArgument D3D8::ArgumentFactory::create_scalar(const double& in_value)
{
    return APIInterceptor::APIFunctionArgument::create_fp64(in_value);
}

APIInterceptor::APIFunctionArgument D3D8::ArgumentFactory::create_scalar(const float& in_value)
{
    return APIInterceptor::APIFunctionArgument::create_fp32(in_value);
}

APIInterceptor::APIFunctionArgument D3D8::ArgumentFactory::create_scalar(const int& in_value)
{
    return APIInterceptor::APIFunctionArgument::create_i32(in_value);
}

APIInterceptor::APIFunctionArgument D3D8::ArgumentFactory::create_scalar(const long& in_value)
{
    return APIInterceptor::APIFunctionArgument::create_i32(static_cast<int>(in_value) );
}

APIInterceptor::APIFunctionArgument D3D8::ArgumentFactory::create_scalar(const short& in_value)
{
    return APIInterceptor::APIFunctionArgument::create_i16(in_value);
}

APIInterceptor::APIFunctionArgument D3D8::ArgumentFactory::create_scalar(const signed char& in_value)
{
    return APIInterceptor::APIFunctionArgument::create_i8(static_cast<char>(in_value) );
}

APIInterceptor::APIFunctionArgument D3D8::ArgumentFactory::create_scalar(const unsigned char& in_value)
{
    return APIInterceptor::APIFunctionArgument::create_u8(in_value);
}

APIInterceptor::APIFunctionArgument D3D8::ArgumentFactory::create_scalar(const unsigned int& in_value)
{
    return APIInterceptor::APIFunctionArgument::create_u32(in_value);
}

APIInterceptor::APIFunctionArgument D3D8::ArgumentFactory::create_scalar(const unsigned long& in_value)
{
    return APIInterceptor::APIFunctionArgument::create_u32(static_cast<unsigned int>(in_value) );
}

APIInterceptor::APIFunctionArgument D3D8::ArgumentFactory::create_scalar(const unsigned short& in_value)
{
    return APIInterceptor::APIFunctionArgument::create_u16(in_value);
}

APIInterceptor::APIFunctionArgument D3D8::ArgumentFactory::create_scalar(const void* const& in_value)
{
    return APIInterceptor::APIFunctionArgument::create_void_ptr(in_value);
}

APIInterceptor::APIFunctionArgument D3D8::ArgumentFactory::create_unknown()
{
    return APIInterceptor::APIFunctionArgument();
}
