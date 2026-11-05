/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "d3d7_call_executor.h"
#include "d3d8_call_executor.h"
#include "gl_call_executor.h"
#include "null_call_executor.h"
#include "replay_engine.h"
#include "win32_call_executor.h"
#include <algorithm>
#include <chrono>
#include <Windows.h>
#include <mmsystem.h>

Replay::ReplayEngineDLL::ReplayEngine::ReplayEngine()
    :m_frame_executor_ptr(&m_default_frame_executor),
     m_is_loaded         (false)
{
    for (const auto& group : Capture::APIDumpLoader::get_api_groups() )
    {
        m_executors.add(group,
                        std::make_shared<NullCallExecutor>() );
    }

    {
        const auto win32_executor_ptr = std::make_shared<Win32CallExecutor>(&m_remapper,
                                                                            [this]()
                                                                            {
                                                                                notify_window_closed();
                                                                            },
                                                                            [this](const WindowPlacement& in_placement)
                                                                            {
                                                                                notify_window_placed(in_placement);
                                                                            });

        m_executors.add(Capture::APIDumpLoader::APIGroup::GDI32,
                        win32_executor_ptr);
        m_executors.add(Capture::APIDumpLoader::APIGroup::USER32,
                        win32_executor_ptr);
        m_executors.add(Capture::APIDumpLoader::APIGroup::WGL,
                        win32_executor_ptr);
    }

    m_executors.add(Capture::APIDumpLoader::APIGroup::D3D7,
                    std::make_shared<D3D7CallExecutor>(&m_remapper) );
    m_executors.add(Capture::APIDumpLoader::APIGroup::D3D8,
                    std::make_shared<D3D8CallExecutor>(&m_remapper) );
    m_executors.add(Capture::APIDumpLoader::APIGroup::GL,
                    std::make_shared<GlCallExecutor>(&m_remapper) );
}

Replay::ReplayEngineDLL::ReplayEngine::~ReplayEngine()
{
    {
        std::lock_guard<std::mutex> lock(m_control.mutex);

        m_control.is_stop_requested = true;
    }

    m_control.cv.notify_all();

    if (m_thread.joinable() )
    {
        m_thread.join();
    }
}

void Replay::ReplayEngineDLL::ReplayEngine::add_call_executor(const Capture::APIDumpLoader::APIGroup& in_group,
                                                              const std::shared_ptr<ICallExecutor>&   in_executor_ptr)
{
    m_executors.add(in_group,
                    in_executor_ptr);
}

void Replay::ReplayEngineDLL::ReplayEngine::add_call_interceptor(ICallInterceptor* in_interceptor_ptr)
{
    std::lock_guard<std::mutex> lock(m_listeners.mutex);

    m_listeners.interceptor_ptr_vec.push_back(in_interceptor_ptr);

    m_listeners.n_interceptors = m_listeners.interceptor_ptr_vec.size();
}

void Replay::ReplayEngineDLL::ReplayEngine::add_replay_observer(IReplayObserver* in_observer_ptr)
{
    m_observers.add(in_observer_ptr);
}

void Replay::ReplayEngineDLL::ReplayEngine::complete_frame(bool* out_is_done_ptr)
{
    bool     is_interrupted = false;
    uint32_t n_frame        = 0;
    bool     should_stop    = false;

    for (const auto executor_ptr : m_executors.get_executor_ptr_vec() )
    {
        executor_ptr->on_frame_presented();
    }

    m_frame_executor_ptr->on_frame_presented();

    {
        std::lock_guard<std::mutex> lock(m_control.mutex);

        n_frame        = m_control.n_frames_presented;
        is_interrupted = (m_control.is_reset_requested || m_control.is_stop_requested);

        /* A frame which is the one asked for ends the playing, unless a reset is on its way: it is the frame to start over for that. */
        if (is_interrupted == false         &&
            m_control.has_stop_frame        &&
            n_frame >= m_control.stop_frame)
        {
            m_control.has_stop_frame = false;
            m_control.should_play    = false;
        }

        should_stop = (is_interrupted || m_control.should_play == false);

        m_control.n_frames_presented++;
    }

    notify_frame_presented(n_frame);

    if (should_stop)
    {
        /* Reset and stop are handled by the caller. */
        if (is_interrupted == false)
        {
            set_state(PlaybackState::PAUSED);
        }

        *out_is_done_ptr = true;
    }
}

