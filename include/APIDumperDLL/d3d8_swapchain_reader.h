/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Reads back the contents of a D3D8 device's back buffer.
 */
#if !defined(APIDUMPERDLL_D3D8_SWAPCHAIN_READER_H)
#define APIDUMPERDLL_D3D8_SWAPCHAIN_READER_H

#include <array>
#include <stdint.h>
#include <vector>

namespace APIDumperDLL
{
    class D3D8SwapchainReader
    {
    public:
        /* Stores the back buffer as RGBA8, bottom row first (like glReadPixels does). Returns false if the back buffer
         * cannot be read, or has a format which is not supported (A8R8G8B8, X8R8G8B8, R5G6B5, X1R5G5B5, A1R5G5B5).
         */
        static bool read(void*                    in_device_ptr,
                         std::array<uint32_t, 2>* out_extents_u32vec2_ptr,
                         std::vector<uint8_t>*    out_rgba_u8_vec_ptr);
    };
}

#endif /* APIDUMPERDLL_D3D8_SWAPCHAIN_READER_H */
