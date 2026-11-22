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

std::vector<uint8_t> Replay::ReplayEngineDLL::GLFrameReader::make_default_pixels(const uint32_t& in_width,
                                                                                const uint32_t& in_height)
{
    constexpr size_t  N_BYTES_PER_PIXEL = 4;
    constexpr uint8_t OPAQUE_ALPHA      = 255;

    std::vector<uint8_t> result_u8_vec(static_cast<size_t>(in_width) * in_height * N_BYTES_PER_PIXEL,
                                       0);

    for (size_t n_alpha =  N_BYTES_PER_PIXEL - 1;
                n_alpha <  result_u8_vec.size();
                n_alpha += N_BYTES_PER_PIXEL)
    {
        result_u8_vec.at(n_alpha) = OPAQUE_ALPHA;
    }

    return result_u8_vec;
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

bool Replay::ReplayEngineDLL::GLFrameReader::write(const std::vector<uint8_t>& in_pixel_u8_vec)
{
    typedef void (APIENTRY* PFNBINDBUFFERPROC)      (unsigned int, unsigned int);
    typedef void (APIENTRY* PFNCOLORMASKPROC)       (unsigned char, unsigned char, unsigned char, unsigned char);
    typedef void (APIENTRY* PFNDEPTHMASKPROC)       (unsigned char);
    typedef void (APIENTRY* PFNDISABLEPROC)         (unsigned int);
    typedef void (APIENTRY* PFNDRAWBUFFERPROC)      (unsigned int);
    typedef void (APIENTRY* PFNDRAWPIXELSPROC)      (int, int, unsigned int, unsigned int, const void*);
    typedef void (APIENTRY* PFNGETINTEGERVPROC)     (unsigned int, int*);
    typedef void (APIENTRY* PFNLOADIDENTITYPROC)    ();
    typedef void (APIENTRY* PFNMATRIXMODEPROC)      (unsigned int);
    typedef void (APIENTRY* PFNPIXELSTOREIPROC)     (unsigned int, int);
    typedef void (APIENTRY* PFNPIXELTRANSFERFPROC)  (unsigned int, float);
    typedef void (APIENTRY* PFNPIXELTRANSFERIPROC)  (unsigned int, int);
    typedef void (APIENTRY* PFNPIXELZOOMPROC)       (float, float);
    typedef void (APIENTRY* PFNPOPATTRIBPROC)       ();
    typedef void (APIENTRY* PFNPOPCLIENTATTRIBPROC) ();
    typedef void (APIENTRY* PFNPOPMATRIXPROC)       ();
    typedef void (APIENTRY* PFNPUSHATTRIBPROC)      (unsigned int);
    typedef void (APIENTRY* PFNPUSHCLIENTATTRIBPROC)(unsigned int);
    typedef void (APIENTRY* PFNPUSHMATRIXPROC)      ();
    typedef void (APIENTRY* PFNRASTERPOS2IPROC)     (int, int);
    typedef void (APIENTRY* PFNSTENCILMASKPROC)     (unsigned int);
    typedef void (APIENTRY* PFNVIEWPORTPROC)        (int, int, int, int);

    constexpr unsigned int ALL_ATTRIBUTE_BITS        = 0x000FFFFF;
    constexpr unsigned int BACK                      = 0x0405;
    constexpr unsigned int BGRA                      = 0x80E1;
    constexpr unsigned int CLIENT_ALL_ATTRIBUTE_BITS = 0xFFFFFFFF;
    constexpr uint32_t     N_BYTES_PER_PIXEL         = 4;
    constexpr unsigned int MODELVIEW                 = 0x1700;
    constexpr unsigned int PIXEL_UNPACK_BINDING      = 0x88EF;
    constexpr unsigned int PIXEL_UNPACK_BUFFER       = 0x88EC;
    constexpr unsigned int PROJECTION                = 0x1701;
    constexpr unsigned int UNSIGNED_BYTE             = 0x1401;

    /* The capabilities that would change what the pixels become, and the unpacking and transfer values that would change what is read from the array. */
    constexpr unsigned int CAPABILITY_ARRAY[]    = {0x0B44, 0x0B50, 0x0B60, 0x0B71, 0x0B90, 0x0BC0, 0x0BE2, 0x0BF2, 0x0C11, 0x0DE1};
    constexpr unsigned int UNPACK_ZERO_ARRAY[]   = {0x0CF0, 0x0CF1, 0x0CF2, 0x0CF3, 0x0CF4};
    constexpr unsigned int UNPACK_ALIGNMENT      = 0x0CF5;
    constexpr unsigned int TRANSFER_SCALE_ARRAY[] = {0x0D14, 0x0D18, 0x0D1A, 0x0D1C};
    constexpr unsigned int TRANSFER_BIAS_ARRAY[]  = {0x0D15, 0x0D19, 0x0D1B, 0x0D1D};
    constexpr unsigned int MAP_COLOR              = 0x0D10;

    const auto bind_buffer_func_ptr       = reinterpret_cast<PFNBINDBUFFERPROC>      (m_resolve_func("glBindBuffer") );
    const auto color_mask_func_ptr        = reinterpret_cast<PFNCOLORMASKPROC>       (m_resolve_func("glColorMask") );
    const auto depth_mask_func_ptr        = reinterpret_cast<PFNDEPTHMASKPROC>       (m_resolve_func("glDepthMask") );
    const auto disable_func_ptr           = reinterpret_cast<PFNDISABLEPROC>         (m_resolve_func("glDisable") );
    const auto draw_buffer_func_ptr       = reinterpret_cast<PFNDRAWBUFFERPROC>      (m_resolve_func("glDrawBuffer") );
    const auto draw_pixels_func_ptr       = reinterpret_cast<PFNDRAWPIXELSPROC>      (m_resolve_func("glDrawPixels") );
    const auto get_integer_func_ptr       = reinterpret_cast<PFNGETINTEGERVPROC>     (m_resolve_func("glGetIntegerv") );
    const auto load_identity_func_ptr     = reinterpret_cast<PFNLOADIDENTITYPROC>    (m_resolve_func("glLoadIdentity") );
    const auto matrix_mode_func_ptr       = reinterpret_cast<PFNMATRIXMODEPROC>      (m_resolve_func("glMatrixMode") );
    const auto pixel_store_func_ptr       = reinterpret_cast<PFNPIXELSTOREIPROC>     (m_resolve_func("glPixelStorei") );
    const auto pixel_transfer_f_func_ptr  = reinterpret_cast<PFNPIXELTRANSFERFPROC>  (m_resolve_func("glPixelTransferf") );
    const auto pixel_transfer_i_func_ptr  = reinterpret_cast<PFNPIXELTRANSFERIPROC>  (m_resolve_func("glPixelTransferi") );
    const auto pixel_zoom_func_ptr        = reinterpret_cast<PFNPIXELZOOMPROC>       (m_resolve_func("glPixelZoom") );
    const auto pop_attrib_func_ptr        = reinterpret_cast<PFNPOPATTRIBPROC>       (m_resolve_func("glPopAttrib") );
    const auto pop_client_attrib_func_ptr = reinterpret_cast<PFNPOPCLIENTATTRIBPROC> (m_resolve_func("glPopClientAttrib") );
    const auto pop_matrix_func_ptr        = reinterpret_cast<PFNPOPMATRIXPROC>       (m_resolve_func("glPopMatrix") );
    const auto push_attrib_func_ptr       = reinterpret_cast<PFNPUSHATTRIBPROC>      (m_resolve_func("glPushAttrib") );
    const auto push_client_attrib_func_ptr = reinterpret_cast<PFNPUSHCLIENTATTRIBPROC>(m_resolve_func("glPushClientAttrib") );
    const auto push_matrix_func_ptr       = reinterpret_cast<PFNPUSHMATRIXPROC>      (m_resolve_func("glPushMatrix") );
    const auto raster_pos_func_ptr        = reinterpret_cast<PFNRASTERPOS2IPROC>     (m_resolve_func("glRasterPos2i") );
    const auto stencil_mask_func_ptr      = reinterpret_cast<PFNSTENCILMASKPROC>     (m_resolve_func("glStencilMask") );
    const auto viewport_func_ptr          = reinterpret_cast<PFNVIEWPORTPROC>        (m_resolve_func("glViewport") );

    const HDC  device_context = ::wglGetCurrentDC();
    const HWND window         = (device_context != nullptr) ? ::WindowFromDC(device_context)
                                                            : nullptr;
    RECT       client_rect    = {};
    uint32_t   height         = 0;
    int32_t    saved_buffer   = 0;
    bool       result         = false;
    uint32_t   width          = 0;

    if (::wglGetCurrentContext()  == nullptr ||
        window                    == nullptr ||
        color_mask_func_ptr       == nullptr ||
        depth_mask_func_ptr       == nullptr ||
        disable_func_ptr          == nullptr ||
        draw_buffer_func_ptr      == nullptr ||
        draw_pixels_func_ptr      == nullptr ||
        get_integer_func_ptr      == nullptr ||
        load_identity_func_ptr    == nullptr ||
        matrix_mode_func_ptr      == nullptr ||
        pixel_store_func_ptr      == nullptr ||
        pixel_transfer_f_func_ptr == nullptr ||
        pixel_transfer_i_func_ptr == nullptr ||
        pixel_zoom_func_ptr       == nullptr ||
        pop_attrib_func_ptr       == nullptr ||
        pop_client_attrib_func_ptr  == nullptr ||
        pop_matrix_func_ptr       == nullptr ||
        push_attrib_func_ptr      == nullptr ||
        push_client_attrib_func_ptr == nullptr ||
        push_matrix_func_ptr      == nullptr ||
        raster_pos_func_ptr       == nullptr ||
        stencil_mask_func_ptr     == nullptr ||
        viewport_func_ptr         == nullptr)
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

    /* An empty array is what a new back buffer has. */
    if (width  == 0 ||
        height == 0 ||
        (in_pixel_u8_vec.empty() == false &&
         in_pixel_u8_vec.size() != static_cast<size_t>(width) * height * N_BYTES_PER_PIXEL) )
    {
        goto end;
    }

    {
        /* GL draws from the bottom row up. */
        std::vector<uint8_t> bottom_up_u8_vec = (in_pixel_u8_vec.empty() ) ? make_default_pixels(width,
                                                                                                   height)
                                                                            : in_pixel_u8_vec;

        make_top_down_and_opaque(width,
                                 height,
                                 &bottom_up_u8_vec);

        push_attrib_func_ptr       (ALL_ATTRIBUTE_BITS);
        push_client_attrib_func_ptr(CLIENT_ALL_ATTRIBUTE_BITS);

        if (bind_buffer_func_ptr != nullptr)
        {
            get_integer_func_ptr(PIXEL_UNPACK_BINDING,
                                &saved_buffer);

            bind_buffer_func_ptr(PIXEL_UNPACK_BUFFER,
                                 0);
        }

        /* The raster position (-1, -1) with identity matrices is the lower left corner of a viewport that is the whole window. */
        matrix_mode_func_ptr(PROJECTION);
        push_matrix_func_ptr();
        load_identity_func_ptr();
        matrix_mode_func_ptr(MODELVIEW);
        push_matrix_func_ptr();
        load_identity_func_ptr();

        viewport_func_ptr(0,
                          0,
                          static_cast<int>(width),
                          static_cast<int>(height) );

        for (const auto capability : CAPABILITY_ARRAY)
        {
            disable_func_ptr(capability);
        }

        color_mask_func_ptr  (1, 1, 1, 1);
        depth_mask_func_ptr  (0);
        stencil_mask_func_ptr(0);
        draw_buffer_func_ptr (BACK);
        pixel_zoom_func_ptr  (1.0f, 1.0f);

        pixel_transfer_i_func_ptr(MAP_COLOR,
                                  0);

        for (const auto name : TRANSFER_SCALE_ARRAY)
        {
            pixel_transfer_f_func_ptr(name,
                                      1.0f);
        }

        for (const auto name : TRANSFER_BIAS_ARRAY)
        {
            pixel_transfer_f_func_ptr(name,
                                      0.0f);
        }

        for (const auto name : UNPACK_ZERO_ARRAY)
        {
            pixel_store_func_ptr(name,
                                 0);
        }

        pixel_store_func_ptr(UNPACK_ALIGNMENT,
                             1);

        raster_pos_func_ptr(-1,
                            -1);

        draw_pixels_func_ptr(static_cast<int>(width),
                             static_cast<int>(height),
                             BGRA,
                             UNSIGNED_BYTE,
                             bottom_up_u8_vec.data() );

        if (bind_buffer_func_ptr != nullptr)
        {
            bind_buffer_func_ptr(PIXEL_UNPACK_BUFFER,
                                 static_cast<unsigned int>(saved_buffer) );
        }

        matrix_mode_func_ptr(PROJECTION);
        pop_matrix_func_ptr();
        matrix_mode_func_ptr(MODELVIEW);
        pop_matrix_func_ptr();

        pop_client_attrib_func_ptr();
        pop_attrib_func_ptr();

        result = true;
    }

end:
    return result;
}
