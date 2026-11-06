/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "common/macros.h"
#include "pixel_converter.h"
#include <string.h>

void Capture::APIDumperDLL::PixelConverter::convert_to_rgba8_bottom_first(const PixelSourceFormat& in_format,
                                                                          const void*              in_pixels_ptr,
                                                                          const uint32_t&          in_pitch_n_bytes,
                                                                          const uint32_t&          in_width,
                                                                          const uint32_t&          in_height,
                                                                          std::vector<uint8_t>*    out_rgba_u8_vec_ptr)
{
    constexpr uint32_t A1R5G5B5_ALPHA_SHIFT = 15;
    constexpr uint32_t CHANNEL_MAX          = 255;

    constexpr uint32_t FIVE_BIT_MAX         = (1u << 5) - 1;
    constexpr uint32_t SIX_BIT_MAX          = (1u << 6) - 1;

    constexpr uint32_t X1R5G5B5_BLUE_SHIFT  = 0;
    constexpr uint32_t X1R5G5B5_GREEN_SHIFT = 5;
    constexpr uint32_t X1R5G5B5_RED_SHIFT   = 10;

    constexpr uint32_t R5G6B5_BLUE_SHIFT    = 0;
    constexpr uint32_t R5G6B5_GREEN_SHIFT   = 5;
    constexpr uint32_t R5G6B5_RED_SHIFT     = 11;

    /* A8R8G8B8 and X8R8G8B8 are stored as B, G, R, A; the output is R, G, B, A. All are 32-bit pixels. */
    constexpr uint32_t ARGB8_BLUE_OFFSET    = 0;
    constexpr uint32_t ARGB8_GREEN_OFFSET   = 1;
    constexpr uint32_t ARGB8_RED_OFFSET     = 2;
    constexpr uint32_t ARGB8_ALPHA_OFFSET   = 3;
    constexpr uint32_t RGBA8_RED_OFFSET     = 0;
    constexpr uint32_t RGBA8_GREEN_OFFSET   = 1;
    constexpr uint32_t RGBA8_BLUE_OFFSET    = 2;
    constexpr uint32_t RGBA8_ALPHA_OFFSET   = 3;

    out_rgba_u8_vec_ptr->resize(static_cast<size_t>(in_width) * in_height * sizeof(uint32_t) );

    for (uint32_t y = 0;
                  y < in_height;
                ++y)
    {
        /* Rows are stored bottom first. */
        uint8_t*       destination_ptr = out_rgba_u8_vec_ptr->data  ()                                                    +
                                         static_cast<size_t>        (in_height - 1 - y) * in_width * sizeof(uint32_t);
        const uint8_t* source_ptr      = static_cast<const uint8_t*>(in_pixels_ptr)                                       +
                                         static_cast<size_t>        (y)                 * in_pitch_n_bytes;

        for (uint32_t x = 0;
                      x < in_width;
                    ++x)
        {
            uint32_t red   = 0;
            uint32_t green = 0;
            uint32_t blue  = 0;
            uint32_t alpha = CHANNEL_MAX;

            switch (in_format)
            {
                case PixelSourceFormat::A8R8G8B8:
                case PixelSourceFormat::X8R8G8B8:
                {
                    const uint8_t* pixel_ptr = source_ptr + x * sizeof(uint32_t);

                    blue  = pixel_ptr[ARGB8_BLUE_OFFSET];
                    green = pixel_ptr[ARGB8_GREEN_OFFSET];
                    red   = pixel_ptr[ARGB8_RED_OFFSET];
                    alpha = (in_format == PixelSourceFormat::A8R8G8B8) ? pixel_ptr[ARGB8_ALPHA_OFFSET]
                                                                  : CHANNEL_MAX;

                    break;
                }

                case PixelSourceFormat::A1R5G5B5:
                case PixelSourceFormat::X1R5G5B5:
                {
                    uint16_t pixel = 0;

                    memcpy(&pixel,
                           source_ptr + x * sizeof(pixel),
                           sizeof(pixel) );

                    blue  = ((pixel >> X1R5G5B5_BLUE_SHIFT)  & FIVE_BIT_MAX) * CHANNEL_MAX / FIVE_BIT_MAX;
                    green = ((pixel >> X1R5G5B5_GREEN_SHIFT) & FIVE_BIT_MAX) * CHANNEL_MAX / FIVE_BIT_MAX;
                    red   = ((pixel >> X1R5G5B5_RED_SHIFT)   & FIVE_BIT_MAX) * CHANNEL_MAX / FIVE_BIT_MAX;
                    alpha = (in_format == PixelSourceFormat::A1R5G5B5) ? (((pixel >> A1R5G5B5_ALPHA_SHIFT) & 1) * CHANNEL_MAX)
                                                                  : CHANNEL_MAX;

                    break;
                }

                case PixelSourceFormat::R5G6B5:
                {
                    uint16_t pixel = 0;

                    memcpy(&pixel,
                           source_ptr + x * sizeof(pixel),
                           sizeof(pixel) );

                    blue  = ((pixel >> R5G6B5_BLUE_SHIFT)  & FIVE_BIT_MAX) * CHANNEL_MAX / FIVE_BIT_MAX;
                    green = ((pixel >> R5G6B5_GREEN_SHIFT) & SIX_BIT_MAX)  * CHANNEL_MAX / SIX_BIT_MAX;
                    red   = ((pixel >> R5G6B5_RED_SHIFT)   & FIVE_BIT_MAX) * CHANNEL_MAX / FIVE_BIT_MAX;

                    break;
                }

                default:
                {
                    AI_FAIL_UNSUPPORTED(static_cast<uint32_t>(in_format) );
                }
            }

            destination_ptr[x * sizeof(uint32_t) + RGBA8_RED_OFFSET]   = static_cast<uint8_t>(red);
            destination_ptr[x * sizeof(uint32_t) + RGBA8_GREEN_OFFSET] = static_cast<uint8_t>(green);
            destination_ptr[x * sizeof(uint32_t) + RGBA8_BLUE_OFFSET]  = static_cast<uint8_t>(blue);
            destination_ptr[x * sizeof(uint32_t) + RGBA8_ALPHA_OFFSET] = static_cast<uint8_t>(alpha);
        }
    }
}
