/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * What the replay can do with a workload, found without replaying it: which of its calls the replay has no code for, which it leaves out, and whether
 * the data chunks that its calls refer to are in it. A workload that was made by an older dumper, or of an API that the replay does not know all of,
 * fails in the middle of a long replay; this finds out at its start, from the same decisions (ICallExecutor::get_call_support) that the replay makes.
 *
 * The segments of the workload are added one after the other, as WorkloadReader reads them, and each is read in full: a chunk that was left out of one
 * (see WorkloadReader::Options::skip_data_chunks_above_n_bytes) is a chunk that is missing.
 */
#ifndef REPLAYENGINEDLL_REPLAY_COVERAGE_H
#define REPLAYENGINEDLL_REPLAY_COVERAGE_H

#include "capture/api_dump_loader/api_dump_loader.h"
#include "types.h"
#include <functional>
#include <map>
#include <stdint.h>
#include <vector>

namespace Replay
{
    namespace ReplayEngineDLL
    {
        class ReplayCoverage
        {
        public:
            /* Tells what the replay does with a call of the function (see ICallExecutor::get_call_support). */
            typedef std::function<CallSupport(const APIInterceptor::APIFunction&)> SupportFunc;

            /* A function that the replay does not replay, and where the workload first calls it. */
            struct FunctionEntry
            {
                uint64_t                    first_call_index  = 0;
                uint64_t                    first_frame_index = 0;
                APIInterceptor::APIFunction function          = APIInterceptor::APIFUNCTION_UNKNOWN;
                uint64_t                    n_calls           = 0;
                CallSupport                 support           = CallSupport::REPLAYED;
            };

            struct Report
            {
                uint64_t                    first_missing_chunk_call_index  = 0; /* of the first call that refers to a chunk which is not there */
                uint64_t                    first_missing_chunk_frame_index = 0;
                APIInterceptor::APIFunction first_missing_chunk_function    = APIInterceptor::APIFUNCTION_UNKNOWN;
                std::vector<FunctionEntry>  function_entry_vec;                  /* the functions with support other than REPLAYED, in the order of the enum */
                uint64_t                    n_calls                         = 0;
                uint64_t                    n_frames                        = 0; /* those that ended                                              */
                uint64_t                    n_missing_chunk_references      = 0;
                uint64_t                    n_skipped_calls                 = 0;
                uint64_t                    n_unsupported_calls             = 0;
                uint32_t                    pointer_n_bytes                 = 0; /* of the process that was dumped                                */
            };

            explicit ReplayCoverage(const SupportFunc& in_support_func);

            /* The segment after the ones added before it. */
            void add_segment(const Capture::APIDumpLoader::Workload& in_segment);

            Report get_report() const;

            /* True if replaying the workload would not fail for what is in the report: no call that the replay has no code for, and no missing chunk. */
            static bool is_replayable(const Report& in_report);

        private:
            std::map<APIInterceptor::APIFunction, FunctionEntry> m_function_entry_map; /* the calls of every function that is not replayed */
            uint64_t                                             m_n_calls;
            uint64_t                                             m_n_frames;
            Report                                               m_report;
            SupportFunc                                          m_support_func;
        };
    }
}

#endif /* REPLAYENGINEDLL_REPLAY_COVERAGE_H */
