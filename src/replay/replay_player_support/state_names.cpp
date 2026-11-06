/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "state_names.h"
#include "common/macros.h"

const char* Replay::ReplayPlayerSupport::StateNames::get_state_name_ptr(const Replay::ReplayEngineDLL::PlaybackState& in_state)
{
    const char* result_ptr = "unknown";

    switch (in_state)
    {
        case Replay::ReplayEngineDLL::PlaybackState::FAILED:
        {
            result_ptr = "failed";

            break;
        }

        case Replay::ReplayEngineDLL::PlaybackState::FINISHED:
        {
            result_ptr = "finished";

            break;
        }

        case Replay::ReplayEngineDLL::PlaybackState::IDLE:
        {
            result_ptr = "idle";

            break;
        }

        case Replay::ReplayEngineDLL::PlaybackState::PAUSED:
        {
            result_ptr = "paused";

            break;
        }

        case Replay::ReplayEngineDLL::PlaybackState::PLAYING:
        {
            result_ptr = "playing";

            break;
        }

        default:
        {
            AI_FAIL_UNSUPPORTED(in_state);

            break;
        }
    }

    return result_ptr;
}
