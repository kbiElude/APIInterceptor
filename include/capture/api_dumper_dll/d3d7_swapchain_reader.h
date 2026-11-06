/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Reads back the frame of a Direct3D 7 application, which is a DirectDraw surface: the back buffer of the primary surface which
 * is flipped, or the surface which is blitted to the primary one.
 */
#if !defined(APIDUMPERDLL_D3D7_SWAPCHAIN_READER_H)
#define APIDUMPERDLL_D3D7_SWAPCHAIN_READER_H

#include "interception/hooks/D3D7/types.h"
#include "pixel_converter.h"
#include <array>
#include <stdint.h>
#include <vector>

namespace Capture
{
    namespace APIDumperDLL
    {
        class D3D7SwapchainReader
        {
        public:
            /* Stores the back buffer which is attached to the primary surface as RGBA8, bottom row first (like glReadPixels does).
             * Returns false if there is none (a primary surface of a window has none), or it cannot be read.
             */
            static bool read_back_buffer(void*                    in_primary_surface_ptr,
                                         std::array<uint32_t, 2>* out_extents_u32vec2_ptr,
                                         std::vector<uint8_t>*    out_rgba_u8_vec_ptr);

            /* Stores the surface as RGBA8, bottom row first. Returns false if it cannot be locked, or has a format which is not
             * supported (A8R8G8B8, X8R8G8B8, R5G6B5, X1R5G5B5, A1R5G5B5).
             */
            static bool read_surface(void*                    in_surface_ptr,
                                     std::array<uint32_t, 2>* out_extents_u32vec2_ptr,
                                     std::vector<uint8_t>*    out_rgba_u8_vec_ptr);

        private:
            /* Maps the masks of the pixels of a surface to a format the converter reads. False for any other. */
            static bool get_source_format(const Interception::Hooks::D3D7::DDPIXELFORMAT& in_pixel_format,
                                          PixelConverter::SourceFormat*                   out_source_format_ptr);
        };
    }
}

#endif /* APIDUMPERDLL_D3D7_SWAPCHAIN_READER_H */
