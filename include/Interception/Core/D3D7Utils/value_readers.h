/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef D3D7UTILS_VALUE_READERS_H
#define D3D7UTILS_VALUE_READERS_H

#include "Interception/Hooks/D3D7/types.h"
#include <stddef.h>
#include <stdint.h>

namespace Interception
{
    namespace Core
    {
        namespace D3D7Utils
        {
            /* What a DDSURFACEDESC2 holds, whatever the pointer size of the dumped process. The fields which share a place in the
             * structure (the pitch and the linear size, the refresh rate and the number of mip maps, ...) are the first member of
             * their union.
             */
            struct SurfaceDescription
            {
                uint32_t                                       alpha_bit_depth    = 0;
                uint32_t                                       back_buffer_count  = 0;
                Interception::Hooks::D3D7::DDSCAPS2            caps               = {};
                Interception::Hooks::D3D7::DDCOLORKEY          color_key_array[4] = {}; /* destination overlay, destination blit, source overlay, source blit */
                uint32_t                                       flags              = 0;
                uint32_t                                       height             = 0;
                uint32_t                                       mip_map_count      = 0;
                int32_t                                        pitch              = 0;
                Interception::Hooks::D3D7::DDPIXELFORMAT       pixel_format       = {};
                uint32_t                                       reserved           = 0;
                uint32_t                                       texture_stage      = 0;
                uint64_t                                       surface_address    = 0;
                uint32_t                                       width              = 0;
            };

            /* Returns false (and leaves the output alone) if the bytes are not a structure of the kind. */
            bool parse_surface_description(const uint8_t*      in_data_ptr,
                                           const size_t&       in_n_bytes,
                                           SurfaceDescription* out_description_ptr);
        }
    }
}

#endif /* D3D7UTILS_VALUE_READERS_H */
