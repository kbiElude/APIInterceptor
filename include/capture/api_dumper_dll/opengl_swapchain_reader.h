/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Reads back the contents of the default framebuffer of an OpenGL window.
 */
#if !defined(APIDUMPERDLL_OPENGL_SWAPCHAIN_READER_H)
#define APIDUMPERDLL_OPENGL_SWAPCHAIN_READER_H

#include <array>
#include <stdint.h>
#include <vector>

namespace Capture
{
    namespace APIDumperDLL
    {
        class OpenGLSwapchainReader
        {
        public:
            /* Stores the color buffer of the window which the device context (an HDC) belongs to as RGBA8, bottom row first, as glReadPixels
             * gives it. The context of the calling thread must be current. Returns false if the window or its size cannot be told.
             */
            static bool read(void*                    in_device_context_ptr,
                             std::array<uint32_t, 2>* out_extents_u32vec2_ptr,
                             std::vector<uint8_t>*    out_rgba_u8_vec_ptr);
        };
    }
}

#endif /* APIDUMPERDLL_OPENGL_SWAPCHAIN_READER_H */
