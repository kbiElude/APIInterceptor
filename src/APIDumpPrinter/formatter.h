/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef APIDUMPPRINTER_FORMATTER_H
#define APIDUMPPRINTER_FORMATTER_H

#include "APIDumpLoader/APIDumpLoader.h"
#include <stdio.h>
#include <set>
#include <vector>

namespace APIDumpPrinter
{
    /* Helper: tells whether two arguments have the same type and the same value. */
    bool are_arguments_identical(const APIInterceptor::APIFunctionArgument& in_arg_a,
                                 const APIInterceptor::APIFunctionArgument& in_arg_b);

    /* Prints a single argument (no trailing separator / newline). */
    void print_argument(FILE*                                      in_file_handle,
                        const APIInterceptor::APIFunctionArgument& in_arg,
                        const APIDumpLoader::Workload&             in_workload);

    /* Prints one API call as a single line:
     *
     *   Name(in_arg, ...) [out: argN=value, ...] returned value
     *
     * The [out: ] part only lists the args which the API implementation updated by reference; the returned part
     * is only present if the call returns a value. If in_n_hexdump_bytes is non-zero, the first in_n_hexdump_bytes
     * bytes of each data chunk referenced by the call are hex-dumped underneath.
     * IDs of all data chunks referenced by the call are added to *inout_referenced_chunks_ptr, if not null.
     */
    void print_call(FILE*                                  in_file_handle,
                    const APIDumpLoader::DumpedAPICall&    in_call,
                    const APIDumpLoader::Workload&         in_workload,
                    uint32_t                               in_n_hexdump_bytes,
                    std::set<APIInterceptor::DataChunkID>* inout_referenced_chunks_ptr);

    /* Helper: hex-dumps up to in_n_bytes_max bytes of a data chunk. */
    void print_hexdump(FILE*                       in_file_handle,
                       const std::vector<uint8_t>& in_chunk,
                       uint32_t                    in_n_bytes_max);

    /* Helper: prints a pointer value, prefixed with a type tag. */
    void print_ptr(FILE*       in_file_handle,
                   const char* in_type_prefix_ptr,
                   const void* in_ptr);
}

#endif /* APIDUMPPRINTER_FORMATTER_H */
