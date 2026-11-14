/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "gl_frame_reader.h"
#include <string.h>
#include <Windows.h>

Replay::ReplayEngineDLL::GLFrameReader::GLFrameReader(ResolveFunc in_resolve_func)
    :m_resolve_func(in_resolve_func)
{
    /* Stub */
}

void Replay::ReplayEngineDLL::GLFrameReader::make_top_down_and_opaque(const uint32_t&       in_width,
                                                                      const uint32_t&       in_height,
                                                                      std::vector<uint8_t>* inout_pixel_u8_vec_ptr)
{
    constexpr size_t  N_BYTES_PER_PIXEL = 4;
    constexpr uint8_t OPAQUE_ALPHA      = 255;

    const size_t         row_n_bytes = static_cast<size_t>(in_width) * N_BYTES_PER_PIXEL;
    std::vector<uint8_t> row_u8_vec  (row_n_bytes);

    for (uint32_t n_row = 0;
                  n_row < in_height / 2;
                ++n_row)
    {
        uint8_t* const top_ptr    = inout_pixel_u8_vec_ptr->data() + static_cast<size_t>(n_row)                 * row_n_bytes;
        uint8_t* const bottom_ptr = inout_pixel_u8_vec_ptr->data() + static_cast<size_t>(in_height - 1 - n_row) * row_n_bytes;

        ::memcpy(row_u8_vec.data(),
                 top_ptr,
                 row_n_bytes);
        ::memcpy(top_ptr,
                 bottom_ptr,
                 row_n_bytes);
        ::memcpy(bottom_ptr,
                 row_u8_vec.data(),
                 row_n_bytes);
    }

    for (size_t n_alpha =  N_BYTES_PER_PIXEL - 1;
                n_alpha <  inout_pixel_u8_vec_ptr->size();
                n_alpha += N_BYTES_PER_PIXEL)
    {
        inout_pixel_u8_vec_ptr->at(n_alpha) = OPAQUE_ALPHA;
    }
}

