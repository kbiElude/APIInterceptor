/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef APIDUMPREPLAYER_I_REPLAY_OBSERVER_H
#define APIDUMPREPLAYER_I_REPLAY_OBSERVER_H

#include "APIDumpReplayer/types.h"

namespace APIDumpReplayer
{
    /* Watches a replay. All the functions are called from the replay thread, so they must not block for long, and must
     * not call back into the engine's blocking functions.
     */
    class IReplayObserver
    {
    public:
        virtual ~IReplayObserver() = default;

        virtual void on_error          (const std::string&     in_message)   = 0;
        virtual void on_frame_presented(const uint32_t&        in_n_frame)   = 0;
        virtual void on_state_changed  (const PlaybackState&   in_old_state,
                                        const PlaybackState&   in_new_state) = 0;
        virtual void on_window_placed  (const WindowPlacement& in_placement) = 0;
    };
}

#endif /* APIDUMPREPLAYER_I_REPLAY_OBSERVER_H */
