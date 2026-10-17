/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Builds workload files for the tests.
 */
#ifndef TESTS_WORKLOAD_FILE_BUILDER_H
#define TESTS_WORKLOAD_FILE_BUILDER_H

#include "Common/types.h"
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <vector>

namespace Tests
{
    class WorkloadFileBuilder
    {
    public:
        static constexpr uint32_t POINTER_N_BYTES = 8;
        static constexpr uint64_t QPC_FREQUENCY   = 10000000;
        static constexpr uint32_t THREAD_ID       = 7;
        static constexpr uint64_t TIMESTAMP_BASE  = 1000; /* a call with argument N is stamped TIMESTAMP_BASE + N */

        /* A file in the layout which preceded the file header: one segment, one call. */
        static void build_file_without_header(std::vector<uint8_t>* out_u8_vec_ptr);

        /* One segment of n_frames frames, each of n_calls_per_frame calls followed by a SwapBuffers call. */
        static void build_frames(std::vector<uint8_t>* out_u8_vec_ptr,
                                 const uint32_t&       in_n_frames,
                                 const uint32_t&       in_n_calls_per_frame);

        /* Two segments: [2 calls, 2 chunks, 1 surface] and [1 call, 1 chunk]. Returns the offset of the second one's chunk. */
        static size_t build_two_segments(std::vector<uint8_t>* out_u8_vec_ptr);

        static const char* get_filename_ptr();
        static void        write_file      (const std::vector<uint8_t>& in_u8_vec);

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
        static void append_file_header       (std::vector<uint8_t>*                      inout_u8_vec_ptr);
        static void append_header            (std::vector<uint8_t>*                      inout_u8_vec_ptr,
                                              const uint32_t&                            in_n_api_calls,
                                              const uint32_t&                            in_n_data_chunks,
                                              const uint32_t&                            in_n_surfaces);
        static void append_surface           (std::vector<uint8_t>*                      inout_u8_vec_ptr,
                                              const std::vector<uint8_t>&                in_data_u8_vec);
    };
}

#endif /* TESTS_WORKLOAD_FILE_BUILDER_H */
