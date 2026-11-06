/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Builds workload files for the tests.
 */
#ifndef TESTS_WORKLOAD_FILE_BUILDER_H
#define TESTS_WORKLOAD_FILE_BUILDER_H

#include "common/types.h"
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <vector>

namespace Tests
{
    class WorkloadFileBuilder
    {
    public:
        static constexpr size_t   LARGE_CHUNK_N_BYTES = 3 * 1024 * 1024; /* more than the reader buffers                      */
        static constexpr uint32_t N_CHUNKS_PER_SEGMENT = 2;                /* of build_many_segments()                          */
        static constexpr uint32_t POINTER_N_BYTES     = 8;
        static constexpr uint64_t QPC_FREQUENCY       = 10000000;
        static constexpr uint32_t THREAD_ID           = 7;
        static constexpr uint64_t TIMESTAMP_BASE      = 1000;            /* a call with argument N is stamped TIMESTAMP_BASE + N */

        /* One segment of 3 frames, one call in each followed by a SwapBuffers call, and 4 data chunks (of 1 to 4 bytes, all of the value of their
         * number plus 1). The call of frame N refers to chunk N, a second call of frame 1 refers to chunk 0 too, and no call refers to chunk 3.
         */
        static void build_chunk_references(std::vector<uint8_t>* out_u8_vec_ptr);

        /* A file in the layout which preceded the file header: one segment, one call. */
        static void build_file_without_header(std::vector<uint8_t>* out_u8_vec_ptr);

        /* One segment of n_frames frames, each of n_calls_per_frame calls followed by a SwapBuffers call. */
        static void build_frames(std::vector<uint8_t>* out_u8_vec_ptr,
                                 const uint32_t&       in_n_frames,
                                 const uint32_t&       in_n_calls_per_frame);

        /* One segment of one call and a chunk of LARGE_CHUNK_N_BYTES bytes, which are get_large_chunk_byte(0..). */
        static void build_large_chunk(std::vector<uint8_t>* out_u8_vec_ptr);

        /* n_segments segments, each of n_calls_per_segment calls (the argument of call N of segment S is S * 1000 + N) and
         * N_CHUNKS_PER_SEGMENT data chunks of n_bytes_per_chunk bytes (get_segment_chunk_byte()), written as the dumper writes
         * them: a frame of unknown size for each segment, with a checksum. The chunks compress by far more than the reader
         * expects, so that it has to make room for more.
         */
        static void build_many_segments(std::vector<uint8_t>* out_u8_vec_ptr,
                                        const uint32_t&       in_n_segments,
                                        const uint32_t&       in_n_calls_per_segment,
                                        const size_t&         in_n_bytes_per_chunk);

        /* n_segments segments of n_calls_per_segment calls each, one data chunk of a few bytes in each. Every (n_calls_per_frame + 1)th call of the
         * file is a SwapBuffers call, which ends a frame, wherever that is in a segment (the frames need not fit in them).
         */
        static void build_segments(std::vector<uint8_t>* out_u8_vec_ptr,
                                   const uint32_t&       in_n_segments,
                                   const uint32_t&       in_n_calls_per_segment,
                                   const uint32_t&       in_n_calls_per_frame);

        /* Two segments: [2 calls, 2 chunks, 1 surface] and [1 call, 1 chunk]. The last bytes of the second segment can
         * be left out, which ends it in the middle of the chunk (the segment is compressed as it is, so the frame is
         * complete).
         */
        static void build_two_segments(std::vector<uint8_t>* out_u8_vec_ptr,
                                       const size_t&         in_n_bytes_to_drop_from_second_segment = 0);

        static const char* get_filename_ptr      ();
        static uint8_t     get_large_chunk_byte  (const size_t&               in_n_byte);
        static uint8_t     get_segment_chunk_byte(const uint32_t&             in_n_segment,
                                                  const uint32_t&             in_n_chunk,
                                                  const size_t&               in_n_byte);
        static void        write_file          (const std::vector<uint8_t>& in_u8_vec);

    private:
        static void append_bytes             (std::vector<uint8_t>*                      inout_u8_vec_ptr,
                                              const void*                                in_data_ptr,
                                              const size_t&                              in_n_bytes);
        static void append_call              (std::vector<uint8_t>*                      inout_u8_vec_ptr,
                                              const uint32_t&                            in_u32_argument,
                                              const APIInterceptor::APIFunction&         in_function = APIInterceptor::APIFUNCTION_GL_GLACCUM);
        static void append_call_with_argument(std::vector<uint8_t>*                      inout_u8_vec_ptr,
                                              const APIInterceptor::APIFunction&         in_function,
                                              const APIInterceptor::APIFunctionArgument& in_argument,
                                              const uint32_t&                            in_timestamp_offset);
        static void append_chunk             (std::vector<uint8_t>*                      inout_u8_vec_ptr,
                                              const std::vector<uint8_t>&                in_data_u8_vec);
        static void append_compressed_segment(std::vector<uint8_t>*                      inout_u8_vec_ptr,
                                              const std::vector<uint8_t>&                in_segment_u8_vec);
        static void append_file_header       (std::vector<uint8_t>*                      inout_u8_vec_ptr);
        static void append_header            (std::vector<uint8_t>*                      inout_u8_vec_ptr,
                                              const uint32_t&                            in_n_api_calls,
                                              const uint32_t&                            in_n_data_chunks,
                                              const uint32_t&                            in_n_surfaces);
        static void append_streamed_segment  (std::vector<uint8_t>*                      inout_u8_vec_ptr,
                                              const std::vector<uint8_t>&                in_segment_u8_vec);
        static void append_surface           (std::vector<uint8_t>*                      inout_u8_vec_ptr,
                                              const std::vector<uint8_t>&                in_data_u8_vec);
    };
}

#endif /* TESTS_WORKLOAD_FILE_BUILDER_H */
