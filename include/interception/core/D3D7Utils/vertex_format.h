/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * What a flexible vertex format (FVF) says about the vertices that are drawn with it. The bits are the same in Direct3D 7 and 8.
 */
#ifndef D3D7UTILS_VERTEX_FORMAT_H
#define D3D7UTILS_VERTEX_FORMAT_H

#include <cstdint>

namespace Interception
{
    namespace Core
    {
        namespace D3D7Utils
        {
            class VertexFormat
            {
            public:
                /* Bytes of the position of a vertex (0 if it has none). */
                static uint32_t get_n_position_bytes(const uint32_t& in_vertex_format);

                /* Bytes of the texture coordinates of a stage of a vertex (0 for a stage which the format does not use). */
                static uint32_t get_n_texture_coordinate_bytes(const uint32_t& in_vertex_format,
                                                               const uint32_t& in_n_stage);

                /* Number of the stages which have texture coordinates. */
                static uint32_t get_n_texture_stages(const uint32_t& in_vertex_format);

                /* Bytes of a vertex. */
                static uint32_t get_n_vertex_bytes(const uint32_t& in_vertex_format);

                static bool has_diffuse (const uint32_t& in_vertex_format);
                static bool has_normal  (const uint32_t& in_vertex_format);
                static bool has_position(const uint32_t& in_vertex_format);
                static bool has_specular(const uint32_t& in_vertex_format);

            private:
                static const uint32_t FLAG_DIFFUSE;
                static const uint32_t FLAG_NORMAL;
                static const uint32_t FLAG_RESERVED1;
                static const uint32_t FLAG_SPECULAR;
                static const uint32_t MAX_N_TEXTURE_STAGES;
                static const uint32_t N_BYTES_COLOR;
                static const uint32_t N_BYTES_FLOAT;
                static const uint32_t N_FLOATS_NORMAL;
                static const uint32_t N_FLOATS_POSITION;
                static const uint32_t N_FLOATS_POSITION_RHW;
                static const uint32_t POSITION_MASK;
                static const uint32_t POSITION_RHW;
                static const uint32_t POSITION_XYZ;
                static const uint32_t TEXTURE_COORDINATE_SIZE_BASE_BIT;
                static const uint32_t TEXTURE_COORDINATE_SIZE_BITS;
                static const uint32_t TEXTURE_COORDINATE_SIZE_MASK;
                static const uint32_t TEXTURE_COUNT_MASK;
                static const uint32_t TEXTURE_COUNT_SHIFT;
            };
        }
    }
}

#endif /* D3D7UTILS_VERTEX_FORMAT_H */
