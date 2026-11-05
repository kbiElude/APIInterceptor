/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Checks of the playback control of the replay engine: frame-boundary pausing, resetting and interception.
 */
#include <gtest/gtest.h>
#include "Replay/ReplayEngineDLL/entrypoints.h"
#include "workload_file_builder.h"
#include <chrono>
#include <thread>

namespace
{
    constexpr uint32_t N_CALLS_PER_FRAME = 2;
    constexpr uint32_t N_FRAMES          = 3;

    /* Pauses the replay, or skips the calls, as told. */
    class TestInterceptor : public Replay::ReplayEngineDLL::ICallInterceptor
    {
    public:
        TestInterceptor(Replay::ReplayEngineDLL::IPlaybackController* in_controller_ptr,
                                const bool&                           in_should_pause_on_first_call,
                                const bool&                           in_should_skip_calls)
            :m_controller_ptr            (in_controller_ptr),
             m_should_pause_on_first_call(in_should_pause_on_first_call),
             m_should_skip_calls         (in_should_skip_calls)
        {
            /* Stub */
        }

        void on_call_replayed(const Capture::APIDumpLoader::DumpedAPICall& in_call,
                                       const uint32_t&                     in_n_frame,
                                       const bool&                         in_was_executed) override
        {
            (void) in_call;
            (void) in_was_executed;

            if (m_should_pause_on_first_call &&
                in_n_frame == 0)
            {
                m_controller_ptr->pause();
            }
        }

        bool should_execute_call(const Capture::APIDumpLoader::DumpedAPICall& in_call,
                                          const uint32_t&                     in_n_frame) override
        {
            (void) in_call;
            (void) in_n_frame;

            return (m_should_skip_calls == false);
        }

    private:
        Replay::ReplayEngineDLL::IPlaybackController* m_controller_ptr;
        bool                                  m_should_pause_on_first_call;
        bool                                  m_should_skip_calls;
    };

    class ReplayEngineTest : public ::testing::Test
    {
    protected:
        void SetUp() override
        {
            std::vector<uint8_t> file_u8_vec;

            Tests::WorkloadFileBuilder::build_frames(&file_u8_vec,
                                                     N_FRAMES,
                                                     N_CALLS_PER_FRAME);
            Tests::WorkloadFileBuilder::write_file  (file_u8_vec);

            m_engine_ptr = Replay::ReplayEngineDLL::aiCreateReplayEngine();
        }

        void TearDown() override
        {
            Replay::ReplayEngineDLL::aiDestroyReplayEngine(m_engine_ptr);
            ::remove(Tests::WorkloadFileBuilder::get_filename_ptr() );
        }

        /* Polls: the replay runs on a thread of its own. */
        bool wait_for_state(const Replay::ReplayEngineDLL::PlaybackState& in_state)
        {
            constexpr auto TIMEOUT = std::chrono::seconds(10);

            const auto deadline = std::chrono::steady_clock::now() + TIMEOUT;
            bool       result   = false;

            while (std::chrono::steady_clock::now() < deadline)
            {
                if (m_engine_ptr->get_playback_controller_ptr()->get_status().state == in_state)
                {
                    result = true;

                    break;
                }

                std::this_thread::sleep_for(std::chrono::milliseconds(1) );
            }

            return result;
        }

        /* The count of the frames presented is what tells that a request was taken: the state may be the one it was. */
        bool wait_for_frames_presented(const uint32_t& in_n_frames)
        {
            constexpr auto TIMEOUT = std::chrono::seconds(10);

            const auto deadline = std::chrono::steady_clock::now() + TIMEOUT;
            bool       result   = false;

            while (std::chrono::steady_clock::now() < deadline)
            {
                if (m_engine_ptr->get_playback_controller_ptr()->get_status().n_frames_presented == in_n_frames)
                {
                    result = true;

                    break;
                }

                std::this_thread::sleep_for(std::chrono::milliseconds(1) );
            }

            return result;
        }

        Replay::ReplayEngineDLL::IReplayEngine* m_engine_ptr = nullptr;
    };
}

TEST_F(ReplayEngineTest, LoadFailsForMissingFile)
{
    std::string error;

    EXPECT_FALSE(m_engine_ptr->load("this_file_does_not_exist.workload",
                                   &error) );
    EXPECT_FALSE(error.empty() );
}

TEST_F(ReplayEngineTest, PlaysTheWholeWorkload)
{
    ASSERT_TRUE(m_engine_ptr->load(Tests::WorkloadFileBuilder::get_filename_ptr(),
                                   nullptr) );

    auto* controller_ptr = m_engine_ptr->get_playback_controller_ptr();

    EXPECT_EQ(controller_ptr->get_status().state,
              Replay::ReplayEngineDLL::PlaybackState::IDLE);

    controller_ptr->play();

    ASSERT_TRUE(wait_for_state(Replay::ReplayEngineDLL::PlaybackState::FINISHED) );

    EXPECT_EQ(controller_ptr->get_status().n_calls_executed,
              static_cast<uint64_t>(N_FRAMES * (N_CALLS_PER_FRAME + 1) ));
    EXPECT_EQ(controller_ptr->get_status().n_frames_presented,
              N_FRAMES);
}

