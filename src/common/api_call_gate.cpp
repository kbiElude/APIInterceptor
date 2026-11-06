/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "common/api_call_gate.h"
#include <assert.h>
#include <chrono>

AI_THREADLOCAL uint32_t APIInterceptor::ApiCallGate::m_n_api_calls_intercepted = 0;
AI_THREADLOCAL uint32_t APIInterceptor::ApiCallGate::m_scope_depth             = 0;

APIInterceptor::ApiCallGate::ApiCallGate()
    :m_is_closed       (false),
     m_n_threads_inside(0)
{
    /* Stub */
}

void APIInterceptor::ApiCallGate::enter()
{
    for (;;)
    {
        m_n_threads_inside++;

        if (m_is_closed.load() == false)
        {
            break;
        }

        /* Back out, let the thread which closed the gate know, and wait for it to open. */
        m_n_threads_inside--;

        {
            std::unique_lock<std::mutex> lock(m_mutex);

            m_cv.notify_all();
            m_cv.wait      (lock,
                            [this]() { return m_is_closed.load() == false; });
        }
    }
}

APIInterceptor::ApiCallGate* APIInterceptor::ApiCallGate::get_ptr()
{
    /* Never destroyed: hooks can still run during shutdown. */
    static ApiCallGate* instance_ptr = new ApiCallGate();

    return instance_ptr;
}

void APIInterceptor::ApiCallGate::leave()
{
    m_n_threads_inside--;

    if (m_is_closed.load() )
    {
        /* Taking the lock makes sure the thread waiting for the gate to quiesce is either not waiting yet (and will see the new count),
         * or is already waiting (and gets the notification).
         */
        {
            std::lock_guard<std::mutex> lock(m_mutex);
        }

        m_cv.notify_all();
    }
}

void APIInterceptor::ApiCallGate::on_api_call_interception_finished()
{
    assert(m_n_api_calls_intercepted > 0);

    m_n_api_calls_intercepted--;

    on_scope_left();
}

bool APIInterceptor::ApiCallGate::on_api_call_interception_started()
{
    const bool result = (m_n_api_calls_intercepted == 0);

    on_scope_entered();

    m_n_api_calls_intercepted++;

    return result;
}

void APIInterceptor::ApiCallGate::on_scope_entered()
{
    if (m_scope_depth == 0)
    {
        enter();
    }

    m_scope_depth++;
}

void APIInterceptor::ApiCallGate::on_scope_left()
{
    assert(m_scope_depth > 0);

    m_scope_depth--;

    if (m_scope_depth == 0)
    {
        leave();
    }
}

void APIInterceptor::ApiCallGate::resume()
{
    {
        std::lock_guard<std::mutex> lock(m_mutex);

        m_is_closed = false;
    }

    m_cv.notify_all();
}

bool APIInterceptor::ApiCallGate::try_quiesce(const uint32_t& in_timeout_ms)
{
    bool       expected_is_closed = false;
    const auto n_own_threads      = (m_scope_depth > 0) ? 1u : 0u; /* the caller is inside a call itself */
    bool       result             = false;

    /* Someone else may be cutting a segment already. */
    if (m_is_closed.compare_exchange_strong(expected_is_closed,
                                            true) == false)
    {
        goto end;
    }

    {
        std::unique_lock<std::mutex> lock(m_mutex);

        result = m_cv.wait_for(lock,
                               std::chrono::milliseconds(in_timeout_ms),
                               [&]() { return m_n_threads_inside.load() <= n_own_threads; });
    }

    if (result == false)
    {
        resume();
    }

end:
    return result;
}

void APIInterceptor::ApiCallGate::resume_nesting(const uint32_t& in_depth)
{
    m_n_api_calls_intercepted = in_depth;
}

uint32_t APIInterceptor::ApiCallGate::suspend_nesting()
{
    const uint32_t result = m_n_api_calls_intercepted;

    m_n_api_calls_intercepted = 0;

    return result;
}
