/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef D3D8UTILS_SURFACE_LAYOUT_H
#define D3D8UTILS_SURFACE_LAYOUT_H

#include "Interception/Hooks/D3D8/types.h"

namespace Interception
{
    namespace Core
    {
        namespace D3D8Utils
        {
            /* How the pixels of a surface region are laid out in memory: n_rows rows of n_row_bytes bytes, the rows being one
             * pitch apart. Compressed formats are counted in rows of 4x4 blocks.
             */
            void get_surface_region_layout(const Interception::Hooks::D3D8::D3DFORMAT& in_format,
                                           const uint32_t&                             in_width,
                                           const uint32_t&                             in_height,
                                           uint32_t*                                   out_n_rows_ptr,
                                           uint32_t*                                   out_n_row_bytes_ptr);
        }
    }
}

#endif /* D3D8UTILS_SURFACE_LAYOUT_H */
