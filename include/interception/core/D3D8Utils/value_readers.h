/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Reads the structures which the dumper stores for D3D8 calls from their bytes, as typed values.
 */
#ifndef D3D8UTILS_VALUE_READERS_H
#define D3D8UTILS_VALUE_READERS_H

#include "interception/core/D3D8Utils/types.h"
#include <stddef.h>
#include <stdint.h>

namespace Interception
{
    namespace Core
    {
        namespace D3D8Utils
        {
            /* Each function returns false (and leaves the output alone) if the bytes are not a structure of the kind. */
            bool parse_matrix            (const uint8_t*                           in_data_ptr,
                                          const size_t&                            in_n_bytes,
                                          Interception::Hooks::D3D8::D3DMATRIX*    out_matrix_ptr);
            bool parse_present_parameters(const uint8_t*                           in_data_ptr,
                                          const size_t&                            in_n_bytes,
                                          PresentParameters*                       out_parameters_ptr);
            bool parse_viewport          (const uint8_t*                           in_data_ptr,
                                          const size_t&                            in_n_bytes,
                                          Interception::Hooks::D3D8::D3DVIEWPORT8* out_viewport_ptr);
        }
    }
}

#endif /* D3D8UTILS_VALUE_READERS_H */
