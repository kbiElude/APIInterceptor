/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Turns one frame of a workload file (see Common/workload_format.h) into the segment it holds: decompresses it, and reads the calls, data
 * chunks and surfaces from what comes out. It touches no file and keeps no state of its own, so any number of threads can use it at once,
 * each with a decompressor of its own. WorkloadReader is what puts the segments in order.
 *
 * A segment is decompressed through a small buffer, and the data chunks are decompressed straight into the vectors that hold them: a segment
 * is far larger than a cache (the data chunks of a segment are most of 100 MB), and one more copy of it costs more than the decompression.
 */
#if !defined(APIDUMPLOADER_SEGMENT_DECODER_H)
#define APIDUMPLOADER_SEGMENT_DECODER_H

#include "Capture/APIDumpLoader/APIDumpLoader.h"
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

        class SegmentDecoder
        {
        public:
            /* How a segment is read. */
            struct Options
            {
                /* Asked of each call of the segment: a data chunk which calls refer to, and none of them wants, is left out (it comes as an empty
                 * chunk, as below). Chunks which no call refers to are kept. For a replay which leaves out what some frames make, and so does not
                 * read their chunks. Empty: every chunk is wanted.
                 */
                ChunkWantedFunc chunk_wanted_func;

                /* What the calls of the segment number their chunks from (the chunk IDs of the dump), and the frame of the first call; both are
                 * used with chunk_wanted_func only.
                 */
                uint32_t first_data_chunk_id = 0;
                uint64_t first_frame_index   = 0;

                /* A data chunk of more bytes than this is left out: it comes as an empty chunk (the chunks after it keep their numbers). For
                 * tools which look at the calls and not at the vertices and pixels. 0: none is left out.
                 */
                uint32_t skip_data_chunks_above_n_bytes = 0;
            };

            /* Reads the segment from the frame. False if there are not even the counts. The segment is as complete as the frame lets it be: what
             * is cut short is left out, and *out_is_truncated_ptr says it was. The chunk IDs start at 0 (see Workload::first_data_chunk_id), and
             * the file's pointer size and clock are not set.
             */
            static bool parse_segment(FrameStream*   inout_stream_ptr,
                                      const Options& in_options,
                                      Workload*      out_workload_ptr,
                                      bool*          out_is_truncated_ptr);

        private:
            /* By the number of the chunk in the segment: whether the options leave it out because of the calls. */
            static std::vector<bool> find_unwanted_chunks(const DumpedAPICallVector& in_call_vec,
                                                          const Options&             in_options,
                                                          const size_t&              in_n_chunks);

            static bool parse_api_call  (FrameStream*    inout_stream_ptr,
                                         DumpedAPICall*  out_api_call_ptr);
            static bool parse_data_chunk(FrameStream*    inout_stream_ptr,
                                         const Options&  in_options,
                                         const bool&     in_is_unwanted,
                                         DataChunk*      out_data_chunk_ptr);
            static bool parse_surface   (FrameStream*    inout_stream_ptr,
                                         DumpedSurface*  out_surface_ptr);
        };
    }
}

#endif /* APIDUMPLOADER_SEGMENT_DECODER_H */
