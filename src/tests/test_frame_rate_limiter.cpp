/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Tests for FrameRateLimiter, with a clock that the test moves: a program that is faster than the limit is held to it, a slower one is left alone, and
 * a program that was late does not run faster to make up for it.
 */
#include <gtest/gtest.h>
#include "capture/api_dumper_dll/frame_rate_limiter.h"
#include <vector>

namespace
{
    constexpr int64_t N_TICKS_PER_SECOND = 1000;

    /* A program that takes some ticks to make a frame, held by a limiter of the frame rate it is given. */
    class LimitedProgram
    {
    public:
        explicit LimitedProgram(const uint32_t& in_max_frames_per_second)
            :m_limiter(in_max_frames_per_second,
                       N_TICKS_PER_SECOND,
                       [this]() { return m_now; },
                       [this](const int64_t& in_n_ticks) { m_now += in_n_ticks; m_n_slept_ticks += in_n_ticks; })
        {
            /* Stub */
        }

        int64_t get_n_slept_ticks() const
        {
            return m_n_slept_ticks;
        }

        int64_t get_now() const
        {
            return m_now;
        }

        /* Makes a frame of the time given, and presents it; returns when the frame was presented, before it was held. */
        int64_t make_frame(const int64_t& in_frame_n_ticks)
        {
            m_now += in_frame_n_ticks;

            const int64_t presented_at = m_now;

            m_limiter.hold();

            return presented_at;
        }

    private:
        int64_t                                 m_n_slept_ticks = 0;
        int64_t                                 m_now           = 1000; /* not 0 */
        Capture::APIDumperDLL::FrameRateLimiter m_limiter;
    };
}

TEST(FrameRateLimiter, TheFirstFrameIsNotHeld)
{
    LimitedProgram program(10); /* a frame every 100 ticks */

    program.make_frame(5);

    EXPECT_EQ(program.get_n_slept_ticks(),
              0);
}

TEST(FrameRateLimiter, AProgramThatIsFasterThanTheLimitIsHeldToIt)
{
    LimitedProgram program(10); /* a frame every 100 ticks */

    const int64_t start = program.get_now();

    for (uint32_t n_frame = 0;
                  n_frame < 50;
                ++n_frame)
    {
        program.make_frame(3); /* a frame takes 3 ticks of work */
    }

    /* 50 frames at 10 a second take 5 seconds (5000 ticks). */
    const int64_t n_elapsed_ticks = program.get_now() - start;

    EXPECT_GE(n_elapsed_ticks,
              4900);
    EXPECT_LE(n_elapsed_ticks,
              5100);
}

TEST(FrameRateLimiter, AProgramThatIsSlowerThanTheLimitIsNotHeldAtAll)
{
    LimitedProgram program(10); /* a frame every 100 ticks */

    for (uint32_t n_frame = 0;
                  n_frame < 20;
                ++n_frame)
    {
        program.make_frame(250);
    }

    EXPECT_EQ(program.get_n_slept_ticks(),
              0);
}

TEST(FrameRateLimiter, AProgramThatWasLateDoesNotRunFasterToMakeUpForIt)
{
    LimitedProgram program(10); /* a frame every 100 ticks */

    program.make_frame(3);
    program.make_frame(3);

    /* One frame that takes a whole second: it is late by nine intervals. */
    program.make_frame(1000);

    /* The frames after it are an interval apart again, not a burst of ten that catches up. */
    std::vector<int64_t> presented_at_vec;

    for (uint32_t n_frame = 0;
                  n_frame < 5;
                ++n_frame)
    {
        presented_at_vec.push_back(program.make_frame(3) );
    }

    for (size_t n_frame = 1;
                n_frame < presented_at_vec.size();
              ++n_frame)
    {
        EXPECT_GE(presented_at_vec.at(n_frame) - presented_at_vec.at(n_frame - 1),
                  100 - 4) << "frame " << n_frame;
    }
}
