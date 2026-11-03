/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Interception/Core/D3D7Utils/palette_layout.h"

const uint32_t Interception::Core::D3D7Utils::PaletteLayout::FLAG_1_BIT       = 0x00000100; /* DDPCAPS_1BIT */
const uint32_t Interception::Core::D3D7Utils::PaletteLayout::FLAG_2_BIT       = 0x00000200; /* DDPCAPS_2BIT */
const uint32_t Interception::Core::D3D7Utils::PaletteLayout::FLAG_4_BIT       = 0x00000008; /* DDPCAPS_4BIT */
const uint32_t Interception::Core::D3D7Utils::PaletteLayout::FLAG_8_BIT       = 0x00000004; /* DDPCAPS_8BIT */
const uint32_t Interception::Core::D3D7Utils::PaletteLayout::N_ENTRIES_1_BIT  = 2;
const uint32_t Interception::Core::D3D7Utils::PaletteLayout::N_ENTRIES_2_BIT  = 4;
const uint32_t Interception::Core::D3D7Utils::PaletteLayout::N_ENTRIES_4_BIT  = 16;
const uint32_t Interception::Core::D3D7Utils::PaletteLayout::N_ENTRIES_8_BIT  = 256;

uint32_t Interception::Core::D3D7Utils::PaletteLayout::get_n_entries(const uint32_t& in_flags)
{
    uint32_t result = 0;

    if ((in_flags & FLAG_8_BIT) != 0)
    {
        result = N_ENTRIES_8_BIT;
    }
    else
    if ((in_flags & FLAG_4_BIT) != 0)
    {
        result = N_ENTRIES_4_BIT;
    }
    else
    if ((in_flags & FLAG_2_BIT) != 0)
    {
        result = N_ENTRIES_2_BIT;
    }
    else
    if ((in_flags & FLAG_1_BIT) != 0)
    {
        result = N_ENTRIES_1_BIT;
    }

    return result;
}
