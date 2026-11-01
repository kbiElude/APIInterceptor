/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef REPLAYPLAYER_STATE_NAMES_H
#define REPLAYPLAYER_STATE_NAMES_H

#include "Replay/ReplayEngineDLL/types.h"

namespace Replay
{
    namespace ReplayPlayer
    {
        /* How the front-ends of the player call the states of the playback. */
        class StateNames
        {
        public:
            static const char* get_state_name_ptr(const Replay::ReplayEngineDLL::PlaybackState& in_state);
        };
    }
}

#endif /* REPLAYPLAYER_STATE_NAMES_H */
