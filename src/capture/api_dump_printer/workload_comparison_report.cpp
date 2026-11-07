/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * --compare: what two captures have in common, and where their calls first differ (see WorkloadComparer).
 */
#include "capture/api_dump_loader/workload_comparison.h"
#include "capture/api_dump_names/function_names.h"
#include "printer.h"
#include <algorithm>
#include <set>
#include <stdio.h>
#include <stdlib.h>

namespace
{
    /* The threads that read segments ahead (a 32-bit process holds the segments in its 4 GB). */
    constexpr uint32_t N_READER_THREADS_64_BIT = 3;
    constexpr uint32_t N_READER_THREADS_32_BIT = 1;

    /* The count of a function in a summary, which is 0 if the workload does not call it. */
    uint64_t get_count(const Capture::APIDumpLoader::WorkloadSummary& in_summary,
                       const APIInterceptor::APIFunction&             in_function)
    {
        const auto iterator = in_summary.call_count_map.find(in_function);

        return (iterator != in_summary.call_count_map.end() ) ? iterator->second
                                                              : 0;
    }

    /* A line of the table of what each workload holds. */
    void print_row(const char*     in_name_ptr,
                   const uint64_t& in_first_value,
                   const uint64_t& in_second_value)
    {
        fprintf(stdout,
                "  %-14s %14llu %14llu%s\n",
                in_name_ptr,
                static_cast<unsigned long long>(in_first_value),
                static_cast<unsigned long long>(in_second_value),
                (in_first_value != in_second_value) ? "  <- differs"
                                                    : "");
    }
}

int Capture::APIDumpPrinter::compare_workloads(const Options& in_options)
{
    constexpr size_t N_FUNCTIONS_LISTED = 40;

    Capture::APIDumpLoader::WorkloadComparison comparison;
    std::string                                error;
    std::vector<APIInterceptor::APIFunction>   function_vec;
    std::set<APIInterceptor::APIFunction>      function_set;
    const uint32_t                             n_threads = (sizeof(void*) == sizeof(uint64_t) ) ? N_READER_THREADS_64_BIT
                                                                                                : N_READER_THREADS_32_BIT;
    int                                        result    = EXIT_FAILURE;

    if (Capture::APIDumpLoader::WorkloadComparer::compare(in_options.workload_filename_ptr,
                                                          in_options.compare_filename_ptr,
                                                          n_threads,
                                                         &comparison,
                                                         &error) == false)
    {
        fprintf(stderr,
                "[!] %s\n",
                error.c_str() );

        goto end;
    }

    fprintf(stdout,
            "Comparison of\n"
            "  first:  %s\n"
            "  second: %s\n"
            "\n"
            "  %-14s %14s %14s\n",
            in_options.workload_filename_ptr,
            in_options.compare_filename_ptr,
            "",
            "first",
            "second");

    print_row("calls",
              comparison.first.n_calls,
              comparison.second.n_calls);
    print_row("frames",
              comparison.first.n_frames,
              comparison.second.n_frames);
    print_row("data chunks",
              comparison.first.n_chunks,
              comparison.second.n_chunks);
    print_row("chunk bytes",
              comparison.first.n_chunk_bytes,
              comparison.second.n_chunk_bytes);
    print_row("surfaces",
              comparison.first.n_surfaces,
              comparison.second.n_surfaces);
    print_row("pointer bytes",
              comparison.first.pointer_n_bytes,
              comparison.second.pointer_n_bytes);

    for (const auto& function_pair : comparison.first.call_count_map)
    {
        function_set.insert(function_pair.first);
    }

    for (const auto& function_pair : comparison.second.call_count_map)
    {
        function_set.insert(function_pair.first);
    }

    /* The functions whose counts differ, the ones that differ most first. */
    for (const auto function : function_set)
    {
        if (get_count(comparison.first,
                      function) != get_count(comparison.second,
                                             function) )
        {
            function_vec.push_back(function);
        }
    }

    std::sort(function_vec.begin(),
              function_vec.end  (),
              [&comparison](const APIInterceptor::APIFunction& in_function_a,
                            const APIInterceptor::APIFunction& in_function_b)
              {
                  const uint64_t first_a  = get_count(comparison.first,  in_function_a);
                  const uint64_t first_b  = get_count(comparison.first,  in_function_b);
                  const uint64_t second_a = get_count(comparison.second, in_function_a);
                  const uint64_t second_b = get_count(comparison.second, in_function_b);
                  const uint64_t gap_a    = (first_a > second_a) ? first_a - second_a : second_a - first_a;
                  const uint64_t gap_b    = (first_b > second_b) ? first_b - second_b : second_b - first_b;

                  return (gap_a != gap_b) ? (gap_a > gap_b)
                                          : (in_function_a < in_function_b);
              });

    if (function_vec.empty() )
    {
        fprintf(stdout,
                "\nEvery function is called as often in the one as in the other.\n");
    }
    else
    {
        fprintf(stdout,
                "\nFunctions called a different number of times (%zu; the ones that differ most first):\n"
                "  %-48s %12s %12s\n",
                function_vec.size(),
                "",
                "first",
                "second");

        for (size_t n_function = 0;
                    n_function < std::min(function_vec.size(),
                                          N_FUNCTIONS_LISTED);
                  ++n_function)
        {
            const auto&    function          = function_vec.at(n_function);
            const char*    function_name_ptr = Capture::APIDumpNames::get_function_name(function);
            const uint64_t first_count       = get_count(comparison.first,
                                                         function);
            const uint64_t second_count      = get_count(comparison.second,
                                                         function);

            fprintf(stdout,
                    "  %-48s %12llu %12llu\n",
                    function_name_ptr,
                    static_cast<unsigned long long>(first_count),
                    static_cast<unsigned long long>(second_count) );
        }
    }

    if (comparison.has_same_call_sequence)
    {
        fprintf(stdout,
                "\nThe calls are the same functions in the same order.\n");
    }
    else
    {
        const char* first_function_name_ptr  = (comparison.first_difference_first_function == APIInterceptor::APIFUNCTION_UNKNOWN)  ? "ended"
                                                                                                                                    : Capture::APIDumpNames::get_function_name(comparison.first_difference_first_function);
        const char* second_function_name_ptr = (comparison.first_difference_second_function == APIInterceptor::APIFUNCTION_UNKNOWN) ? "ended"
                                                                                                                                    : Capture::APIDumpNames::get_function_name(comparison.first_difference_second_function);

        fprintf(stdout,
                "\nThe calls are the same functions in the same order up to call %llu (in frame %llu of the first): there the first has %s, and the second %s.\n",
                static_cast<unsigned long long>(comparison.first_difference_call_index),
                static_cast<unsigned long long>(comparison.first_difference_frame_index),
                first_function_name_ptr,
                second_function_name_ptr);
    }

    result = (comparison.has_same_call_sequence) ? EXIT_SUCCESS
                                                 : EXIT_FAILURE;
end:
    return result;
}
