/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Captures the vertex arrays of a strided D3D7 draw call.
 */
#ifndef D3D7_STRIDED_DATA_CAPTURE_H
#define D3D7_STRIDED_DATA_CAPTURE_H

#include "common/api_function_argument.h"
#include "interception/hooks/D3D7/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace D3D7
        {
            class StridedDataCapture
            {
            public:
                /* The arrays a strided draw reads its n_vertices vertices from, as one data chunk. The arrays are in the order of the
                 * fields of the structure (the position, the normal, the diffuse and specular colors, and the texture coordinates of
                 * each of the 8 stages); one which the vertex format does not have, or the structure does not point at, is empty.
                 * The chunk is the number of the arrays (a uint32_t), then the size in bytes of each, then the arrays themselves,
                 * one after the other.
                 */
                static APIInterceptor::APIFunctionArgument create_argument(const D3DDRAWPRIMITIVESTRIDEDDATA* in_strided_data_ptr,
                                                                           const uint32_t&                    in_vertex_format,
                                                                           const uint32_t&                    in_n_vertices);
            };
        }
    }
}

#endif /* D3D7_STRIDED_DATA_CAPTURE_H */
