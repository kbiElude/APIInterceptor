/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Layout of a workload file, shared by the dumper, the loader and the tests:
 *
 *   file    := WorkloadFileHeader segment*
 *   segment := 3 x uint32_t (n API calls, n data chunks, n surfaces) call* chunk* surface*
 *   call    := uint32_t function, uint32_t n in args, uint32_t n out args, uint32_t thread ID, uint64_t timestamp,
 *              in args, out args, returned value
 *   chunk   := uint32_t n bytes, bytes
 *   surface := uint32_t width, uint32_t height, uint32_t n bytes, bytes
 *
 * Timestamps are QueryPerformanceCounter ticks, taken when the call is intercepted.
 */
#ifndef COMMON_WORKLOAD_FORMAT_H
#define COMMON_WORKLOAD_FORMAT_H

#include <stdint.h>

namespace APIInterceptor
{
    namespace WorkloadFormat
    {
        /* Size of the fixed part of a call; the arguments follow. */
        constexpr uint32_t CALL_HEADER_N_BYTES = 4 * sizeof(uint32_t) + sizeof(uint64_t);
        constexpr uint32_t FILE_VERSION        = 2;
        constexpr char     MAGIC[8]            = {'A', 'P', 'I', 'D', 'W', 'K', 'L', 'D'};

        struct WorkloadFileHeader
        {
            char     magic_i8vec8[8];
            uint32_t version;
            uint32_t pointer_n_bytes;   /* of the process which was dumped */
            uint64_t qpc_frequency;     /* ticks per second                */
        };

        static_assert(sizeof(WorkloadFileHeader) == 24,
                      "Unexpected padding in the file header");
        static_assert(CALL_HEADER_N_BYTES        == 24,
                      "Unexpected size of the call header");
    }
}

#endif /* COMMON_WORKLOAD_FORMAT_H */
