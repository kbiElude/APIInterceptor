/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * How the vertices of a strided draw are dumped, and how they are made a structure of the draw again. The arrays that a strided draw reads from are
 * in the memory of the application, and the structure that points at them is of no use once the process is gone: the dump has the structure (for the
 * distance between the vertices of each array) and the arrays as one chunk (see HookPolicyHelper::create_strided_data_argument), which is the number
 * of the arrays (a uint32_t), then the size in bytes of each, then the arrays themselves, one after the other.
 */
#ifndef D3D7UTILS_STRIDED_LAYOUT_H
#define D3D7UTILS_STRIDED_LAYOUT_H

#include "interception/hooks/D3D7/types.h"
#include <stddef.h>
#include <stdint.h>

namespace Interception
{
    namespace Core
    {
        namespace D3D7Utils
        {
            class StridedLayout
            {
            public:
                /* The position, the normal, the diffuse and specular colors, and the texture coordinates of each of the 8 stages: in the order of the
                 * fields of the structure.
                 */
                static constexpr uint32_t N_ARRAYS = 12;

                /* The structure that points at the arrays of the chunk, with the distances of the structure of the dump. An array which the chunk
                 * has none of has no data. False, with nothing made, if either does not have the size or the numbers it should.
                 */
                static bool rebuild(const uint8_t*                                         in_structure_ptr,
                                    const size_t&                                          in_n_structure_bytes,
                                    const uint8_t*                                         in_arrays_ptr,
                                    const size_t&                                          in_n_arrays_bytes,
                                    Interception::Hooks::D3D7::D3DDRAWPRIMITIVESTRIDEDDATA* out_strided_ptr);
            };
        }
    }
}

#endif /* D3D7UTILS_STRIDED_LAYOUT_H */
