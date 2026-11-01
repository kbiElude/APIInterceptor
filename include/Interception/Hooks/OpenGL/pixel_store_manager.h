/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#if !defined(OPENGL_PIXEL_STORE_MANAGER_H)
#define OPENGL_PIXEL_STORE_MANAGER_H

#include <cstdint>

namespace OpenGL
{
    /* Tracks the pixel storage modes (glPixelStore*) of a GL context, and works out how much memory an image transfer
     * reads from, or writes to, given those modes. There is one for each GL context (see ContextState).
     *
     * The sizes cover everything from the pointer which the app passes to the last byte which the transfer touches,
     * so that the skipped rows and pixels are included.
     */
    class PixelStoreManager
    {
    public:
        PixelStoreManager();

        /* Size of the image that a transfer to client memory (e.g. glReadPixels) writes. */
        uint64_t get_n_pack_bytes(const int64_t&  in_width,
                                  const int64_t&  in_height,
                                  const int64_t&  in_depth,
                                  const uint32_t& in_format,
                                  const uint32_t& in_type) const;

        /* Size of the bitmap that glBitmap() and glPolygonStipple() read: one bit per pixel. */
        uint64_t get_n_unpack_bitmap_bytes(const int64_t& in_width,
                                           const int64_t& in_height) const;

        /* Size of the image that a transfer from client memory (e.g. glTexImage2D) reads. */
        uint64_t get_n_unpack_bytes(const int64_t&  in_width,
                                    const int64_t&  in_height,
                                    const int64_t&  in_depth,
                                    const uint32_t& in_format,
                                    const uint32_t& in_type) const;

        /* The modes which do not change the size of an image are ignored. */
        void on_pixel_store(const uint32_t& in_pname,
                            const int32_t&  in_value);

    private:
        struct Params
        {
            uint32_t alignment    = 4;
            uint32_t image_height = 0;
            uint32_t row_length   = 0;
            uint32_t skip_images  = 0;
            uint32_t skip_pixels  = 0;
            uint32_t skip_rows    = 0;
        };

        /* The size of a bitmap with one bit for each pixel; see get_n_unpack_bitmap_bytes(). */
        static uint64_t get_n_bitmap_bytes(const Params&  in_params,
                                           const int64_t& in_width,
                                           const int64_t& in_height);

        /* The element is a pixel, or a group of pixels for a packed type. */
        static uint64_t get_n_image_bytes(const Params&   in_params,
                                          const int64_t&  in_width,
                                          const int64_t&  in_height,
                                          const int64_t&  in_depth,
                                          const uint32_t& in_format,
                                          const uint32_t& in_type);

        Params m_pack_params;
        Params m_unpack_params;
    };
}

#endif /* OPENGL_PIXEL_STORE_MANAGER_H */
