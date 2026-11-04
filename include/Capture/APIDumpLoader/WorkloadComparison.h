/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * What two captures have in common: what each holds (its calls by function, its frames, its data), and where their calls first differ. Captures of the same
 * program are rarely alike call for call (a program that waits on a clock, or that is run twice, makes other calls), so the function of each call is what is
 * compared, and not its arguments, which have addresses and times in them.
 *
 * The two workloads are read side by side, a segment at a time, so neither has to fit in memory.
 */
#ifndef APIDUMPLOADER_WORKLOAD_COMPARISON_H
#define APIDUMPLOADER_WORKLOAD_COMPARISON_H

#include "Common/types.h"
#include <map>
#include <stdint.h>
#include <string>

namespace Capture
{
    namespace APIDumpLoader
    {
        /* What one workload holds. */
        struct WorkloadSummary
        {
            std::map<APIInterceptor::APIFunction, uint64_t> call_count_map;
            uint64_t                                        n_calls            = 0;
            uint64_t                                        n_chunk_bytes      = 0;
            uint64_t                                        n_chunks           = 0;
            uint64_t                                        n_frames           = 0; /* the calls that end a frame */
            uint64_t                                        n_surfaces         = 0;
            uint32_t                                        pointer_n_bytes    = 0; /* of the process that was dumped */
        };

        struct WorkloadComparison
        {
            WorkloadSummary             first;
            uint64_t                    first_difference_call_index    = 0; /* the calls before it are the same functions in the same order */
            uint64_t                    first_difference_frame_index   = 0; /* the frame of the call in the first workload                  */
            APIInterceptor::APIFunction first_difference_first_function  = APIInterceptor::APIFUNCTION_UNKNOWN; /* UNKNOWN: the workload ended   */
            APIInterceptor::APIFunction first_difference_second_function = APIInterceptor::APIFUNCTION_UNKNOWN;
            bool                        has_same_call_sequence         = true;
            WorkloadSummary             second;
        };

        class WorkloadComparer
        {
        public:
            /* Reads both workloads to their ends. False, and why, if one cannot be opened. */
            static bool compare(const char*         in_first_filename_ptr,
                                const char*         in_second_filename_ptr,
                                const uint32_t&     in_n_threads,
                                WorkloadComparison* out_comparison_ptr,
                                std::string*        out_error_ptr);
        };
    }
}

#endif /* APIDUMPLOADER_WORKLOAD_COMPARISON_H */
