/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef REPLAYENGINEDLL_REPLAY_ENGINE_H
#define REPLAYENGINEDLL_REPLAY_ENGINE_H

#include "replay/replay_engine_dll/i_replay_engine.h"
#include "call_walker.h"
#include "executor_registry.h"
#include "i_frame_executor.h"
#include "i_frame_host.h"
#include "listener_list.h"
#include "object_remapper.h"
#include "sequential_frame_executor.h"
#include <atomic>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <vector>

namespace Replay
{
    namespace ReplayEngineDLL
    {
        /* Walks the workload on a thread of its own, and hands each call to the executor of its API. Pauses at frame boundaries
         * only, so that a paused replay is always between two frames. How the calls of a frame are read and executed is up to a
         * frame executor, which a program that replays more than the plain sequence of calls can replace.
         */
        class ReplayEngine : public IReplayEngine,
                             public IPlaybackController,
                             public IFrameHost
        {
        public:
            ReplayEngine();
            ~ReplayEngine();

            /* Replaces the executor of the API. Before the workload is loaded. */
            void                                    add_call_executor          (const Capture::APIDumpLoader::APIGroup&       in_group,
                                                                                const std::shared_ptr<ICallExecutor>&         in_executor_ptr);
            void                                    add_call_interceptor       (ICallInterceptor*                             in_interceptor_ptr) override;
            void                                    add_replay_observer        (IReplayObserver*                              in_observer_ptr)    override;
            bool                                    execute_call               (const Capture::APIDumpLoader::DumpedAPICall&  in_call,
                                                                                const IChunkSource&                           in_chunk_source) override;
            void                                    fail                       (const std::string&                            in_message)         override;
            ICallExecutor*                          get_call_executor_ptr      (const Capture::APIDumpLoader::APIGroup& in_group)           const override;
            const std::vector<ICallExecutor*>&      get_call_executor_ptr_vec  ()                                                                 const override;
            const IChunkSource&                     get_chunk_source           ()                                                                 const override;
            uint32_t                                get_n_frames_presented     ()                                                                 const override;
            IPlaybackController*                    get_playback_controller_ptr()                                                                 override;
            ObjectRemapper*                         get_remapper_ptr           ();
            const Capture::APIDumpLoader::Workload& get_segment                ()                                                                 const override;
            PlaybackStatus                          get_status                 ()                                                                 const override;
            bool                                    load                       (const char*                                   in_filename_ptr,
                                                                                std::string*                                  out_error_ptr) override;
            void                                    pause                      ()                                                                 override;
            void                                    play                       ()                                                                 override;
            void                                    play_to_frame              (const uint32_t&                               in_n_frame)         override;
            bool                                    read_next_call             (const Capture::APIDumpLoader::DumpedAPICall** out_call_ptr_ptr)   override;
            void                                    remove_call_interceptor    (ICallInterceptor*                             in_interceptor_ptr) override;
            void                                    remove_replay_observer     (IReplayObserver*                              in_observer_ptr)    override;
            void                                    reset                      ()                                                                 override;
            void                                    set_chunk_wanted_func      (const Capture::APIDumpLoader::ChunkWantedFunc& in_func);
            void                                    set_frame_executor         (IFrameExecutor*                               in_executor_ptr);
            void                                    set_windows_visible        (const bool&                                   in_are_visible);

        private:
            /* State shared with the replay thread. */
            struct Control
            {
                std::condition_variable cv;
                std::string             error_message;
                bool                    has_stop_frame     = false; /* the replay pauses after the frame which stop_frame says */
                bool                    is_reset_requested = false;
                bool                    is_stop_requested  = false;
                std::mutex              mutex;
                std::atomic<uint64_t>   n_calls_executed{0};   /* written by the replay thread, read by any */
                std::atomic<uint32_t>   n_frames_presented{0};
                bool                    should_play        = false;
                PlaybackState           state              = PlaybackState::IDLE;
                uint32_t                stop_frame         = 0;
            };

            /* Lock order: Control::mutex is never held while a listener is called. */
            struct Listeners
            {
                std::vector<ICallInterceptor*> interceptor_ptr_vec;
                std::mutex                     mutex;
                std::atomic<size_t>            n_interceptors{0}; /* the number above, to look at without the lock */
            };

            void complete_frame           (bool*                  out_is_done_ptr);
            void notify_error             (const std::string&     in_message);
            void notify_frame_presented   (const uint32_t&        in_n_frame);
            void notify_idle              ();
            void notify_window_closed     ();
            void notify_window_placed     (const WindowPlacement& in_placement);
            void play_until_frame_boundary();
            void reset_executors          (const bool&            in_is_final);
            bool rewind                   ();
            void set_state                (const PlaybackState&   in_state);
            void thread_main              ();

            mutable Control               m_control;
            ExecutorRegistry              m_executors;
            SequentialFrameExecutor       m_default_frame_executor;
            IFrameExecutor*               m_frame_executor_ptr;
            bool                          m_is_loaded;
            mutable Listeners             m_listeners;
            ListenerList<IReplayObserver> m_observers;
            ObjectRemapper                m_remapper;
            std::thread                   m_thread;
            CallWalker                    m_walker;
        };
    }
}

#endif /* REPLAYENGINEDLL_REPLAY_ENGINE_H */