TEST_F(ReplayEngineTest, PausesAtTheNextFrameBoundary)
{
    ASSERT_TRUE(m_engine_ptr->load(Tests::WorkloadFileBuilder::get_filename_ptr(),
                                   nullptr) );

    auto*           controller_ptr = m_engine_ptr->get_playback_controller_ptr();
    TestInterceptor interceptor    (controller_ptr,
                                    true,   /* in_should_pause_on_first_call */
                                    false); /* in_should_skip_calls          */

    m_engine_ptr->add_call_interceptor(&interceptor);

    controller_ptr->play();

    ASSERT_TRUE(wait_for_state(Replay::ReplayEngineDLL::PlaybackState::PAUSED) );

    /* The first frame was replayed in full, and nothing of the second one. */
    EXPECT_EQ(controller_ptr->get_status().n_calls_executed,
              static_cast<uint64_t>(N_CALLS_PER_FRAME + 1) );
    EXPECT_EQ(controller_ptr->get_status().n_frames_presented,
              1u);

    controller_ptr->play();

    ASSERT_TRUE(wait_for_state(Replay::ReplayEngineDLL::PlaybackState::FINISHED) );

    EXPECT_EQ(controller_ptr->get_status().n_frames_presented,
              N_FRAMES);

    m_engine_ptr->remove_call_interceptor(&interceptor);
}

TEST_F(ReplayEngineTest, ResetShowsTheFirstFrameAndWaits)
{
    ASSERT_TRUE(m_engine_ptr->load(Tests::WorkloadFileBuilder::get_filename_ptr(),
                                   nullptr) );

    auto* controller_ptr = m_engine_ptr->get_playback_controller_ptr();

    controller_ptr->play();

    ASSERT_TRUE(wait_for_state(Replay::ReplayEngineDLL::PlaybackState::FINISHED) );

    controller_ptr->reset();

    /* The first frame is replayed, and the replay waits for play(). */
    ASSERT_TRUE(wait_for_state(Replay::ReplayEngineDLL::PlaybackState::PAUSED) );

    EXPECT_EQ(controller_ptr->get_status().n_calls_executed,
              static_cast<uint64_t>(N_CALLS_PER_FRAME + 1) );
    EXPECT_EQ(controller_ptr->get_status().n_frames_presented,
              1u);

    controller_ptr->play();

    ASSERT_TRUE(wait_for_state(Replay::ReplayEngineDLL::PlaybackState::FINISHED) );

    EXPECT_EQ(controller_ptr->get_status().n_frames_presented,
              N_FRAMES);
}

TEST_F(ReplayEngineTest, SkippedCallsAreNotExecuted)
{
    ASSERT_TRUE(m_engine_ptr->load(Tests::WorkloadFileBuilder::get_filename_ptr(),
                                   nullptr) );

    auto*           controller_ptr = m_engine_ptr->get_playback_controller_ptr();
    TestInterceptor interceptor    (controller_ptr,
                                    false,  /* in_should_pause_on_first_call */
                                    true);  /* in_should_skip_calls          */

    m_engine_ptr->add_call_interceptor(&interceptor);

    controller_ptr->play();

    ASSERT_TRUE(wait_for_state(Replay::ReplayEngineDLL::PlaybackState::FINISHED) );

    EXPECT_EQ(controller_ptr->get_status().n_calls_executed,
              0u);
    EXPECT_EQ(controller_ptr->get_status().n_frames_presented,
              N_FRAMES);

    m_engine_ptr->remove_call_interceptor(&interceptor);
}

TEST_F(ReplayEngineTest, PlayToFramePausesAfterThatFrame)
{
    ASSERT_TRUE(m_engine_ptr->load(Tests::WorkloadFileBuilder::get_filename_ptr(),
                                   nullptr) );

    auto* controller_ptr = m_engine_ptr->get_playback_controller_ptr();

    controller_ptr->play_to_frame(1);

    ASSERT_TRUE(wait_for_state(Replay::ReplayEngineDLL::PlaybackState::PAUSED) );

    /* Frames 0 and 1 were presented, and nothing of the third. */
    EXPECT_EQ(controller_ptr->get_status().n_frames_presented,
              2u);
    EXPECT_EQ(controller_ptr->get_status().n_calls_executed,
              static_cast<uint64_t>(2 * (N_CALLS_PER_FRAME + 1) ));

    /* The last frame is one that it can pause after, too; and play() goes on from there. */
    controller_ptr->play_to_frame(N_FRAMES - 1);

    ASSERT_TRUE(wait_for_frames_presented(N_FRAMES) );
    ASSERT_TRUE(wait_for_state(Replay::ReplayEngineDLL::PlaybackState::PAUSED) );

    EXPECT_EQ(controller_ptr->get_status().n_frames_presented,
              N_FRAMES);

    controller_ptr->play();

    ASSERT_TRUE(wait_for_state(Replay::ReplayEngineDLL::PlaybackState::FINISHED) );
}

