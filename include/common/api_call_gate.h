/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef COMMON_API_CALL_GATE_H
#define COMMON_API_CALL_GATE_H

#include "common/globals.h"
#include <atomic>
#include <condition_variable>
#include <mutex>
#include <stdint.h>

namespace APIInterceptor
{
    /* Lets the dumper hold other threads back from entering intercepted API calls: the cv and the mutex let the threads wait for the
     * gate to open, and the gate owner wait for the threads to leave. The counters are atomic so that the (very hot) path of entering
     * and leaving a call takes no lock when the gate is open.
     *
     * Gate state is read and written with sequentially consistent atomics: a thread entering the gate increments the counter and then
     * checks the flag, while the thread closing it sets the flag and then checks the counter. Whichever goes second sees the other, so
     * a thread is never inside while the gate is reported as quiescent.
     */
    class ApiCallGate
    {
    public:
        ApiCallGate();

        void on_api_call_interception_finished();
        bool on_api_call_interception_started ();

        /* The thread counts as being inside an intercepted API call from the first scope it enters to the last one it leaves; scopes
         * inside other scopes are covered by the outermost one.
         */
        void on_scope_entered();
        void on_scope_left   ();

        void resume();

        /* The nesting of intercepted calls on the thread is forgotten, and later put back (see TopLevelScope). */
        void     resume_nesting (const uint32_t& in_depth);
        uint32_t suspend_nesting();

        /* Closes the gate and waits for the threads which are inside intercepted calls to leave (the caller, if it is inside one, does
         * not count). Returns false, and leaves the gate open, if that does not happen within the timeout, or if the gate is closed.
         */
        bool try_quiesce(const uint32_t& in_timeout_ms);

        static ApiCallGate* get_ptr();

    private:
        void enter();
        void leave();

        std::condition_variable m_cv;
        std::atomic<bool>       m_is_closed;
        std::mutex              m_mutex;
        std::atomic<uint32_t>   m_n_threads_inside;

        static AI_THREADLOCAL uint32_t m_n_api_calls_intercepted;
        static AI_THREADLOCAL uint32_t m_scope_depth;
    };
}

#endif /* COMMON_API_CALL_GATE_H */
