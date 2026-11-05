/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef REPLAYENGINEDLL_I_PLAYBACK_CONTROLLER_H
#define REPLAYENGINEDLL_I_PLAYBACK_CONTROLLER_H

#include "Replay/ReplayEngineDLL/types.h"

namespace Replay
{
    namespace ReplayEngineDLL
    {
        /* Controls a replay from any thread. The functions return at once; a request takes effect at the next frame
         * boundary of the replay (at once, if the replay is not running). Observers tell when it did.
         */
        class IPlaybackController
        {
        public:
            virtual ~IPlaybackController() = default;

            virtual PlaybackStatus get_status() const = 0;

            /* Stops at the next frame boundary. */
            virtual void pause() = 0;

            /* Starts, or resumes. Does nothing once the replay has finished or failed. */
            virtual void play() = 0;

            /* Plays up to a frame and pauses after it has been presented. The frames are counted from 0, as the replay presents them. A frame
             * behind the replay is reached by starting over (see reset()), and a frame which the replay is at already is left as it is. If the
             * workload ends before the frame, the replay finishes. pause(), play() and reset() cancel it.
             */
            virtual void play_to_frame(const uint32_t& in_n_frame) = 0;

            /* Goes back to the start of the workload, replays its first frame, and pauses there until play(). The frame is
             * rendered, so it can be seen. Takes effect at the next frame boundary if the replay is running.
             */
            virtual void reset() = 0;

        };
    }
}

#endif /* REPLAYENGINEDLL_I_PLAYBACK_CONTROLLER_H */