bool Replay::ReplayEngineDLL::ReplayEngine::execute_call(const Capture::APIDumpLoader::DumpedAPICall& in_call,
                                                         const IChunkSource&                          in_chunk_source)
{
    std::string                    error;
    std::vector<ICallInterceptor*> interceptor_ptr_vec;
    uint32_t                       n_frame        = 0;
    bool                           result         = false;
    bool                           should_execute = true;

    n_frame = m_control.n_frames_presented;

    /* Most replays have no interceptor, and then nothing is locked or copied for the call. */
    if (m_listeners.n_interceptors != 0)
    {
        std::lock_guard<std::mutex> lock(m_listeners.mutex);

        interceptor_ptr_vec = m_listeners.interceptor_ptr_vec;
    }

    /* Every interceptor sees the call, even if another one has skipped it. */
    for (auto interceptor_ptr : interceptor_ptr_vec)
    {
        if (interceptor_ptr->should_execute_call(in_call,
                                                 n_frame) == false)
        {
            should_execute = false;
        }
    }

    if (should_execute)
    {
        const auto group = Capture::APIDumpLoader::get_api_group(in_call.func);

        if (m_executors.has_executor(group) == false)
        {
            fail("The workload holds a call of an unknown API.");

            goto end;
        }

        if (m_executors.get_executor_ptr(group)->execute(in_call,
                                                         in_chunk_source,
                                                        &error) == false)
        {
            fail(error);

            goto end;
        }

        m_control.n_calls_executed++;
    }

    for (auto interceptor_ptr : interceptor_ptr_vec)
    {
        interceptor_ptr->on_call_replayed(in_call,
                                          n_frame,
                                          should_execute);
    }

    result = true;

end:
    return result;
}

void Replay::ReplayEngineDLL::ReplayEngine::fail(const std::string& in_message)
{
    {
        std::lock_guard<std::mutex> lock(m_control.mutex);

        m_control.error_message  = in_message;
        m_control.has_stop_frame = false;
        m_control.should_play    = false;
    }

    set_state   (PlaybackState::FAILED);
    notify_error(in_message);
}

Replay::ReplayEngineDLL::ICallExecutor* Replay::ReplayEngineDLL::ReplayEngine::get_call_executor_ptr(const Capture::APIDumpLoader::APIGroup& in_group) const
{
    return m_executors.get_executor_ptr(in_group);
}

const std::vector<Replay::ReplayEngineDLL::ICallExecutor*>& Replay::ReplayEngineDLL::ReplayEngine::get_call_executor_ptr_vec() const
{
    return m_executors.get_executor_ptr_vec();
}

const Replay::ReplayEngineDLL::IChunkSource& Replay::ReplayEngineDLL::ReplayEngine::get_chunk_source() const
{
    return m_walker;
}

uint32_t Replay::ReplayEngineDLL::ReplayEngine::get_n_frames_presented() const
{
    return m_control.n_frames_presented;
}

Replay::ReplayEngineDLL::IPlaybackController* Replay::ReplayEngineDLL::ReplayEngine::get_playback_controller_ptr()
{
    return this;
}

Replay::ReplayEngineDLL::ObjectRemapper* Replay::ReplayEngineDLL::ReplayEngine::get_remapper_ptr()
{
    return &m_remapper;
}

const Capture::APIDumpLoader::Workload& Replay::ReplayEngineDLL::ReplayEngine::get_segment() const
{
    return m_walker.get_segment();
}

Replay::ReplayEngineDLL::PlaybackStatus Replay::ReplayEngineDLL::ReplayEngine::get_status() const
{
    PlaybackStatus result;

    {
        std::lock_guard<std::mutex> lock(m_control.mutex);

        result.error_message      = m_control.error_message;
        /* Past the end there is nothing to go on to; a stop frame that is the next one is a step. */
        const bool is_before_stop_frame = (m_control.is_reset_requested ||
                                           m_control.stop_frame > m_control.n_frames_presented);
        const bool is_going_on          = (m_control.state != PlaybackState::FAILED   &&
                                           m_control.state != PlaybackState::FINISHED);

        result.is_seeking         = (m_control.has_stop_frame &&
                                     m_control.should_play    &&
                                     is_before_stop_frame     &&
                                     is_going_on);
        result.n_calls_executed   = m_control.n_calls_executed;
        result.n_frames_presented = m_control.n_frames_presented;
        result.state              = m_control.state;
    }

    return result;
}

bool Replay::ReplayEngineDLL::ReplayEngine::load(const char*  in_filename_ptr,
                                                 std::string* out_error_ptr)
{
    bool result = false;

    if (m_is_loaded)
    {
        if (out_error_ptr != nullptr)
        {
            *out_error_ptr = "A workload has been loaded already.";
        }

        goto end;
    }

    if (m_walker.open(in_filename_ptr,
                      out_error_ptr) == false)
    {
        goto end;
    }

    m_is_loaded = true;
    m_thread    = std::thread(&ReplayEngine::thread_main,
                              this);
    result      = true;

end:
    return result;
}

