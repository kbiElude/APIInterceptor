/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef APIDUMPPRINTER_FORMATTER_H
#define APIDUMPPRINTER_FORMATTER_H

#include "APIDumpLoader/APIDumpLoader.h"
#include "d3d8_decoder.h"
#include <stdio.h>
#include <set>
#include <vector>

namespace APIDumpPrinter
{
    /* Helper: tells whether two arguments have the same type and the same value. */
    bool are_arguments_identical(const APIInterceptor::APIFunctionArgument& in_argument_a,
                                 const APIInterceptor::APIFunctionArgument& in_argument_b,
                                 const APIDumpLoader::Workload&             in_workload);

    /* Prints a single argument (no trailing separator / newline). */
    void print_argument(FILE*                                      in_file_handle,
                        const APIInterceptor::APIFunctionArgument& in_argument,
                        const APIDumpLoader::Workload&             in_workload);

    /* Prints a call as: Name(in arguments) [out: argN=value, ...] returned value
     * [out: ] lists only arguments updated by reference. A non-zero in_n_hexdump_bytes hex-dumps referenced data
     * chunks; their IDs are added to *inout_referenced_chunk_set_ptr, if not null.
     */
    void print_call(FILE*                                  in_file_handle,
                    const APIDumpLoader::DumpedAPICall&    in_call,
                    const APIDumpLoader::Workload&         in_workload,
                    uint32_t                               in_n_hexdump_bytes,
                    std::set<APIInterceptor::DataChunkID>* inout_referenced_chunk_set_ptr,
                    D3D8Decoder*                           inout_d3d8_decoder_ptr);

    /* Helper: hex-dumps up to in_n_bytes_max bytes of a data chunk. */
    void print_hexdump(FILE*                       in_file_handle,
                       const std::vector<uint8_t>& in_chunk_u8_vec,
                       uint32_t                    in_n_bytes_max);

    /* Helper: prints a pointer value, prefixed with a type tag. */
    void print_ptr(FILE*       in_file_handle,
                   const char* in_type_prefix_ptr,
                   const void* in_ptr);
}

#endif /* APIDUMPPRINTER_FORMATTER_H */
