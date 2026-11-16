/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Holds an application to a number of frames a second while it is dumped. A program that has no limit of its own (an old demo that does not wait for
 * the screen) makes thousands of frames a second, which is far more than anyone needs to analyze or replay it, and makes a capture of it enormous.
 */
#if !defined(APIDUMPERDLL_FRAME_RATE_LIMITER_H)
#define APIDUMPERDLL_FRAME_RATE_LIMITER_H

#include <functional>
#include <memory>
#include <mutex>
#include <stdint.h>

namespace Capture
{
    namespace APIDumperDLL
    {
        class FrameRateLimiter;

        typedef std::unique_ptr<FrameRateLimiter> FrameRateLimiterUniquePtr;

        class FrameRateLimiter
        {
        public:
            /* The time, in ticks (in_n_ticks_per_second of them a second). */
            typedef std::function<int64_t()> NowFunc;

            /* Waits for this many ticks. */
            typedef std::function<void(const int64_t&)> SleepFunc;

            /* in_max_frames_per_second must be above 0. */
            FrameRateLimiter(const uint32_t&  in_max_frames_per_second,
                             const int64_t&   in_n_ticks_per_second,
                             const NowFunc&   in_now_func,
                             const SleepFunc& in_sleep_func);

            /* Call it when a frame has been presented: it waits until the next frame is due, so that frames are at least a frame interval apart. The first
             * frame is not held. A program that is late is not held, and does not run faster afterwards to make up for it. Any thread.
             */
            void hold();

        private:
            int64_t    m_interval_n_ticks;
            std::mutex m_mutex;
            int64_t    m_next_due_ticks;   /* 0: no frame yet; guarded by m_mutex */
            NowFunc    m_now_func;
            SleepFunc  m_sleep_func;
        };
    }
}

#endif /* APIDUMPERDLL_FRAME_RATE_LIMITER_H */
