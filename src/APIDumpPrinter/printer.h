/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Declarations of the printer tool's logic, defined in main.cpp.
 */
#ifndef APIDUMPPRINTER_PRINTER_H
#define APIDUMPPRINTER_PRINTER_H

#include "APIDumpLoader/APIDumpLoader.h"
#include "api_info.h"
#include <map>
#include <set>
#include <string>

namespace APIDumpPrinter
{
    struct Options
    {
        std::string        chunk_dump_dir;
        uint32_t           first_frame           = 0;
        uint32_t           last_frame            = UINT32_MAX;
        uint32_t           n_hexdump_bytes       = 0;
        bool               show_stats            = false;
        std::set<APIGroup> allowed_api_groups;                  /* empty = all */
        const char*        workload_filename_ptr = nullptr;
    };

    bool parse_api_list   (const char* in_arg_ptr,
                           Options*    inout_options_ptr);
    bool parse_args       (int      in_argc,
                           char*    in_argv[],
                           Options* out_options_ptr);
    bool parse_frame_range(const char* in_arg_ptr,
                           Options*    inout_options_ptr);
    void print_stats      (const std::map<APIInterceptor::APIFunction, uint32_t>& in_call_count_map,
                           const std::map<APIGroup, uint32_t>&                    in_group_count_map,
                           const uint32_t&                                        in_n_calls_selected,
                           const uint32_t&                                        in_n_frames_total,
                           const APIDumpLoader::Workload&                         in_workload);
    void print_usage      ();

    /* Entry point of the tool (called by the global main). */
    int run(int   in_argc,
            char* in_argv[]);

    void write_chunks  (const std::string&                           in_dir,
                        const APIDumpLoader::Workload&               in_workload,
                        const std::set<APIInterceptor::DataChunkID>& in_chunk_id_set);
    void write_surfaces(const APIDumpLoader::Workload&               in_workload);
}

#endif /* APIDUMPPRINTER_PRINTER_H */
