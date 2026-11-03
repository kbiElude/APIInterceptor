/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Interception/Core/D3D7Utils/vertex_format.h"
#include <algorithm>

const uint32_t Interception::Core::D3D7Utils::VertexFormat::FLAG_DIFFUSE                     = 0x00000040;
const uint32_t Interception::Core::D3D7Utils::VertexFormat::FLAG_NORMAL                      = 0x00000010;
const uint32_t Interception::Core::D3D7Utils::VertexFormat::FLAG_RESERVED1                   = 0x00000020;
const uint32_t Interception::Core::D3D7Utils::VertexFormat::FLAG_SPECULAR                   = 0x00000080;
const uint32_t Interception::Core::D3D7Utils::VertexFormat::MAX_N_TEXTURE_STAGES            = 8;
const uint32_t Interception::Core::D3D7Utils::VertexFormat::N_BYTES_COLOR                   = sizeof(uint32_t);
const uint32_t Interception::Core::D3D7Utils::VertexFormat::N_BYTES_FLOAT                   = sizeof(float);
const uint32_t Interception::Core::D3D7Utils::VertexFormat::N_FLOATS_NORMAL                 = 3;
const uint32_t Interception::Core::D3D7Utils::VertexFormat::N_FLOATS_POSITION               = 3;
const uint32_t Interception::Core::D3D7Utils::VertexFormat::N_FLOATS_POSITION_RHW           = 4;
const uint32_t Interception::Core::D3D7Utils::VertexFormat::POSITION_MASK                   = 0x0000000e;
const uint32_t Interception::Core::D3D7Utils::VertexFormat::POSITION_RHW                    = 0x00000004;
const uint32_t Interception::Core::D3D7Utils::VertexFormat::POSITION_XYZ                    = 0x00000002;
const uint32_t Interception::Core::D3D7Utils::VertexFormat::TEXTURE_COORDINATE_SIZE_BASE_BIT = 16; /* the size of the coordinates of stage 0; each stage has 2 more bits */
const uint32_t Interception::Core::D3D7Utils::VertexFormat::TEXTURE_COORDINATE_SIZE_BITS    = 2;
const uint32_t Interception::Core::D3D7Utils::VertexFormat::TEXTURE_COORDINATE_SIZE_MASK    = 0x00000003;
const uint32_t Interception::Core::D3D7Utils::VertexFormat::TEXTURE_COUNT_MASK              = 0x00000f00;
const uint32_t Interception::Core::D3D7Utils::VertexFormat::TEXTURE_COUNT_SHIFT             = 8;

uint32_t Interception::Core::D3D7Utils::VertexFormat::get_n_position_bytes(const uint32_t& in_vertex_format)
{
    const uint32_t position = in_vertex_format & POSITION_MASK;
    uint32_t       result   = 0;

    if (position == POSITION_RHW)
    {
        result = N_FLOATS_POSITION_RHW * N_BYTES_FLOAT;
    }
    else
    if (position == POSITION_XYZ)
    {
        result = N_FLOATS_POSITION * N_BYTES_FLOAT;
    }
    else
    if (position > POSITION_RHW)
    {
        /* XYZB1..XYZB5 follow XYZRHW, 2 apart in the format; each has one blending weight more than the one before. */
        const uint32_t n_blending_weights = (position - POSITION_RHW) / POSITION_XYZ;

        result = (N_FLOATS_POSITION + n_blending_weights) * N_BYTES_FLOAT;
    }

    return result;
}

uint32_t Interception::Core::D3D7Utils::VertexFormat::get_n_texture_coordinate_bytes(const uint32_t& in_vertex_format,
                                                                                const uint32_t& in_n_stage)
{
    constexpr uint32_t N_FLOATS_1D = 1;
    constexpr uint32_t N_FLOATS_2D = 2;
    constexpr uint32_t N_FLOATS_3D = 3;
    constexpr uint32_t N_FLOATS_4D = 4;
    constexpr uint32_t SIZE_CODE_1D = 3;
    constexpr uint32_t SIZE_CODE_2D = 0;
    constexpr uint32_t SIZE_CODE_3D = 1;
    constexpr uint32_t SIZE_CODE_4D = 2;

    uint32_t result = 0;

    if (in_n_stage < get_n_texture_stages(in_vertex_format) )
    {
        const uint32_t size_code = (in_vertex_format >> (TEXTURE_COORDINATE_SIZE_BASE_BIT + in_n_stage * TEXTURE_COORDINATE_SIZE_BITS) ) & TEXTURE_COORDINATE_SIZE_MASK;

        switch (size_code)
        {
            case SIZE_CODE_1D:
            {
                result = N_FLOATS_1D * N_BYTES_FLOAT;

                break;
            }

            case SIZE_CODE_2D:
            {
                result = N_FLOATS_2D * N_BYTES_FLOAT;

                break;
            }

            case SIZE_CODE_3D:
            {
                result = N_FLOATS_3D * N_BYTES_FLOAT;

                break;
            }

            case SIZE_CODE_4D:
            {
                result = N_FLOATS_4D * N_BYTES_FLOAT;

                break;
            }

            default:
            {
                break;
            }
        }
    }

    return result;
}

uint32_t Interception::Core::D3D7Utils::VertexFormat::get_n_texture_stages(const uint32_t& in_vertex_format)
{
    return std::min<uint32_t>((in_vertex_format & TEXTURE_COUNT_MASK) >> TEXTURE_COUNT_SHIFT,
                              MAX_N_TEXTURE_STAGES);
}

uint32_t Interception::Core::D3D7Utils::VertexFormat::get_n_vertex_bytes(const uint32_t& in_vertex_format)
{
    uint32_t result = get_n_position_bytes(in_vertex_format);

    if (has_normal(in_vertex_format) )
    {
        result += N_FLOATS_NORMAL * N_BYTES_FLOAT;
    }

    if ((in_vertex_format & FLAG_RESERVED1) != 0)
    {
        result += N_BYTES_COLOR;
    }

    if (has_diffuse(in_vertex_format) )
    {
        result += N_BYTES_COLOR;
    }

    if (has_specular(in_vertex_format) )
    {
        result += N_BYTES_COLOR;
    }

    for (uint32_t n_stage = 0;
                  n_stage < get_n_texture_stages(in_vertex_format);
                ++n_stage)
    {
        result += get_n_texture_coordinate_bytes(in_vertex_format,
                                                 n_stage);
    }

    return result;
}

bool Interception::Core::D3D7Utils::VertexFormat::has_diffuse(const uint32_t& in_vertex_format)
{
    return (in_vertex_format & FLAG_DIFFUSE) != 0;
}

bool Interception::Core::D3D7Utils::VertexFormat::has_normal(const uint32_t& in_vertex_format)
{
    return (in_vertex_format & FLAG_NORMAL) != 0;
}

bool Interception::Core::D3D7Utils::VertexFormat::has_position(const uint32_t& in_vertex_format)
{
    return (in_vertex_format & POSITION_MASK) != 0;
}

bool Interception::Core::D3D7Utils::VertexFormat::has_specular(const uint32_t& in_vertex_format)
{
    return (in_vertex_format & FLAG_SPECULAR) != 0;
}
