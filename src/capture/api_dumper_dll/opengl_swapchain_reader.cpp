/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include <Windows.h>
#include "GL/gl.h"
#include "interception/hooks/OpenGL/types.h"
#include "opengl_swapchain_reader.h"

bool Capture::APIDumperDLL::OpenGLSwapchainReader::read(void*                    in_device_context_ptr,
                                                        std::array<uint32_t, 2>* out_extents_u32vec2_ptr,
                                                        std::vector<uint8_t>*    out_rgba_u8_vec_ptr)
{
    constexpr uint32_t N_BYTES_PER_PIXEL = 4; /* rgba8_unorm */

    std::array<uint32_t, 2> extents_u32vec2    = {};
    bool                    result             = false;
    uint8_t*                rgba_ptr           = nullptr;
    RECT                    window_client_rect = {};
    HWND                    window_handle      = ::WindowFromDC(reinterpret_cast<HDC>(in_device_context_ptr) );

    if (window_handle == nullptr)
    {
        goto end;
    }

    if (::GetClientRect(window_handle,
                       &window_client_rect) == FALSE)
    {
        goto end;
    }

    extents_u32vec2[0] = static_cast<uint32_t>(window_client_rect.right  - window_client_rect.left);
    extents_u32vec2[1] = static_cast<uint32_t>(window_client_rect.bottom - window_client_rect.top);

    if (extents_u32vec2[0] == 0 ||
        extents_u32vec2[1] == 0)
    {
        goto end;
    }

    out_rgba_u8_vec_ptr->resize(static_cast<size_t>(extents_u32vec2[0]) * extents_u32vec2[1] * N_BYTES_PER_PIXEL);

    rgba_ptr = out_rgba_u8_vec_ptr->data();

    ::glReadPixels(0, /* x */
                   0, /* y */
                   extents_u32vec2[0],
                   extents_u32vec2[1],
                   GL_RGBA,
                   GL_UNSIGNED_BYTE,
                   rgba_ptr);
    ::glFinish    ();

    *out_extents_u32vec2_ptr = extents_u32vec2;

    result = true;
end:
    return result;
}
