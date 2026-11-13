/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Reads the image of the window that the replay has drawn to with GL: the color buffer of the context that is current, as the size of the client area
 * of its window says. The state of GL that a read depends on (the buffer it reads, the way it packs the rows, a buffer bound to receive them) is
 * the program's, and is put back as it was.
 */
#ifndef REPLAYENGINEDLL_GL_FRAME_READER_H
#define REPLAYENGINEDLL_GL_FRAME_READER_H

#include "replay/replay_engine_dll/types.h"
#include <functional>
#include <stdint.h>
#include <vector>

namespace Replay
{
    namespace ReplayEngineDLL
    {
        class GLFrameReader
        {
        public:
            /* The way to the functions of GL by name (those of opengl32.dll and of the driver). */
            typedef std::function<void*(const char*)> ResolveFunc;

            explicit GLFrameReader(ResolveFunc in_resolve_func);

            /* Reads the image of the window of the current context into what is asked for (a null pointer is not asked for): the pixels as rows from the
             * top, four bytes each (blue, green, red and an alpha of 255), with no padding; and the image, valid until the next call. False if there
             * is no current context, or its window has no size, or the driver does not read.
             */
            bool read(std::vector<uint8_t>* out_pixel_u8_vec_ptr,
                      FrameImage*           out_image_ptr);

            /* The rows of what GL read (from the bottom, four bytes a pixel) put from the top, and an alpha of 255 in every pixel. */
            static void make_top_down_and_opaque(const uint32_t&       in_width,
                                                 const uint32_t&       in_height,
                                                 std::vector<uint8_t>* inout_pixel_u8_vec_ptr);

        private:
            /* The state of the reads of GL that the program may have set. */
            struct PackState
            {
                int32_t alignment       = 4;
                int32_t buffer_binding  = 0;
                int32_t read_buffer     = 0;
                int32_t row_length      = 0;
                int32_t skip_pixels     = 0;
                int32_t skip_rows       = 0;
            };

            ResolveFunc          m_resolve_func;
            std::vector<uint8_t> m_pixel_u8_vec;
        };
    }
}

#endif /* REPLAYENGINEDLL_GL_FRAME_READER_H */
