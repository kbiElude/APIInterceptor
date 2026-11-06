/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Turns the pixels of a back buffer which a swapchain reader has locked into RGBA8, whatever API the readers are of.
 */
#if !defined(APIDUMPERDLL_PIXEL_CONVERTER_H)
#define APIDUMPERDLL_PIXEL_CONVERTER_H

#include "capture/api_dumper_dll/types.h"
#include <stdint.h>
#include <vector>

namespace Capture
{
    namespace APIDumperDLL
    {
        class PixelConverter
        {
        public:
            /* Stores width x height pixels, whose rows start in_pitch_n_bytes apart, as RGBA8 with the bottom row first (like
             * glReadPixels does). A format without alpha gives an alpha of 255.
             */
            static void convert_to_rgba8_bottom_first(const PixelSourceFormat& in_format,
                                                      const void*              in_pixels_ptr,
                                                      const uint32_t&          in_pitch_n_bytes,
                                                      const uint32_t&          in_width,
                                                      const uint32_t&          in_height,
                                                      std::vector<uint8_t>*    out_rgba_u8_vec_ptr);
        };
    }
}

#endif /* APIDUMPERDLL_PIXEL_CONVERTER_H */
