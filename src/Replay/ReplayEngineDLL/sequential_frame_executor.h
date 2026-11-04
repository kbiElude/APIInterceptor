/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef REPLAYENGINEDLL_SEQUENTIAL_FRAME_EXECUTOR_H
#define REPLAYENGINEDLL_SEQUENTIAL_FRAME_EXECUTOR_H

#include "i_frame_executor.h"

namespace Replay
{
    namespace ReplayEngineDLL
    {
        /* Executes the calls of a frame once, in the order they were made, each as soon as it is read. */
        class SequentialFrameExecutor : public IFrameExecutor
        {
        public:
            bool execute_frame(IFrameHost* in_host_ptr,
                               bool*       out_has_workload_ended_ptr) override;
        };
    }
}

#endif /* REPLAYENGINEDLL_SEQUENTIAL_FRAME_EXECUTOR_H */
