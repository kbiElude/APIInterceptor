/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * What the flags of a DirectDraw palette say about its entries.
 */
#ifndef D3D7UTILS_PALETTE_LAYOUT_H
#define D3D7UTILS_PALETTE_LAYOUT_H

#include <cstdint>

namespace Interception
{
    namespace Core
    {
        namespace D3D7Utils
        {
            class PaletteLayout
            {
            public:
                /* Number of the entries of a palette made with the given flags (DDPCAPS_1BIT..DDPCAPS_8BIT); 0 if they say none. */
                static uint32_t get_n_entries(const uint32_t& in_flags);

            private:
                static const uint32_t FLAG_1_BIT;
                static const uint32_t FLAG_2_BIT;
                static const uint32_t FLAG_4_BIT;
                static const uint32_t FLAG_8_BIT;
                static const uint32_t N_ENTRIES_1_BIT;
                static const uint32_t N_ENTRIES_2_BIT;
                static const uint32_t N_ENTRIES_4_BIT;
                static const uint32_t N_ENTRIES_8_BIT;
            };
        }
    }
}

#endif /* D3D7UTILS_PALETTE_LAYOUT_H */
