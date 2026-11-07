/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "interception/core/D3D7Utils/value_readers.h"
#include <string.h>

bool Interception::Core::D3D7Utils::parse_surface_description(const uint8_t*      in_data_ptr,
                                                              const size_t&       in_n_bytes,
                                                              SurfaceDescription* out_description_ptr)
{
    /* A 32-bit process has the surface pointer at 36 and 4 bytes long; a 64-bit one has it aligned, at 40, 8 bytes long, and the
     * structure ends with padding.
     */
    constexpr size_t N_BYTES_32_BIT       = 124;
    constexpr size_t N_BYTES_64_BIT       = 136;
    constexpr size_t N_BYTES_POINTER_32   = 4;
    constexpr size_t N_BYTES_POINTER_64   = 8;
    constexpr size_t OFFSET_POINTER_32    = 36;
    constexpr size_t OFFSET_POINTER_64    = 40;
    constexpr size_t OFFSET_FLAGS         = 4;
    constexpr size_t OFFSET_HEIGHT        = 8;
    constexpr size_t OFFSET_WIDTH         = 12;
    constexpr size_t OFFSET_PITCH         = 16;
    constexpr size_t OFFSET_BACK_BUFFERS  = 20;
    constexpr size_t OFFSET_MIP_MAPS      = 24;
    constexpr size_t OFFSET_ALPHA_DEPTH   = 28;
    constexpr size_t OFFSET_RESERVED      = 32;

    const bool is_32_bit = (in_n_bytes == N_BYTES_32_BIT);
    const bool is_64_bit = (in_n_bytes == N_BYTES_64_BIT);
    bool       result    = false;

    if (is_32_bit || is_64_bit)
    {
        SurfaceDescription description;
        size_t             offset = (is_32_bit) ? OFFSET_POINTER_32 + N_BYTES_POINTER_32
                                                : OFFSET_POINTER_64 + N_BYTES_POINTER_64;

        const auto read_func = [&](const size_t& in_offset,
                                   void*         out_value_ptr,
                                   const size_t& in_n_value_bytes)
        {
            memcpy(out_value_ptr,
                   in_data_ptr + in_offset,
                   in_n_value_bytes);
        };

        read_func(OFFSET_FLAGS,        &description.flags,             sizeof(uint32_t) );
        read_func(OFFSET_HEIGHT,       &description.height,            sizeof(uint32_t) );
        read_func(OFFSET_WIDTH,        &description.width,             sizeof(uint32_t) );
        read_func(OFFSET_PITCH,        &description.pitch,             sizeof(int32_t) );
        read_func(OFFSET_BACK_BUFFERS, &description.back_buffer_count, sizeof(uint32_t) );
        read_func(OFFSET_MIP_MAPS,     &description.mip_map_count,     sizeof(uint32_t) );
        read_func(OFFSET_ALPHA_DEPTH,  &description.alpha_bit_depth,   sizeof(uint32_t) );
        read_func(OFFSET_RESERVED,     &description.reserved,          sizeof(uint32_t) );

        if (is_32_bit)
        {
            uint32_t surface_address_u32 = 0;

            read_func(OFFSET_POINTER_32, &surface_address_u32, N_BYTES_POINTER_32);

            description.surface_address = surface_address_u32;
        }
        else
        {
            read_func(OFFSET_POINTER_64, &description.surface_address, N_BYTES_POINTER_64);
        }

        read_func(offset, description.color_key_array, sizeof(description.color_key_array) );
        offset += sizeof(description.color_key_array);

        read_func(offset, &description.pixel_format, sizeof(description.pixel_format) );
        offset += sizeof(description.pixel_format);

        read_func(offset, &description.caps, sizeof(description.caps) );
        offset += sizeof(description.caps);

        read_func(offset, &description.texture_stage, sizeof(uint32_t) );

        *out_description_ptr = description;
        result               = true;
    }

    return result;
}
