/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Creates API call arguments out of values of D3D8 argument types.
 */
#ifndef D3D8_ARGUMENT_FACTORY_H
#define D3D8_ARGUMENT_FACTORY_H

#include "D3D8/types.h"

namespace D3D8
{
    class ArgumentFactory
    {
    public:
        /* Registers the data as a data chunk. A null pointer yields an empty chunk. */
        static APIInterceptor::APIFunctionArgument create_chunk(const void*     in_data_ptr,
                                                                const uint32_t& in_n_bytes);

        /* Scalars. Enums are converted to uint32_t by the caller. */
        static APIInterceptor::APIFunctionArgument create_scalar(const double&         in_value);
        static APIInterceptor::APIFunctionArgument create_scalar(const float&          in_value);
        static APIInterceptor::APIFunctionArgument create_scalar(const int&            in_value);
        static APIInterceptor::APIFunctionArgument create_scalar(const long&           in_value);
        static APIInterceptor::APIFunctionArgument create_scalar(const short&          in_value);
        static APIInterceptor::APIFunctionArgument create_scalar(const signed char&    in_value);
        static APIInterceptor::APIFunctionArgument create_scalar(const unsigned char&  in_value);
        static APIInterceptor::APIFunctionArgument create_scalar(const unsigned int&   in_value);
        static APIInterceptor::APIFunctionArgument create_scalar(const unsigned long&  in_value);
        static APIInterceptor::APIFunctionArgument create_scalar(const unsigned short& in_value);
        static APIInterceptor::APIFunctionArgument create_scalar(const void* const&    in_value);

        /* Used for functions which return nothing. */
        static APIInterceptor::APIFunctionArgument create_unknown();
    };
}

#endif /* D3D8_ARGUMENT_FACTORY_H */