TEST_F(ReplayEngineTest, PlayToFrameBehindTheReplayStartsOverAndPausesAfterThatFrame)
{
    ASSERT_TRUE(m_engine_ptr->load(Tests::WorkloadFileBuilder::get_filename_ptr(),
                                   nullptr) );

    auto* controller_ptr = m_engine_ptr->get_playback_controller_ptr();

    controller_ptr->play();

    ASSERT_TRUE(wait_for_state(Replay::ReplayEngineDLL::PlaybackState::FINISHED) );

    controller_ptr->play_to_frame(1);

    ASSERT_TRUE(wait_for_state(Replay::ReplayEngineDLL::PlaybackState::PAUSED) );

    /* It started over: the calls and the frames are those of frames 0 and 1 alone. */
    EXPECT_EQ(controller_ptr->get_status().n_frames_presented,
              2u);
    EXPECT_EQ(controller_ptr->get_status().n_calls_executed,
              static_cast<uint64_t>(2 * (N_CALLS_PER_FRAME + 1) ));

    controller_ptr->play_to_frame(0);

    ASSERT_TRUE(wait_for_frames_presented(1u) );
    ASSERT_TRUE(wait_for_state(Replay::ReplayEngineDLL::PlaybackState::PAUSED) );

    EXPECT_EQ(controller_ptr->get_status().n_frames_presented,
              1u);
}

TEST_F(ReplayEngineTest, PlayToTheFrameTheReplayIsAtLeavesItAlone)
{
    ASSERT_TRUE(m_engine_ptr->load(Tests::WorkloadFileBuilder::get_filename_ptr(),
                                   nullptr) );

    auto* controller_ptr = m_engine_ptr->get_playback_controller_ptr();

    controller_ptr->play_to_frame(1);

    ASSERT_TRUE(wait_for_state(Replay::ReplayEngineDLL::PlaybackState::PAUSED) );

    controller_ptr->play_to_frame(1);

    std::this_thread::sleep_for(std::chrono::milliseconds(100) );

    EXPECT_EQ(controller_ptr->get_status().state,
              Replay::ReplayEngineDLL::PlaybackState::PAUSED);
    EXPECT_EQ(controller_ptr->get_status().n_frames_presented,
              2u);
}

TEST_F(ReplayEngineTest, PlayToAFrameBeyondTheEndFinishesTheReplay)
{
    ASSERT_TRUE(m_engine_ptr->load(Tests::WorkloadFileBuilder::get_filename_ptr(),
                                   nullptr) );

    auto* controller_ptr = m_engine_ptr->get_playback_controller_ptr();

    controller_ptr->play_to_frame(1000);

    ASSERT_TRUE(wait_for_state(Replay::ReplayEngineDLL::PlaybackState::FINISHED) );

    EXPECT_EQ(controller_ptr->get_status().n_frames_presented,
              N_FRAMES);
}

TEST_F(ReplayEngineTest, TheReplayIsNotSeekingOnceItHasReachedTheFrameItWasAskedFor)
{
    ASSERT_TRUE(m_engine_ptr->load(Tests::WorkloadFileBuilder::get_filename_ptr(),
                                   nullptr) );

    auto* controller_ptr = m_engine_ptr->get_playback_controller_ptr();

    EXPECT_FALSE(controller_ptr->get_status().is_seeking);

    controller_ptr->play_to_frame(1);

    ASSERT_TRUE(wait_for_frames_presented(2u) );
    ASSERT_TRUE(wait_for_state(Replay::ReplayEngineDLL::PlaybackState::PAUSED) );

    EXPECT_FALSE(controller_ptr->get_status().is_seeking);

    /* A step to the next frame is not a seek. */
    controller_ptr->play_to_frame(2);

    ASSERT_TRUE(wait_for_frames_presented(3u) );
    ASSERT_TRUE(wait_for_state(Replay::ReplayEngineDLL::PlaybackState::PAUSED) );

    EXPECT_FALSE(controller_ptr->get_status().is_seeking);

    controller_ptr->play();

    ASSERT_TRUE(wait_for_state(Replay::ReplayEngineDLL::PlaybackState::FINISHED) );

    EXPECT_FALSE(controller_ptr->get_status().is_seeking);
}
