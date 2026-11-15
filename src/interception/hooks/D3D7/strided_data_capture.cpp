/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "interception/hooks/common/argument_factory.h"
#include "interception/hooks/D3D7/strided_data_capture.h"
#include "interception/core/D3D7Utils/strided_layout.h"
#include "interception/core/D3D7Utils/vertex_format.h"
#include <vector>

APIInterceptor::APIFunctionArgument Interception::Hooks::D3D7::StridedDataCapture::create_argument(const D3DDRAWPRIMITIVESTRIDEDDATA* in_strided_data_ptr,
                                                                                                   const uint32_t&                    in_vertex_format,
                                                                                                   const uint32_t&                    in_n_vertices)
{
    constexpr uint32_t DIFFUSE_ARRAY  = 2;
    constexpr uint32_t N_BYTES_COLOR  = sizeof(uint32_t);
    constexpr uint32_t N_BYTES_NORMAL = 3 * sizeof(float);
    constexpr uint32_t NORMAL_ARRAY   = 1;
    constexpr uint32_t POSITION_ARRAY = 0;
    constexpr uint32_t SPECULAR_ARRAY = 3;
    constexpr uint32_t TEXTURE_ARRAY  = 4;

    constexpr uint32_t N_ARRAYS = Interception::Core::D3D7Utils::StridedLayout::N_ARRAYS;

    const uint8_t* array_ptr_ptr_vec[N_ARRAYS] = {};
    uint32_t       array_n_bytes_vec [N_ARRAYS] = {};

    /* The last vertex is not padded up to the stride. */
    const auto set_array_func = [&](const uint32_t&        in_n_array,
                                    const D3DDP_PTRSTRIDE& in_array,
                                    const uint32_t&        in_n_element_bytes)
    {
        if (in_array.lpvData != nullptr &&
            in_n_vertices    != 0)
        {
            array_ptr_ptr_vec[in_n_array] = static_cast<const uint8_t*>(in_array.lpvData);
            array_n_bytes_vec[in_n_array] = (in_n_vertices - 1) * in_array.dwStride + in_n_element_bytes;
        }
    };

    if (in_strided_data_ptr != nullptr)
    {
        if (Interception::Core::D3D7Utils::VertexFormat::has_position(in_vertex_format) )
        {
            const uint32_t position_n_bytes = Interception::Core::D3D7Utils::VertexFormat::get_n_position_bytes(in_vertex_format);

            set_array_func(POSITION_ARRAY,
                           in_strided_data_ptr->position,
                           position_n_bytes);
        }

        if (Interception::Core::D3D7Utils::VertexFormat::has_normal(in_vertex_format) )
        {
            set_array_func(NORMAL_ARRAY,
                           in_strided_data_ptr->normal,
                           N_BYTES_NORMAL);
        }

        if (Interception::Core::D3D7Utils::VertexFormat::has_diffuse(in_vertex_format) )
        {
            set_array_func(DIFFUSE_ARRAY,
                           in_strided_data_ptr->diffuse,
                           N_BYTES_COLOR);
        }

        if (Interception::Core::D3D7Utils::VertexFormat::has_specular(in_vertex_format) )
        {
            set_array_func(SPECULAR_ARRAY,
                           in_strided_data_ptr->specular,
                           N_BYTES_COLOR);
        }

        for (uint32_t n_stage = 0;
                      n_stage < Interception::Core::D3D7Utils::VertexFormat::get_n_texture_stages(in_vertex_format);
                    ++n_stage)
        {
            const uint32_t coordinate_n_bytes = Interception::Core::D3D7Utils::VertexFormat::get_n_texture_coordinate_bytes(in_vertex_format,
                                                                                                                            n_stage);

            set_array_func(TEXTURE_ARRAY + n_stage,
                           in_strided_data_ptr->textureCoords[n_stage],
                           coordinate_n_bytes);
        }
    }

    /* The number of the arrays, their sizes, and the arrays. */
    std::vector<uint8_t> chunk_u8_vec;

    chunk_u8_vec.insert(chunk_u8_vec.end(),
                        reinterpret_cast<const uint8_t*>(&N_ARRAYS),
                        reinterpret_cast<const uint8_t*>(&N_ARRAYS) + sizeof(N_ARRAYS) );
    chunk_u8_vec.insert(chunk_u8_vec.end(),
                        reinterpret_cast<const uint8_t*>(array_n_bytes_vec),
                        reinterpret_cast<const uint8_t*>(array_n_bytes_vec) + sizeof(array_n_bytes_vec) );

    for (uint32_t n_array = 0;
                  n_array < N_ARRAYS;
                ++n_array)
    {
        if (array_ptr_ptr_vec[n_array] != nullptr)
        {
            chunk_u8_vec.insert(chunk_u8_vec.end(),
                                array_ptr_ptr_vec[n_array],
                                array_ptr_ptr_vec[n_array] + array_n_bytes_vec[n_array]);
        }
    }

    return Interception::Hooks::Common::ArgumentFactory::create_chunk(chunk_u8_vec.data(),
                                                                      static_cast<uint32_t>(chunk_u8_vec.size() ));
}
