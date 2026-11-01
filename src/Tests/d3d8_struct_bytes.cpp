/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "d3d8_struct_bytes.h"
#include <string.h>

std::vector<uint8_t> Tests::D3D8StructBytes::build_matrix(const Interception::Hooks::D3D8::D3DMATRIX& in_matrix)
{
    std::vector<uint8_t> result_u8_vec(sizeof(in_matrix) );

    ::memcpy(result_u8_vec.data(),
            &in_matrix,
             sizeof(in_matrix) );

    return result_u8_vec;
}

std::vector<uint8_t> Tests::D3D8StructBytes::build_present_parameters(const size_t& in_pointer_n_bytes)
{
    const uint32_t       head_u32vec6[6] = {800, 600, Interception::Hooks::D3D8::D3DFMT_X8R8G8B8, 2, Interception::Hooks::D3D8::D3DMULTISAMPLE_NONE, Interception::Hooks::D3D8::D3DSWAPEFFECT_FLIP};
    const uint32_t       tail_u32vec6[6] = {0, 1, Interception::Hooks::D3D8::D3DFMT_D24S8, 0x10, 60, 1};
    std::vector<uint8_t> result_u8_vec(sizeof(head_u32vec6) + in_pointer_n_bytes + sizeof(tail_u32vec6),
                                       0);

    ::memcpy(result_u8_vec.data(),
             head_u32vec6,
             sizeof(head_u32vec6) );
    ::memcpy(result_u8_vec.data() + sizeof(head_u32vec6) + in_pointer_n_bytes,
             tail_u32vec6,
             sizeof(tail_u32vec6) );

    return result_u8_vec;
}

std::vector<uint8_t> Tests::D3D8StructBytes::build_viewport(const Interception::Hooks::D3D8::D3DVIEWPORT8& in_viewport)
{
    std::vector<uint8_t> result_u8_vec(sizeof(in_viewport) );

    ::memcpy(result_u8_vec.data(),
            &in_viewport,
             sizeof(in_viewport) );

    return result_u8_vec;
}
