/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * The decompressed bytes of one frame of a workload file, which SegmentDecoder reads from in order.
 */
#if !defined(APIDUMPLOADER_FRAME_STREAM_H)
#define APIDUMPLOADER_FRAME_STREAM_H

#include "zstd.h"
#include <stddef.h>
#include <stdint.h>
#include <vector>

namespace Capture
{
    namespace APIDumpLoader
    {
        /* The decompressed bytes of one frame, which are read from in order. */
        class FrameStream
        {
        public:
            /* The frame is not copied: it must stay where it is for as long as the stream is used. The decompressor is made ready for it. */
            FrameStream(ZSTD_DCtx*     in_decompressor_ptr,
                        const uint8_t* in_frame_ptr,
                        const size_t&  in_n_frame_bytes);

            /* Makes the next bytes available, as many of them as asked up to MAX_PEEK_N_BYTES (fewer at the end of the frame), and returns
             * how many are. They are at get_buffered_ptr(); read_bytes() and skip_bytes() are what take them out.
             */
            size_t peek(const size_t& in_n_bytes);

            /* Reads on to the end of the frame, which is where it is checked: false if the frame was cut or is damaged, anywhere. */
            bool finish();

            const uint8_t* get_buffered_ptr() const;

            /* Whether the frame is known to be cut or damaged so far (a frame which was read to the end is also checked by finish()). */
            bool is_broken() const;

            /* Takes the bytes at the front out of the buffer, which peek() has made available. */
            void consume(const size_t& in_n_bytes);

            /* False if the frame ends first (what was read is lost). Large reads do not go through the buffer. */
            bool read_bytes(void*         out_data_ptr,
                            const size_t& in_n_bytes);

            /* The same, for bytes which are not wanted. */
            bool skip_bytes(const size_t& in_n_bytes);

            /* Bytes which follow the ones in the buffer, so that an argument which is cut short can be looked at without reading outside it. */
            static constexpr size_t MAX_PEEK_N_BYTES = 64;

        private:
            /* Decompresses into the place, as far as the frame goes. */
            size_t decompress(void*         out_data_ptr,
                              const size_t& in_n_bytes);

            size_t               m_buffer_end;
            size_t               m_buffer_start;
            std::vector<uint8_t> m_buffer_u8_vec;
            ZSTD_DCtx*           m_decompressor_ptr;
            ZSTD_inBuffer        m_input;
            bool                 m_is_broken;       /* the frame was cut, or is damaged */
            bool                 m_is_frame_done;
        };
    }
}

#endif /* APIDUMPLOADER_FRAME_STREAM_H */