void Replay::ReplayEngineDLL::ReplayEngine::notify_error(const std::string& in_message)
{
    m_observers.for_each([&](IReplayObserver* in_observer_ptr)
                         {
                             in_observer_ptr->on_error(in_message);
                         });
}

void Replay::ReplayEngineDLL::ReplayEngine::notify_frame_presented(const uint32_t& in_n_frame)
{
    m_observers.for_each([&](IReplayObserver* in_observer_ptr)
                         {
                             in_observer_ptr->on_frame_presented(in_n_frame);
                         });
}

void Replay::ReplayEngineDLL::ReplayEngine::notify_idle()
{
    for (const auto executor_ptr : m_executors.get_executor_ptr_vec() )
    {
        executor_ptr->on_idle();
    }
}

void Replay::ReplayEngineDLL::ReplayEngine::notify_window_closed()
{
    m_observers.for_each([](IReplayObserver* in_observer_ptr)
                         {
                             in_observer_ptr->on_window_closed();
                         });
}

void Replay::ReplayEngineDLL::ReplayEngine::notify_window_placed(const WindowPlacement& in_placement)
{
    m_observers.for_each([&](IReplayObserver* in_observer_ptr)
                         {
                             in_observer_ptr->on_window_placed(in_placement);
                         });
}

void Replay::ReplayEngineDLL::ReplayEngine::pause()
{
    std::lock_guard<std::mutex> lock(m_control.mutex);

    m_control.has_stop_frame = false;
    m_control.should_play    = false;
}

void Replay::ReplayEngineDLL::ReplayEngine::play()
{
    {
        std::lock_guard<std::mutex> lock(m_control.mutex);

        m_control.has_stop_frame = false;
        m_control.should_play    = true;
    }

    m_control.cv.notify_all();
}

void Replay::ReplayEngineDLL::ReplayEngine::play_to_frame(const uint32_t& in_n_frame)
{
    {
        std::lock_guard<std::mutex> lock(m_control.mutex);

        /* The frame which was presented last is the one before the count; the replay is at the frame asked for already. */
        const bool is_at_frame = (m_control.n_frames_presented == static_cast<uint32_t>(in_n_frame + 1) &&
                                  m_control.is_reset_requested == false);

        m_control.has_stop_frame = (is_at_frame == false);
        m_control.stop_frame     = in_n_frame;
        m_control.should_play    = (is_at_frame == false);

        /* A frame behind the replay is reached by starting over, which plays on (the first frame is played by it, and the playing goes on to the
         * frame because play is asked for as well).
         */
        if (is_at_frame == false &&
            m_control.n_frames_presented > in_n_frame)
        {
            m_control.is_reset_requested = true;
        }
    }

    m_control.cv.notify_all();
}

void Replay::ReplayEngineDLL::ReplayEngine::play_until_frame_boundary()
{
    bool is_done = false;

    set_state(PlaybackState::PLAYING);

    m_frame_executor_ptr->on_play_started();

    while (is_done == false)
    {
        bool has_workload_ended = false;

        if (m_frame_executor_ptr->execute_frame(this,
                                               &has_workload_ended) == false)
        {
            is_done = true;
        }
        else
        if (has_workload_ended)
        {
            {
                std::lock_guard<std::mutex> lock(m_control.mutex);

                m_control.has_stop_frame = false;
                m_control.should_play    = false;
            }

            set_state(PlaybackState::FINISHED);

            is_done = true;
        }
        else
        {
            complete_frame(&is_done);
        }
    }
}

bool Replay::ReplayEngineDLL::ReplayEngine::read_next_call(const Capture::APIDumpLoader::DumpedAPICall** out_call_ptr_ptr)
{
    return m_walker.read_next_call(out_call_ptr_ptr);
}

void Replay::ReplayEngineDLL::ReplayEngine::remove_call_interceptor(ICallInterceptor* in_interceptor_ptr)
{
    std::lock_guard<std::mutex> lock(m_listeners.mutex);

    m_listeners.interceptor_ptr_vec.erase(std::remove(m_listeners.interceptor_ptr_vec.begin(),
                                                      m_listeners.interceptor_ptr_vec.end  (),
                                                      in_interceptor_ptr),
                                          m_listeners.interceptor_ptr_vec.end() );

    m_listeners.n_interceptors = m_listeners.interceptor_ptr_vec.size();
}

