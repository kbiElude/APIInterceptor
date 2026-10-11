/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Builds workload files for the tests.
 */
#ifndef TESTS_WORKLOAD_FILE_BUILDER_H
#define TESTS_WORKLOAD_FILE_BUILDER_H

#include <stddef.h>
#include <stdint.h>
#include <vector>

namespace Tests
{
    class WorkloadFileBuilder
    {
    public:
        static const char* get_filename_ptr();

        /* Two segments: [2 calls, 2 chunks, 1 surface] and [1 call, 1 chunk]. Returns the offset of the second one's chunk. */
        static size_t build_two_segments(std::vector<uint8_t>* out_u8_vec_ptr);

        static void write_file(const std::vector<uint8_t>& in_u8_vec);

    private:
        static void append_bytes  (std::vector<uint8_t>*       inout_u8_vec_ptr,
                                   const void*                 in_data_ptr,
                                   const size_t&               in_n_bytes);
        static void append_call   (std::vector<uint8_t>*       inout_u8_vec_ptr,
                                   const uint32_t&             in_u32_argument);
        static void append_chunk  (std::vector<uint8_t>*       inout_u8_vec_ptr,
                                   const std::vector<uint8_t>& in_data_u8_vec);
        static void append_header (std::vector<uint8_t>*       inout_u8_vec_ptr,
                                   const uint32_t&             in_n_api_calls,
                                   const uint32_t&             in_n_data_chunks,
                                   const uint32_t&             in_n_surfaces);
        static void append_surface(std::vector<uint8_t>*       inout_u8_vec_ptr,
                                   const std::vector<uint8_t>& in_data_u8_vec);
    };
}

#endif /* TESTS_WORKLOAD_FILE_BUILDER_H */
