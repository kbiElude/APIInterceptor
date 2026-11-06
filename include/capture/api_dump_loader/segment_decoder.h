/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Turns one frame of a workload file (see common/workload_format.h) into the segment it holds: decompresses it, and reads the calls, data
 * chunks and surfaces from what comes out. It touches no file and keeps no state of its own, so any number of threads can use it at once,
 * each with a decompressor of its own. WorkloadReader is what puts the segments in order.
 *
 * A segment is decompressed through a small buffer, and the data chunks are decompressed straight into the vectors that hold them: a segment
 * is far larger than a cache (the data chunks of a segment are most of 100 MB), and one more copy of it costs more than the decompression.
 */
#if !defined(APIDUMPLOADER_SEGMENT_DECODER_H)
#define APIDUMPLOADER_SEGMENT_DECODER_H

#include "capture/api_dump_loader/api_dump_loader.h"
#include "capture/api_dump_loader/frame_stream.h"
#include <stddef.h>
#include <stdint.h>
#include <vector>

namespace Capture
{
    namespace APIDumpLoader
    {
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
