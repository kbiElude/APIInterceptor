/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/macros.h"
#include "Interception/Hooks/OpenGL/pixel_store_manager.h"
#include "Interception/Hooks/OpenGL/utils.h"

/* gl/gl.h provides the compatibility-profile tokens which are absent from glcorearb.h. */
#include "gl/gl.h"

OpenGL::PixelStoreManager::PixelStoreManager()
{
    /* Stub */
}

uint64_t OpenGL::PixelStoreManager::get_n_bitmap_bytes(const Params&  in_params,
                                                       const int64_t& in_width,
                                                       const int64_t& in_height)
{
    constexpr uint64_t N_BITS_PER_BYTE = 8;

    uint64_t alignment = in_params.alignment;
    uint64_t result    = 0;

    if (in_width <= 0 ||
        in_height <= 0)
    {
        goto end;
    }

    if (alignment == 0)
    {
        AI_ASSERT_FAIL();

        alignment = 1;
    }

    {
        const uint64_t n_columns = (in_params.row_length != 0) ? in_params.row_length
                                                                : static_cast<uint64_t>(in_width);
        const uint64_t row_bytes = ( (n_columns + N_BITS_PER_BYTE - 1) / N_BITS_PER_BYTE + alignment - 1) / alignment * alignment;
        const uint64_t skip      = in_params.skip_rows * row_bytes + in_params.skip_pixels / N_BITS_PER_BYTE;
        const uint64_t n_bits    = in_params.skip_pixels % N_BITS_PER_BYTE + static_cast<uint64_t>(in_width);

        result = skip + (static_cast<uint64_t>(in_height) - 1) * row_bytes + (n_bits + N_BITS_PER_BYTE - 1) / N_BITS_PER_BYTE;
    }

end:
    return result;
}

uint64_t OpenGL::PixelStoreManager::get_n_image_bytes(const Params&   in_params,
                                                      const int64_t&  in_width,
                                                      const int64_t&  in_height,
                                                      const int64_t&  in_depth,
                                                      const uint32_t& in_format,
                                                      const uint32_t& in_type)
{
    uint64_t alignment = in_params.alignment;
    uint64_t element_n_bytes;
    uint64_t result    = 0;

    if (in_width  <= 0 ||
        in_height <= 0 ||
        in_depth  <= 0)
    {
        goto end;
    }

    if (in_type == GL_BITMAP)
    {
        result = get_n_bitmap_bytes(in_params,
                                    in_width,
                                    in_height) * static_cast<uint64_t>(in_depth);

        goto end;
    }

    if (alignment == 0)
    {
        AI_ASSERT_FAIL();

        alignment = 1;
    }

    if (Utils::is_packed_pixel_type(in_type) )
    {
        element_n_bytes = Utils::get_n_bytes_for_type(in_type);
    }
    else
    {
        element_n_bytes = static_cast<uint64_t>(Utils::get_n_components_for_format(in_format) ) * Utils::get_n_bytes_for_type(in_type);
    }

    {
        const uint64_t n_columns   = (in_params.row_length != 0) ? in_params.row_length
                                                                  : static_cast<uint64_t>(in_width);
        const uint64_t n_rows      = (in_params.image_height != 0) ? in_params.image_height
                                                                    : static_cast<uint64_t>(in_height);
        const uint64_t row_bytes   = (element_n_bytes >= alignment) ? element_n_bytes * n_columns
                                                                    : (element_n_bytes * n_columns + alignment - 1) / alignment * alignment;
        const uint64_t image_bytes = n_rows * row_bytes;
        const uint64_t skip_bytes  = in_params.skip_pixels * element_n_bytes + in_params.skip_rows * row_bytes + in_params.skip_images * image_bytes;
        const uint64_t extent      = (static_cast<uint64_t>(in_depth)  - 1) * image_bytes +
                                     (static_cast<uint64_t>(in_height) - 1) * row_bytes   +
                                      static_cast<uint64_t>(in_width)       * element_n_bytes;

        result = skip_bytes + extent;
    }

end:
    return result;
}

uint64_t OpenGL::PixelStoreManager::get_n_pack_bytes(const int64_t&  in_width,
                                                     const int64_t&  in_height,
                                                     const int64_t&  in_depth,
                                                     const uint32_t& in_format,
                                                     const uint32_t& in_type) const
{
    return get_n_image_bytes(m_pack_params,
                             in_width,
                             in_height,
                             in_depth,
                             in_format,
                             in_type);
}

uint64_t OpenGL::PixelStoreManager::get_n_unpack_bitmap_bytes(const int64_t& in_width,
                                                              const int64_t& in_height) const
{
    return get_n_bitmap_bytes(m_unpack_params,
                              in_width,
                              in_height);
}

uint64_t OpenGL::PixelStoreManager::get_n_unpack_bytes(const int64_t&  in_width,
                                                       const int64_t&  in_height,
                                                       const int64_t&  in_depth,
                                                       const uint32_t& in_format,
                                                       const uint32_t& in_type) const
{
    return get_n_image_bytes(m_unpack_params,
                             in_width,
                             in_height,
                             in_depth,
                             in_format,
                             in_type);
}

void OpenGL::PixelStoreManager::on_pixel_store(const uint32_t& in_pname,
                                               const int32_t&  in_value)
{
    /* Negative values are errors, and change nothing. */
    if (in_value >= 0)
    {
        const uint32_t value = static_cast<uint32_t>(in_value);

        switch (in_pname)
        {
            case GL_PACK_ALIGNMENT:     m_pack_params.alignment    = value; break;
            case GL_PACK_IMAGE_HEIGHT:  m_pack_params.image_height = value; break;
            case GL_PACK_ROW_LENGTH:    m_pack_params.row_length   = value; break;
            case GL_PACK_SKIP_IMAGES:   m_pack_params.skip_images  = value; break;
            case GL_PACK_SKIP_PIXELS:   m_pack_params.skip_pixels = value; break;
            case GL_PACK_SKIP_ROWS:     m_pack_params.skip_rows    = value; break;

            case GL_UNPACK_ALIGNMENT:    m_unpack_params.alignment    = value; break;
            case GL_UNPACK_IMAGE_HEIGHT: m_unpack_params.image_height = value; break;
            case GL_UNPACK_ROW_LENGTH:   m_unpack_params.row_length   = value; break;
            case GL_UNPACK_SKIP_IMAGES:  m_unpack_params.skip_images  = value; break;
            case GL_UNPACK_SKIP_PIXELS:  m_unpack_params.skip_pixels  = value; break;
            case GL_UNPACK_SKIP_ROWS:    m_unpack_params.skip_rows    = value; break;

            default:
            {
                /* Swapping bytes, the bit order and the sizes of compressed blocks do not change the size. */
                break;
            }
        }
    }
}