void Replay::ReplayEngineDLL::ReplayEngine::remove_replay_observer(IReplayObserver* in_observer_ptr)
{
    m_observers.remove(in_observer_ptr);
}

void Replay::ReplayEngineDLL::ReplayEngine::reset()
{
    {
        std::lock_guard<std::mutex> lock(m_control.mutex);

        m_control.has_stop_frame     = false;
        m_control.is_reset_requested = true;
        m_control.should_play        = false;
    }

    m_control.cv.notify_all();
}

void Replay::ReplayEngineDLL::ReplayEngine::reset_executors(const bool& in_is_final)
{
    /* The executors which came later depend on the ones which came earlier (a device needs its window). */
    const auto executor_ptr_vec = m_executors.get_executor_ptr_vec();

    for (auto iterator  = executor_ptr_vec.rbegin();
              iterator != executor_ptr_vec.rend  ();
            ++iterator)
    {
        if (in_is_final)
        {
            (*iterator)->shutdown();
        }
        else
        {
            (*iterator)->reset();
        }
    }

    m_remapper.clear();
}

bool Replay::ReplayEngineDLL::ReplayEngine::rewind()
{
    std::string error;
    const bool  is_rewound = m_walker.rewind(&error);

    m_frame_executor_ptr->on_rewind();

    reset_executors(false); /* in_is_final */

    {
        std::lock_guard<std::mutex> lock(m_control.mutex);

        m_control.error_message      = "";
        m_control.n_calls_executed   = 0;
        m_control.n_frames_presented = 0;
    }

    if (is_rewound == false)
    {
        fail(error);
    }

    return is_rewound;
}

void Replay::ReplayEngineDLL::ReplayEngine::set_chunk_wanted_func(const Capture::APIDumpLoader::ChunkWantedFunc& in_func)
{
    m_walker.set_chunk_wanted_func(in_func);
}

void Replay::ReplayEngineDLL::ReplayEngine::set_frame_executor(IFrameExecutor* in_executor_ptr)
{
    m_frame_executor_ptr = (in_executor_ptr != nullptr) ? in_executor_ptr
                                                        : &m_default_frame_executor;
}

void Replay::ReplayEngineDLL::ReplayEngine::set_state(const PlaybackState& in_state)
{
    PlaybackState old_state;

    {
        std::lock_guard<std::mutex> lock(m_control.mutex);

        old_state       = m_control.state;
        m_control.state = in_state;
    }

    if (old_state != in_state)
    {
        m_observers.for_each([&](IReplayObserver* in_observer_ptr)
                             {
                                 in_observer_ptr->on_state_changed(old_state,
                                                                   in_state);
                             });
    }
}

void Replay::ReplayEngineDLL::ReplayEngine::set_windows_visible(const bool& in_are_visible)
{
    for (const auto executor_ptr : m_executors.get_executor_ptr_vec() )
    {
        executor_ptr->set_windows_visible(in_are_visible);
    }
}

void Replay::ReplayEngineDLL::ReplayEngine::thread_main()
{
    constexpr std::chrono::milliseconds IDLE_INTERVAL(10);

    const auto can_proceed_func = [this]()
    {
        const bool is_playable = (m_control.state == PlaybackState::IDLE ||
                                  m_control.state == PlaybackState::PAUSED);

        return (m_control.is_reset_requested           ||
                m_control.is_stop_requested            ||
                (m_control.should_play && is_playable) );
    };
    bool is_stopping = false;

    while (is_stopping == false)
    {
        bool should_reset = false;

        {
            std::unique_lock<std::mutex> lock(m_control.mutex);

            /* The windows of the replay belong to this thread: while it waits, they are given their messages. */
            while (can_proceed_func() == false)
            {
                if (m_control.cv.wait_for(lock,
                                          IDLE_INTERVAL,
                                          can_proceed_func) == false)
                {
                    lock.unlock();

                    notify_idle();

                    lock.lock();
                }
            }

            is_stopping                  = m_control.is_stop_requested;
            should_reset                 = m_control.is_reset_requested;
            m_control.is_reset_requested = false;
        }

        if (is_stopping)
        {
            continue;
        }

        if (should_reset)
        {
            /* The first frame is replayed, so that it is on the screen, and the replay waits there for play(): a reset
             * does not ask to play, so the replay stops at the first frame boundary.
             */
            if (rewind() )
            {
                play_until_frame_boundary();
            }
        }
        else
        {
            play_until_frame_boundary();
        }
    }

    reset_executors(true); /* in_is_final */
}
