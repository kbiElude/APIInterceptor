/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * How the pixels of a locked DirectDraw surface are laid out in memory.
 */
#ifndef D3D7UTILS_SURFACE_LAYOUT_H
#define D3D7UTILS_SURFACE_LAYOUT_H

#include "Interception/Hooks/D3D7/types.h"

namespace Interception
{
    namespace Core
    {
        namespace D3D7Utils
        {
            class SurfaceLayout
            {
            public:
                /* Bytes of the pixels in the rows of the region of a surface that was locked, which the description that the lock
                 * has filled in tells about; the region is the whole surface if no rectangle is given. The last row is not padded
                 * up to the pitch. 0 if the description tells nothing of the pixels.
                 */
                static uint32_t get_region_n_bytes(const Interception::Hooks::D3D7::DDSURFACEDESC2& in_locked_description,
                                                   const RECT*                                       in_rect_ptr);

            private:
                static const uint32_t FLAG_LINEAR_SIZE;
                static const uint32_t FLAG_PITCH;
                static const uint32_t N_BITS_IN_BYTE;
            };
        }
    }
}

#endif /* D3D7UTILS_SURFACE_LAYOUT_H */