bool Replay::ReplayEngineDLL::GLFrameReader::read(std::vector<uint8_t>* out_pixel_u8_vec_ptr,
                                                  FrameImage*           out_image_ptr)
{
    typedef void (APIENTRY* PFNBINDBUFFERPROC)  (unsigned int, unsigned int);
    typedef void (APIENTRY* PFNGETINTEGERVPROC) (unsigned int, int*);
    typedef void (APIENTRY* PFNPIXELSTOREIPROC) (unsigned int, int);
    typedef void (APIENTRY* PFNREADBUFFERPROC)  (unsigned int);
    typedef void (APIENTRY* PFNREADPIXELSPROC)  (int, int, int, int, unsigned int, unsigned int, void*);

    constexpr unsigned int BACK                  = 0x0405;
    constexpr unsigned int BGRA                  = 0x80E1;
    constexpr unsigned int PACK_ALIGNMENT        = 0x0D05;
    constexpr unsigned int PACK_ROW_LENGTH       = 0x0D02;
    constexpr unsigned int PACK_SKIP_PIXELS      = 0x0D04;
    constexpr unsigned int PACK_SKIP_ROWS        = 0x0D03;
    constexpr unsigned int PIXEL_PACK_BUFFER     = 0x88EB;
    constexpr unsigned int PIXEL_PACK_BINDING    = 0x88ED;
    constexpr unsigned int READ_BUFFER           = 0x0C02;
    constexpr uint32_t     N_BYTES_PER_PIXEL     = 4;
    constexpr unsigned int UNSIGNED_BYTE         = 0x1401;

    const auto bind_buffer_func_ptr   = reinterpret_cast<PFNBINDBUFFERPROC>  (m_resolve_func("glBindBuffer") );
    const auto get_integer_func_ptr   = reinterpret_cast<PFNGETINTEGERVPROC> (m_resolve_func("glGetIntegerv") );
    const auto pixel_store_func_ptr   = reinterpret_cast<PFNPIXELSTOREIPROC> (m_resolve_func("glPixelStorei") );
    const auto read_buffer_func_ptr   = reinterpret_cast<PFNREADBUFFERPROC>  (m_resolve_func("glReadBuffer") );
    const auto read_pixels_func_ptr   = reinterpret_cast<PFNREADPIXELSPROC>  (m_resolve_func("glReadPixels") );

    const HDC  device_context  = ::wglGetCurrentDC();
    const HWND window          = (device_context != nullptr) ? ::WindowFromDC(device_context)
                                                             : nullptr;
    RECT       client_rect     = {};
    bool       has_bind_buffer = (bind_buffer_func_ptr != nullptr);
    uint32_t   height          = 0;
    bool       result          = false;
    PackState  saved;
    uint32_t   width           = 0;

    if (::wglGetCurrentContext() == nullptr ||
        window                   == nullptr ||
        get_integer_func_ptr     == nullptr ||
        pixel_store_func_ptr     == nullptr ||
        read_buffer_func_ptr     == nullptr ||
        read_pixels_func_ptr     == nullptr)
    {
        goto end;
    }

    if (::GetClientRect(window,
                       &client_rect) == FALSE)
    {
        goto end;
    }

    width  = static_cast<uint32_t>(client_rect.right  - client_rect.left);
    height = static_cast<uint32_t>(client_rect.bottom - client_rect.top);

    if (width  == 0 ||
        height == 0)
    {
        goto end;
    }

    /* What the program has set is put back after the read. */
    get_integer_func_ptr(PACK_ALIGNMENT,
                        &saved.alignment);
    get_integer_func_ptr(PACK_ROW_LENGTH,
                        &saved.row_length);
    get_integer_func_ptr(PACK_SKIP_PIXELS,
                        &saved.skip_pixels);
    get_integer_func_ptr(PACK_SKIP_ROWS,
                        &saved.skip_rows);
    get_integer_func_ptr(READ_BUFFER,
                        &saved.read_buffer);

    if (has_bind_buffer)
    {
        get_integer_func_ptr(PIXEL_PACK_BINDING,
                            &saved.buffer_binding);

        bind_buffer_func_ptr(PIXEL_PACK_BUFFER,
                             0);
    }

    pixel_store_func_ptr(PACK_ALIGNMENT,
                         1);
    pixel_store_func_ptr(PACK_ROW_LENGTH,
                         0);
    pixel_store_func_ptr(PACK_SKIP_PIXELS,
                         0);
    pixel_store_func_ptr(PACK_SKIP_ROWS,
                         0);
    read_buffer_func_ptr(BACK);

    m_pixel_u8_vec.resize(static_cast<size_t>(width) * height * N_BYTES_PER_PIXEL);

    read_pixels_func_ptr(0,
                         0,
                         static_cast<int>(width),
                         static_cast<int>(height),
                         BGRA,
                         UNSIGNED_BYTE,
                         m_pixel_u8_vec.data() );

    read_buffer_func_ptr(static_cast<unsigned int>(saved.read_buffer) );
    pixel_store_func_ptr(PACK_ALIGNMENT,
                         saved.alignment);
    pixel_store_func_ptr(PACK_ROW_LENGTH,
                         saved.row_length);
    pixel_store_func_ptr(PACK_SKIP_PIXELS,
                         saved.skip_pixels);
    pixel_store_func_ptr(PACK_SKIP_ROWS,
                         saved.skip_rows);

    if (has_bind_buffer)
    {
        bind_buffer_func_ptr(PIXEL_PACK_BUFFER,
                             static_cast<unsigned int>(saved.buffer_binding) );
    }

    make_top_down_and_opaque(width,
                             height,
                             &m_pixel_u8_vec);

    if (out_pixel_u8_vec_ptr != nullptr)
    {
        *out_pixel_u8_vec_ptr = m_pixel_u8_vec;
    }

    if (out_image_ptr != nullptr)
    {
        out_image_ptr->height    = height;
        out_image_ptr->pixel_ptr = m_pixel_u8_vec.data();
        out_image_ptr->width     = width;
    }

    result = true;

end:
    return result;
}
