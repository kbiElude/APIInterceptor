/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "state_names.h"

const char* APIDumpPlayer::StateNames::get_state_name_ptr(const APIDumpReplayer::PlaybackState& in_state)
{
    const char* result_ptr = "unknown";

    switch (in_state)
    {
        case APIDumpReplayer::PlaybackState::FAILED:
        {
            result_ptr = "failed";

            break;
        }

        case APIDumpReplayer::PlaybackState::FINISHED:
        {
            result_ptr = "finished";

            break;
        }

        case APIDumpReplayer::PlaybackState::IDLE:
        {
            result_ptr = "idle";

            break;
        }

        case APIDumpReplayer::PlaybackState::PAUSED:
        {
            result_ptr = "paused";

            break;
        }

        case APIDumpReplayer::PlaybackState::PLAYING:
        {
            result_ptr = "playing";

            break;
        }

        default:
        {
            break;
        }
    }

    return result_ptr;
}
