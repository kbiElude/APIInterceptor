/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Pauses the replay, or skips the calls, as told, for the tests of the replayer.
 */
#ifndef TESTS_PAUSING_INTERCEPTOR_H
#define TESTS_PAUSING_INTERCEPTOR_H

#include "replay/replay_engine_dll/i_call_interceptor.h"
#include "replay/replay_engine_dll/i_playback_controller.h"

namespace Tests
{
    /* Pauses the replay, or skips the calls, as told. */
    class PausingInterceptor : public Replay::ReplayEngineDLL::ICallInterceptor
    {
    public:
        PausingInterceptor(Replay::ReplayEngineDLL::IPlaybackController* in_controller_ptr,
                           const bool&                                     in_should_pause_on_first_call,
                           const bool&                                     in_should_skip_calls);

        void on_call_replayed   (const Capture::APIDumpLoader::DumpedAPICall& in_call,
                                 const uint32_t&                              in_n_frame,
                                 const bool&                                  in_was_executed) override;
        bool should_execute_call(const Capture::APIDumpLoader::DumpedAPICall& in_call,
                                 const uint32_t&                              in_n_frame) override;

    private:
        Replay::ReplayEngineDLL::IPlaybackController* m_controller_ptr;
        bool                                            m_should_pause_on_first_call;
        bool                                            m_should_skip_calls;
    };
}

#endif /* TESTS_PAUSING_INTERCEPTOR_H */
