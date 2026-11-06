/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef REPLAYENGINEDLL_I_FRAME_EXECUTOR_H
#define REPLAYENGINEDLL_I_FRAME_EXECUTOR_H

#include "i_frame_host.h"

namespace Replay
{
    namespace ReplayEngineDLL
    {
        /* Replays one frame of the workload: what the engine does between two frame boundaries. The engine presents the frame, and
         * waits there if it is asked to pause, when this returns.
         */
        class IFrameExecutor
        {
        public:
            virtual ~IFrameExecutor() = default;

            /* Reads and executes the calls up to the end of the frame (the call that presents it included). Returns false if the replay
             * has failed (and has said so to the host). Sets the flag when the workload ended before the frame did.
             */
            virtual bool execute_frame(IFrameHost* in_host_ptr,
                                       bool*       out_has_workload_ended_ptr) = 0;

            /* The frame has been presented: the executors of the calls know it already. */
            virtual void on_frame_presented()
            {
                /* Stub */
            }

            /* The replay (re)starts to play: a pause or a reset must not make it hurry to catch up. */
            virtual void on_play_started()
            {
                /* Stub */
            }

            /* The replay goes back to the start of the workload. */
            virtual void on_rewind()
            {
                /* Stub */
            }

        };
    }
}

#endif /* REPLAYENGINEDLL_I_FRAME_EXECUTOR_H */
