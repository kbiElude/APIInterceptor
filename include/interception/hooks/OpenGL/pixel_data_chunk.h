/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#if !defined(OPENGL_PIXEL_DATA_CHUNK_H)
#define OPENGL_PIXEL_DATA_CHUNK_H

#include "interception/hooks/OpenGL/buffer_offset_or_memory_chunk.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            /* The pixels which an image transfer reads from, or writes to, the app. How they are recorded depends on where they
             * are:
             *  - If a buffer is bound to the pixel pack (or unpack) binding point, the pointer is an offset in that buffer. It
             *    is recorded as it is, and the memory behind it is not touched.
             *  - Otherwise, the pixels are copied into a data chunk, when the argument is asked for for the first time.
             *
             * The create_*() functions work out the amount of memory from the pixel storage modes of the current GL context.
             * They must be called from within an intercepted API call, and, for a transfer to the app, after the call.
             */
            class PixelDataChunk : public BufferOffsetOrMemoryChunk
            {
            public:
                PixelDataChunk();

                static PixelDataChunk create_for_pack(const void*     in_pixels_ptr,
                                                      const int64_t&  in_width,
                                                      const int64_t&  in_height,
                                                      const int64_t&  in_depth,
                                                      const uint32_t& in_format,
                                                      const uint32_t& in_type);

                /* A single texel, as glClearTexImage() and glClearBufferData() read it: always client memory, and the pixel
                 * storage modes do not apply.
                 */
                static PixelDataChunk create_for_texel(const void*     in_texel_ptr,
                                                       const uint32_t& in_format,
                                                       const uint32_t& in_type);

                static PixelDataChunk create_for_unpack       (const void*     in_pixels_ptr,
                                                               const int64_t&  in_width,
                                                               const int64_t&  in_height,
                                                               const int64_t&  in_depth,
                                                               const uint32_t& in_format,
                                                               const uint32_t& in_type);
                static PixelDataChunk create_for_unpack_bitmap(const void*     in_bitmap_ptr,
                                                               const int64_t&  in_width,
                                                               const int64_t&  in_height);

                /* For the data whose size the app tells, e.g. compressed images. */
                static PixelDataChunk create_for_unpack_bytes(const void*     in_pixels_ptr,
                                                              const uint64_t& in_n_bytes);

            private:
                PixelDataChunk(const void*     in_pixels_ptr,
                               const uint64_t& in_n_bytes,
                               const bool&     in_is_buffer_offset);
            };
        }
    }
}

#endif /* OPENGL_PIXEL_DATA_CHUNK_H */
