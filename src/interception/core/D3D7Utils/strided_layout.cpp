/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "interception/core/D3D7Utils/strided_layout.h"
#include <string.h>

bool Interception::Core::D3D7Utils::StridedLayout::rebuild(const uint8_t*                                         in_structure_ptr,
                                                           const size_t&                                          in_n_structure_bytes,
                                                           const uint8_t*                                         in_arrays_ptr,
                                                           const size_t&                                          in_n_arrays_bytes,
                                                           Interception::Hooks::D3D7::D3DDRAWPRIMITIVESTRIDEDDATA* out_strided_ptr)
{
    constexpr size_t N_HEAD_BYTES = sizeof(uint32_t) * (1 + N_ARRAYS); /* the number of the arrays, and the size of each */

    Interception::Hooks::D3D7::D3DDRAWPRIMITIVESTRIDEDDATA dumped = {};
    Interception::Hooks::D3D7::D3DDP_PTRSTRIDE*            array_ptr_array[N_ARRAYS]        = {};
    const Interception::Hooks::D3D7::D3DDP_PTRSTRIDE*      dumped_array_ptr_array[N_ARRAYS] = {};
    uint32_t                                               n_arrays                         = 0;
    size_t                                                 offset                           = N_HEAD_BYTES;
    Interception::Hooks::D3D7::D3DDRAWPRIMITIVESTRIDEDDATA rebuilt                          = {};
    bool                                                   result                           = false;

    if (in_structure_ptr     == nullptr             ||
        in_arrays_ptr        == nullptr             ||
        in_n_structure_bytes != sizeof(dumped)      ||
        in_n_arrays_bytes    <  N_HEAD_BYTES)
    {
        goto end;
    }

    ::memcpy(&dumped,
             in_structure_ptr,
             sizeof(dumped) );
    ::memcpy(&n_arrays,
             in_arrays_ptr,
             sizeof(n_arrays) );

    if (n_arrays != N_ARRAYS)
    {
        goto end;
    }

    array_ptr_array[0]        = &rebuilt.position;
    array_ptr_array[1]        = &rebuilt.normal;
    array_ptr_array[2]        = &rebuilt.diffuse;
    array_ptr_array[3]        = &rebuilt.specular;
    dumped_array_ptr_array[0] = &dumped.position;
    dumped_array_ptr_array[1] = &dumped.normal;
    dumped_array_ptr_array[2] = &dumped.diffuse;
    dumped_array_ptr_array[3] = &dumped.specular;

    for (size_t n_stage = 0;
                n_stage < 8;
              ++n_stage)
    {
        array_ptr_array       [4 + n_stage] = &rebuilt.textureCoords[n_stage];
        dumped_array_ptr_array[4 + n_stage] = &dumped.textureCoords [n_stage];
    }

    for (size_t n_array = 0;
                n_array < N_ARRAYS;
              ++n_array)
    {
        uint32_t n_array_bytes = 0;

        ::memcpy(&n_array_bytes,
                 in_arrays_ptr + sizeof(uint32_t) * (1 + n_array),
                 sizeof(n_array_bytes) );

        if (n_array_bytes != 0)
        {
            if (offset + n_array_bytes > in_n_arrays_bytes)
            {
                goto end;
            }

            array_ptr_array[n_array]->lpvData  = const_cast<uint8_t*>(in_arrays_ptr + offset);
            array_ptr_array[n_array]->dwStride = dumped_array_ptr_array[n_array]->dwStride;

            offset += n_array_bytes;
        }
    }

    *out_strided_ptr = rebuilt;
    result           = true;

end:
    return result;
}
