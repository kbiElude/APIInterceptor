/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef REPLAYENGINEDLL_I_CALL_INTERCEPTOR_H
#define REPLAYENGINEDLL_I_CALL_INTERCEPTOR_H

#include "capture/api_dump_loader/api_dump_loader.h"
#include "capture/api_dump_loader/types.h"
#include <vector>

namespace Replay
{
    namespace ReplayEngineDLL
    {
        /* Sees the calls of the workload around their replay (every call, or those of the APIs get_api_groups() names): the hook for analysis and for tools built on the replayer.
         * Called from the replay thread. The call is valid for the duration of the function only.
         */
        class ICallInterceptor
        {
        public:
            virtual ~ICallInterceptor() = default;

            /* The APIs whose calls the interceptor wants to see; none named: all of them. Asked when it is added. */
            virtual std::vector<Capture::APIDumpLoader::APIGroup> get_api_groups() const
            {
                return std::vector<Capture::APIDumpLoader::APIGroup>();
            }

            /* Called after the call was replayed, or skipped. */
            virtual void on_call_replayed(const Capture::APIDumpLoader::DumpedAPICall& in_call,
                                                   const uint32_t&                     in_n_frame,
                                                   const bool&                         in_was_executed) = 0;

            /* Returns false to skip the call. The call is skipped if any interceptor says so. */
            virtual bool should_execute_call(const Capture::APIDumpLoader::DumpedAPICall& in_call,
                                                      const uint32_t&                     in_n_frame) = 0;
        };
    }
}

#endif /* REPLAYENGINEDLL_I_CALL_INTERCEPTOR_H */
