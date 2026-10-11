/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Printer tool logic (defined in main.cpp).
 */
#ifndef APIDUMPPRINTER_PRINTER_H
#define APIDUMPPRINTER_PRINTER_H

#include "APIDumpLoader/APIDumpLoader.h"
#include "types.h"
#include <map>
#include <set>
#include <string>

namespace APIDumpPrinter
{
    bool parse_api_list    (const char* in_argument_ptr,
                            Options*    inout_options_ptr);
    bool parse_arguments   (int      in_argc,
                            char*    in_argv[],
                            Options* out_options_ptr);
    bool parse_frame_range (const char* in_argument_ptr,
                            Options*    inout_options_ptr);
    void print_statistics  (const std::map<APIInterceptor::APIFunction, uint32_t>& in_call_count_map,
                            const std::map<APIGroup, uint32_t>&                    in_group_count_map,
                            const uint32_t&                                        in_n_calls_selected,
                            const uint32_t&                                        in_n_frames_total,
                            const WorkloadTotals&                                  in_totals);
    void print_usage       ();

    /* Entry point of the tool (called by the global main). */
    int run(int   in_argc,
            char* in_argv[]);

    uint32_t write_chunks  (const std::string&                           in_directory,
                            const APIDumpLoader::Workload&               in_workload,
                            const std::set<APIInterceptor::DataChunkID>& in_chunk_id_set);
    void     write_surfaces(const APIDumpLoader::Workload&               in_workload,
                            const uint32_t&                              in_first_surface_index);
}

#endif /* APIDUMPPRINTER_PRINTER_H */
