/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "frame_rate_limiter.h"

Capture::APIDumperDLL::FrameRateLimiter::FrameRateLimiter(const uint32_t&  in_max_frames_per_second,
                                                          const int64_t&   in_n_ticks_per_second,
                                                          const NowFunc&   in_now_func,
                                                          const SleepFunc& in_sleep_func)
    :m_interval_n_ticks(in_n_ticks_per_second / static_cast<int64_t>(in_max_frames_per_second) ),
     m_next_due_ticks  (0),
     m_now_func        (in_now_func),
     m_sleep_func      (in_sleep_func)
{
    /* Stub */
}

void Capture::APIDumperDLL::FrameRateLimiter::hold()
{
    int64_t n_ticks_to_sleep = 0;

    {
        std::lock_guard<std::mutex> lock(m_mutex);

        const int64_t now = m_now_func();

        if (m_next_due_ticks == 0)
        {
            m_next_due_ticks = now + m_interval_n_ticks;
        }
        else
        if (now >= m_next_due_ticks)
        {
            /* On time or late: not held. Being more than a frame late is not made up for by running faster: the next frame is due an interval from now. */
            m_next_due_ticks = (now > m_next_due_ticks + m_interval_n_ticks) ? now + m_interval_n_ticks
                                                                             : m_next_due_ticks + m_interval_n_ticks;
        }
        else
        {
            n_ticks_to_sleep  = m_next_due_ticks - now;
            m_next_due_ticks += m_interval_n_ticks;
        }
    }

    if (n_ticks_to_sleep > 0)
    {
        m_sleep_func(n_ticks_to_sleep);
    }
}
