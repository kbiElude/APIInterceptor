/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "interception/core/D3D7Utils/surface_layout.h"

const uint32_t Interception::Core::D3D7Utils::SurfaceLayout::FLAG_LINEAR_SIZE = 0x00080000; /* DDSD_LINEARSIZE */
const uint32_t Interception::Core::D3D7Utils::SurfaceLayout::FLAG_PITCH       = 0x00000008; /* DDSD_PITCH      */
const uint32_t Interception::Core::D3D7Utils::SurfaceLayout::N_BITS_IN_BYTE   = 8;

uint32_t Interception::Core::D3D7Utils::SurfaceLayout::get_region_n_bytes(const Interception::Hooks::D3D7::DDSURFACEDESC2& in_locked_description,
                                                                          const RECT*                                       in_rect_ptr)
{
    const uint32_t bits_per_pixel = in_locked_description.ddpfPixelFormat.dwRGBBitCount;
    const uint32_t height         = (in_rect_ptr != nullptr) ? static_cast<uint32_t>(in_rect_ptr->bottom - in_rect_ptr->top)
                                                             : in_locked_description.dwHeight;
    const uint32_t width          = (in_rect_ptr != nullptr) ? static_cast<uint32_t>(in_rect_ptr->right  - in_rect_ptr->left)
                                                             : in_locked_description.dwWidth;
    uint32_t       result         = 0;

    if (bits_per_pixel != 0)
    {
        const uint32_t n_row_bytes = (width * bits_per_pixel + N_BITS_IN_BYTE - 1) / N_BITS_IN_BYTE;
        const uint32_t pitch       = ((in_locked_description.dwFlags & FLAG_PITCH) != 0) ? static_cast<uint32_t>(in_locked_description.lPitch)
                                                                                         : n_row_bytes;

        if (height != 0)
        {
            result = (height - 1) * pitch + n_row_bytes;
        }
    }
    else
    if ((in_locked_description.dwFlags & FLAG_LINEAR_SIZE) != 0)
    {
        /* Compressed formats tell the size of the surface instead of a pitch. */
        result = static_cast<uint32_t>(in_locked_description.lPitch);
    }

    return result;
}
