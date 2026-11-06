/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "pausing_interceptor.h"

Tests::PausingInterceptor::PausingInterceptor(Replay::ReplayEngineDLL::IPlaybackController* in_controller_ptr,
                                              const bool&                                     in_should_pause_on_first_call,
                                              const bool&                                     in_should_skip_calls)
    :m_controller_ptr            (in_controller_ptr),
     m_should_pause_on_first_call(in_should_pause_on_first_call),
     m_should_skip_calls         (in_should_skip_calls)
{
    /* Stub */
}

void Tests::PausingInterceptor::on_call_replayed(const Capture::APIDumpLoader::DumpedAPICall& in_call,
                                                 const uint32_t&                              in_n_frame,
                                                 const bool&                                  in_was_executed)
{
    (void) in_call;
    (void) in_was_executed;

    if (m_should_pause_on_first_call &&
        in_n_frame == 0)
    {
        m_controller_ptr->pause();
    }
}

bool Tests::PausingInterceptor::should_execute_call(const Capture::APIDumpLoader::DumpedAPICall& in_call,
                                                    const uint32_t&                              in_n_frame)
{
    (void) in_call;
    (void) in_n_frame;

    return (m_should_skip_calls == false);
}
