/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef REPLAYPLAYERSUPPORT_STATE_NAMES_H
#define REPLAYPLAYERSUPPORT_STATE_NAMES_H

#include "replay/replay_engine_dll/types.h"

namespace Replay
{
    namespace ReplayPlayerSupport
    {
        /* How the front-ends of the player call the states of the playback. */
        class StateNames
        {
        public:
            static const char* get_state_name_ptr(const Replay::ReplayEngineDLL::PlaybackState& in_state);
        };
    }
}

#endif /* REPLAYPLAYERSUPPORT_STATE_NAMES_H */
