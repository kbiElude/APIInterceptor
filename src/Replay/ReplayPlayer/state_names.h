/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef APIDUMPPLAYER_STATE_NAMES_H
#define APIDUMPPLAYER_STATE_NAMES_H

#include "Replay/ReplayEngineDLL/types.h"

namespace APIDumpPlayer
{
    /* How the front-ends of the player call the states of the playback. */
    class StateNames
    {
    public:
        static const char* get_state_name_ptr(const APIDumpReplayer::PlaybackState& in_state);
    };
}

#endif /* APIDUMPPLAYER_STATE_NAMES_H */
