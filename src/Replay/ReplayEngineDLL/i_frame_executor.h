/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef REPLAYENGINEDLL_I_FRAME_EXECUTOR_H
#define REPLAYENGINEDLL_I_FRAME_EXECUTOR_H

#include "Capture/APIDumpLoader/APIDumpLoader.h"
#include "Capture/APIDumpLoader/api_info.h"
#include "i_call_executor.h"
#include "i_chunk_source.h"
#include <stdint.h>
#include <vector>

namespace Replay
{
    namespace ReplayEngineDLL
    {
        /* What the engine gives a frame executor to work with. */
        class IFrameHost
        {
        public:
            virtual ~IFrameHost() = default;

            /* Hands the call to the interceptors and to the executor of its API. Returns false once the replay has failed. */
            virtual bool execute_call(const Capture::APIDumpLoader::DumpedAPICall& in_call,
                                      const IChunkSource&                          in_chunk_source) = 0;

            /* Stops the replay with the error. */
            virtual void fail(const std::string& in_message) = 0;

            /* The executor of the API, or one which does nothing, if the API has none. */
            virtual ICallExecutor* get_call_executor_ptr(const Capture::APIDumpLoader::APIGroup& in_group) const = 0;

            /* Every executor once. */
            virtual const std::vector<ICallExecutor*>& get_call_executor_ptr_vec() const = 0;

            /* The chunks of the calls which read_next_call() gives. */
            virtual const IChunkSource& get_chunk_source() const = 0;

            /* Of the frames which have been presented. */
            virtual uint32_t get_n_frames_presented() const = 0;

            /* The segment of the workload which the last call was read from. */
            virtual const Capture::APIDumpLoader::Workload& get_segment() const = 0;

            /* False once there is no call left. The call and its chunks stay valid until the next call of this function. */
            virtual bool read_next_call(const Capture::APIDumpLoader::DumpedAPICall** out_call_ptr_ptr) = 0;
        };

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
