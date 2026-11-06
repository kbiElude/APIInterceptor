/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * The checks of what the replay can do: --verify (a workload) and --unreplayed-functions (no workload). The decisions are the ones of the executors of
 * the replay engine (ICallExecutor::get_call_support), asked without a replay.
 */
#include "Capture/APIDumpLoader/WorkloadReader.h"
#include "Capture/APIDumpLoader/api_info.h"
#include "Capture/APIDumpNames/function_names.h"
#include "printer.h"
#include "replay_coverage.h"
#include "replay_engine.h"
#include <stdio.h>
#include <stdlib.h>

namespace
{
    /* The threads that read segments ahead of the check (a 32-bit process holds the segments in its 4 GB). */
    constexpr uint32_t N_READER_THREADS_64_BIT = 6;
    constexpr uint32_t N_READER_THREADS_32_BIT = 3;

    /* What the engine's executor of the function's API says of it. */
    Replay::ReplayEngineDLL::CallSupport get_support(const Replay::ReplayEngineDLL::ReplayEngine& in_engine,
                                                     const APIInterceptor::APIFunction&           in_function)
    {
        return in_engine.get_call_executor_ptr(Capture::APIDumpLoader::get_api_group(in_function) )->get_call_support(in_function);
    }

    /* Prints the functions of the entries which have the support, one a line. */
    void print_entries(const std::vector<Replay::ReplayEngineDLL::ReplayCoverage::FunctionEntry>& in_entry_vec,
                       const Replay::ReplayEngineDLL::CallSupport&                                 in_support)
    {
        for (const auto& entry : in_entry_vec)
        {
            if (entry.support != in_support)
            {
                continue;
            }

            const char* function_name_ptr = Capture::APIDumpNames::get_function_name(entry.function);

            fprintf(stdout,
                    "    %-48s %10llu calls, the first is call %llu in frame %llu\n",
                    function_name_ptr,
                    static_cast<unsigned long long>(entry.n_calls),
                    static_cast<unsigned long long>(entry.first_call_index),
                    static_cast<unsigned long long>(entry.first_frame_index) );
        }
    }
}

int Capture::APIDumpPrinter::list_unreplayed_functions()
{
    Replay::ReplayEngineDLL::ReplayEngine engine;
    uint32_t                              n_skipped     = 0;
    uint32_t                              n_unsupported = 0;

    fprintf(stdout,
            "The functions which the dumper records and the replay has no code for (a workload that has a call of one cannot be replayed):\n");

    for (uint32_t n_function = 0;
                  n_function < static_cast<uint32_t>(APIInterceptor::APIFUNCTION_COUNT);
                ++n_function)
    {
        const auto function = static_cast<APIInterceptor::APIFunction>(n_function);
        const auto group    = Capture::APIDumpLoader::get_api_group(function);
        const auto support  = (group == Capture::APIDumpLoader::APIGroup::UNKNOWN) ? Replay::ReplayEngineDLL::CallSupport::REPLAYED
                                                                                   : get_support(engine,
                                                                                                 function);

        if (support == Replay::ReplayEngineDLL::CallSupport::SKIPPED)
        {
            n_skipped++;
        }

        if (support == Replay::ReplayEngineDLL::CallSupport::UNSUPPORTED)
        {
            const char* function_name_ptr = Capture::APIDumpNames::get_function_name(function);
            const char* group_name_ptr    = Capture::APIDumpLoader::get_api_group_name(group);

            n_unsupported++;

            fprintf(stdout,
                    "  [%s] %s\n",
                    group_name_ptr,
                    function_name_ptr);
        }
    }

    fprintf(stdout,
            "%u such functions. %u more are left out by the replay on purpose (what asks the API about itself, and what it does for itself).\n",
            n_unsupported,
            n_skipped);

    return (n_unsupported == 0) ? EXIT_SUCCESS
                                : EXIT_FAILURE;
}

int Capture::APIDumpPrinter::verify_replay(const Options& in_options)
{
    const uint32_t                                  n_threads = (sizeof(void*) == sizeof(uint64_t) ) ? N_READER_THREADS_64_BIT
                                                                                                     : N_READER_THREADS_32_BIT;
    Replay::ReplayEngineDLL::ReplayCoverage::Report report;
    std::string                                     reader_error;
    Capture::APIDumpLoader::WorkloadReader::Options reader_options;
    Capture::APIDumpLoader::WorkloadReaderUniquePtr reader_ptr;
    int                                             result        = EXIT_FAILURE;
    Capture::APIDumpLoader::Workload                segment;
    Replay::ReplayEngineDLL::ReplayEngine           engine;
    Replay::ReplayEngineDLL::ReplayCoverage         coverage([&engine](const APIInterceptor::APIFunction& in_function)
                                                             {
                                                                 return get_support(engine,
                                                                                    in_function);
                                                             });

    reader_options.n_threads = n_threads;

    reader_ptr = Capture::APIDumpLoader::WorkloadReader::create(in_options.workload_filename_ptr,
                                                                reader_options,
                                                               &reader_error);

    if (reader_ptr == nullptr)
    {
        fprintf(stderr,
                "[!] Could not open the specified workload: %s\n",
                reader_error.c_str() );

        goto end;
    }

    while (reader_ptr->read_next_segment(&segment) )
    {
        coverage.add_segment(segment);
    }

    report = coverage.get_report();

    fprintf(stdout,
            "Replay check of %s:\n"
            "  %llu calls in %llu frames, dumped by a %u-bit process (its Direct3D calls are replayed by a process of the same size).\n",
            in_options.workload_filename_ptr,
            static_cast<unsigned long long>(report.n_calls),
            static_cast<unsigned long long>(report.n_frames),
            report.pointer_n_bytes * 8);

    if (report.n_unsupported_calls != 0)
    {
        fprintf(stdout,
                "  The replay has no code for these functions, and fails on the first call of each (%llu calls in all):\n",
                static_cast<unsigned long long>(report.n_unsupported_calls) );

        print_entries(report.function_entry_vec,
                      Replay::ReplayEngineDLL::CallSupport::UNSUPPORTED);
    }

    if (report.n_skipped_calls != 0)
    {
        fprintf(stdout,
                "  The replay leaves these functions out (%llu calls in all), which is not a failure:\n",
                static_cast<unsigned long long>(report.n_skipped_calls) );

        print_entries(report.function_entry_vec,
                      Replay::ReplayEngineDLL::CallSupport::SKIPPED);
    }

    if (report.n_missing_chunk_references != 0)
    {
        const char* function_name_ptr = Capture::APIDumpNames::get_function_name(report.first_missing_chunk_function);

        fprintf(stdout,
                "  %llu references to data chunks which are not in the workload; the first is in call %llu (%s) in frame %llu.\n",
                static_cast<unsigned long long>(report.n_missing_chunk_references),
                static_cast<unsigned long long>(report.first_missing_chunk_call_index),
                function_name_ptr,
                static_cast<unsigned long long>(report.first_missing_chunk_frame_index) );
    }

    if (reader_ptr->is_truncated() )
    {
        fprintf(stdout,
                "  The workload ends unexpectedly: what follows was not checked.\n");
    }

    if (Replay::ReplayEngineDLL::ReplayCoverage::is_replayable(report) )
    {
        fprintf(stdout,
                "  Verdict: nothing in the workload stops a replay.\n");

        result = EXIT_SUCCESS;
    }
    else
    {
        fprintf(stdout,
                "  Verdict: a replay of the workload would fail.\n");
    }

end:
    return result;
}
