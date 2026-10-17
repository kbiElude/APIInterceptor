/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "D3D8Utils/surface_layout.h"

void D3D8::Utils::get_surface_region_layout(const D3DFORMAT& in_format,
                                            const uint32_t&  in_width,
                                            const uint32_t&  in_height,
                                            uint32_t*        out_n_rows_ptr,
                                            uint32_t*        out_n_row_bytes_ptr)
{
    constexpr uint32_t BLOCK_N_PIXELS_PER_SIDE = 4; /* compressed formats are made of 4x4 blocks */
    constexpr uint32_t DXT1_BLOCK_N_BYTES      = 8;
    constexpr uint32_t DXT2_TO_5_BLOCK_N_BYTES = 16;
    constexpr uint32_t PIXEL_N_BYTES_24BIT     = 3;

    uint32_t n_block_bytes = 0;
    uint32_t n_pixel_bytes = 0;
    uint32_t n_rows        = in_height;
    uint32_t n_row_bytes   = 0;

    switch (in_format)
    {
        case D3DFMT_DXT1:
        {
            n_block_bytes = DXT1_BLOCK_N_BYTES;

            break;
        }

        case D3DFMT_DXT2:
        case D3DFMT_DXT3:
        case D3DFMT_DXT4:
        case D3DFMT_DXT5:
        {
            n_block_bytes = DXT2_TO_5_BLOCK_N_BYTES;

            break;
        }

        case D3DFMT_A8:
        case D3DFMT_A4L4:
        case D3DFMT_L8:
        case D3DFMT_P8:
        case D3DFMT_R3G3B2:
        {
            n_pixel_bytes = sizeof(uint8_t);

            break;
        }

        case D3DFMT_A1R5G5B5:
        case D3DFMT_A4R4G4B4:
        case D3DFMT_A8L8:
        case D3DFMT_A8P8:
        case D3DFMT_A8R3G3B2:
        case D3DFMT_D15S1:
        case D3DFMT_D16:
        case D3DFMT_D16_LOCKABLE:
        case D3DFMT_L6V5U5:
        case D3DFMT_R5G6B5:
        case D3DFMT_UYVY:
        case D3DFMT_V8U8:
        case D3DFMT_X1R5G5B5:
        case D3DFMT_X4R4G4B4:
        case D3DFMT_YUY2:
        {
            n_pixel_bytes = sizeof(uint16_t);

            break;
        }

        case D3DFMT_R8G8B8:
        {
            n_pixel_bytes = PIXEL_N_BYTES_24BIT;

            break;
        }

        default:
        {
            /* 32-bit formats, and any format this code is not aware of. */
            n_pixel_bytes = sizeof(uint32_t);

            break;
        }
    }

    if (n_block_bytes != 0)
    {
        n_rows      = (in_height + BLOCK_N_PIXELS_PER_SIDE - 1) / BLOCK_N_PIXELS_PER_SIDE;
        n_row_bytes = ((in_width + BLOCK_N_PIXELS_PER_SIDE - 1) / BLOCK_N_PIXELS_PER_SIDE) * n_block_bytes;
    }
    else
    {
        n_row_bytes = in_width * n_pixel_bytes;
    }

    *out_n_rows_ptr      = n_rows;
    *out_n_row_bytes_ptr = n_row_bytes;
}
