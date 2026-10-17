/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include <Windows.h>
#include "Common/callbacks.h"
#include "Common/types.h"
#include <assert.h>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <vector>

typedef std::vector<uint8_t>   U8Vec;
typedef std::unique_ptr<U8Vec> U8VecUniquePtr;

typedef std::pair<APIInterceptor::PFNPOSTCALLBACKFUNCPROC, void*> PostAPIFuncCallback;
typedef std::pair<APIInterceptor::PFNPRECALLBACKFUNCPROC,  void*> PreAPIFuncCallback;

/* All accesses to chunk_vec must be done with mutex held. */
struct DataChunkStore
{
    std::vector<U8VecUniquePtr> chunk_vec;
    std::mutex                  mutex;
};

/* Lets the dumper hold other threads back from entering intercepted API calls. cv and mutex let the threads wait for
 * the gate to open, and the gate owner wait for the threads to leave. The counters are atomic so that the (very hot)
 * path of entering and leaving a call takes no lock when the gate is open.
 */
struct Gate
{
    std::condition_variable cv;
    std::atomic<bool>       is_closed;
    std::mutex              mutex;
    std::atomic<uint32_t>   n_threads_inside;

    Gate()
        :is_closed       (false),
         n_threads_inside(0)
    {
        /* Stub */
    }
};

AI_THREADLOCAL bool                    g_callbacks_enabled          = true;
static         DataChunkStore          g_data_chunk_store;
static         Gate                    g_gate;
AI_THREADLOCAL uint32_t                g_gate_scope_depth           = 0;
AI_THREADLOCAL uint32_t                g_n_api_calls_intercepted    = 0;
static         auto                    g_post_api_func_callback_vec = std::vector<PostAPIFuncCallback>(APIInterceptor::APIFUNCTION_COUNT);
static         auto                    g_pre_api_func_callback_vec  = std::vector<PreAPIFuncCallback> (APIInterceptor::APIFUNCTION_COUNT);

/* Gate state is read and written with sequentially consistent atomics: a thread entering the gate increments the
 * counter and then checks the flag, while the thread closing it sets the flag and then checks the counter. Whichever
 * goes second sees the other, so a thread is never inside while the gate is reported as quiescent.
 */
static void enter_api_call_gate();
static void leave_api_call_gate();

void APIInterceptor::disable_callbacks_for_this_thread()
{
    g_callbacks_enabled = false;
}

static void enter_api_call_gate()
{
    for (;;)
    {
        g_gate.n_threads_inside++;

        if (g_gate.is_closed.load() == false)
        {
            break;
        }

        /* Back out, let the thread which closed the gate know, and wait for it to open. */
        g_gate.n_threads_inside--;

        {
            std::unique_lock<std::mutex> lock(g_gate.mutex);

            g_gate.cv.notify_all();
            g_gate.cv.wait      (lock,
                                 []() { return g_gate.is_closed.load() == false; });
        }
    }
}

bool APIInterceptor::get_data_chunk(const DataChunkID& in_data_chunk_id,
                                    const void**       out_data_ptr_ptr,
                                    uint32_t*          out_n_bytes_ptr)
{
    bool result = false;

    {
        std::lock_guard<std::mutex> lock(g_data_chunk_store.mutex);

        if (g_data_chunk_store.chunk_vec.size() > in_data_chunk_id         &&
            g_data_chunk_store.chunk_vec.at(in_data_chunk_id) != nullptr)
        {
            auto data_chunk_ptr = g_data_chunk_store.chunk_vec.at(in_data_chunk_id).get();

            *out_data_ptr_ptr = data_chunk_ptr->data ();
            *out_n_bytes_ptr  = static_cast<uint32_t>(data_chunk_ptr->size() );

            result = true;
        }
    }

    return result;
}

uint32_t APIInterceptor::get_n_data_chunks()
{
    uint32_t result = 0;

    {
        std::lock_guard<std::mutex> lock(g_data_chunk_store.mutex);

        result = static_cast<uint32_t>(g_data_chunk_store.chunk_vec.size() );
    }

    return result;
}

bool APIInterceptor::get_post_callback_for_function(const APIFunction&       in_api_func,
                                                    PFNPOSTCALLBACKFUNCPROC* out_callback_func_ptr,
                                                    void**                   out_user_arg_ptr)
{
    bool result = false;

    if (g_callbacks_enabled)
    {
        auto data_ptr = &g_post_api_func_callback_vec.at(static_cast<size_t>(in_api_func) );

        *out_callback_func_ptr = data_ptr->first;
        *out_user_arg_ptr      = data_ptr->second;

        result = (data_ptr->first != nullptr);
    }

    return result;
}

bool APIInterceptor::get_pre_callback_for_function(const APIFunction&                      in_api_func,
                                                   APIInterceptor::PFNPRECALLBACKFUNCPROC* out_callback_func_ptr,
                                                   void**                                  out_user_arg_ptr)
{
    bool result = false;

    if (g_callbacks_enabled)
    {
        auto data_ptr = &g_pre_api_func_callback_vec.at(static_cast<size_t>(in_api_func) );

        *out_callback_func_ptr = data_ptr->first;
        *out_user_arg_ptr      = data_ptr->second;

        result = (data_ptr->first != nullptr);
    }

    return result;
}

static void leave_api_call_gate()
{
    g_gate.n_threads_inside--;

    if (g_gate.is_closed.load() )
    {
        /* Taking the lock makes sure the thread waiting for the gate to quiesce is either not waiting yet (and will
         * see the new count), or is already waiting (and gets the notification).
         */
        {
            std::lock_guard<std::mutex> lock(g_gate.mutex);
        }

        g_gate.cv.notify_all();
    }
}

void APIInterceptor::on_api_call_interception_finished()
{
    assert(g_n_api_calls_intercepted > 0);

    g_n_api_calls_intercepted--;

    on_gate_scope_left();
}

bool APIInterceptor::on_api_call_interception_started()
{
    const bool result = (g_n_api_calls_intercepted == 0);

    on_gate_scope_entered();

    g_n_api_calls_intercepted++;

    return result;
}

void APIInterceptor::on_gate_scope_entered()
{
    /* Scopes inside other scopes are covered by the outermost one. */
    if (g_gate_scope_depth == 0)
    {
        enter_api_call_gate();
    }

    g_gate_scope_depth++;
}

void APIInterceptor::on_gate_scope_left()
{
    assert(g_gate_scope_depth > 0);

    g_gate_scope_depth--;

    if (g_gate_scope_depth == 0)
    {
        leave_api_call_gate();
    }
}

APIInterceptor::DataChunkID APIInterceptor::register_data_chunk(const void*     in_data_ptr,
                                                                const uint32_t& in_n_bytes)
{
    U8VecUniquePtr new_data_chunk_ptr;
    DataChunkID    result             = 0;

    new_data_chunk_ptr.reset(
        new U8Vec(in_n_bytes)
    );

    if (in_n_bytes != 0)
    {
        memcpy(new_data_chunk_ptr->data(),
               in_data_ptr,
               in_n_bytes);
    }

    {
        std::lock_guard<std::mutex> lock(g_data_chunk_store.mutex);

        result = static_cast<uint32_t>(g_data_chunk_store.chunk_vec.size() );

        g_data_chunk_store.chunk_vec.emplace_back(
            std::move(new_data_chunk_ptr)
        );
    }

    return result;
}

void APIInterceptor::register_for_post_callback(APIFunction                             in_function,
                                                APIInterceptor::PFNPOSTCALLBACKFUNCPROC in_callback_func_ptr,
                                                void*                                   in_func_user_arg)
{
    g_post_api_func_callback_vec[static_cast<uint32_t>(in_function)] = PostAPIFuncCallback{in_callback_func_ptr,
                                                                                           in_func_user_arg};
}

void APIInterceptor::register_for_pre_callback(APIFunction                            in_function,
                                               APIInterceptor::PFNPRECALLBACKFUNCPROC in_callback_func_ptr,
                                               void*                                  in_func_user_arg)
{
    g_pre_api_func_callback_vec[static_cast<uint32_t>(in_function)] = PreAPIFuncCallback{in_callback_func_ptr,
                                                                                         in_func_user_arg};
}

void APIInterceptor::release_data_chunk(const DataChunkID& in_data_chunk_id)
{
    {
        std::lock_guard<std::mutex> lock(g_data_chunk_store.mutex);

        if (g_data_chunk_store.chunk_vec.size() > in_data_chunk_id)
        {
            g_data_chunk_store.chunk_vec.at(in_data_chunk_id).reset();
        }
    }
}

void APIInterceptor::resume_api_calls()
{
    {
        std::lock_guard<std::mutex> lock(g_gate.mutex);

        g_gate.is_closed = false;
    }

    g_gate.cv.notify_all();
}

void APIInterceptor::take_data_chunks(const DataChunkID&                  in_first_data_chunk_id,
                                      const uint32_t&                     in_n_data_chunks,
                                      std::vector<std::vector<uint8_t> >* out_data_chunk_vec_ptr)
{
    out_data_chunk_vec_ptr->clear();
    out_data_chunk_vec_ptr->resize(in_n_data_chunks);

    {
        std::lock_guard<std::mutex> lock(g_data_chunk_store.mutex);

        for (uint32_t n_data_chunk = 0;
                      n_data_chunk < in_n_data_chunks;
                    ++n_data_chunk)
        {
            const DataChunkID data_chunk_id = in_first_data_chunk_id + n_data_chunk;

            if (data_chunk_id < g_data_chunk_store.chunk_vec.size()       &&
                g_data_chunk_store.chunk_vec.at(data_chunk_id) != nullptr)
            {
                out_data_chunk_vec_ptr->at(n_data_chunk) = std::move(*g_data_chunk_store.chunk_vec.at(data_chunk_id) );

                g_data_chunk_store.chunk_vec.at(data_chunk_id).reset();
            }
        }
    }
}

bool APIInterceptor::try_quiesce_api_calls(const uint32_t& in_timeout_ms)
{
    bool       expected_is_closed = false;
    const auto n_own_threads      = (g_gate_scope_depth > 0) ? 1u : 0u; /* the caller is inside a call itself */
    bool       result             = false;

    /* Someone else may be cutting a segment already. */
    if (g_gate.is_closed.compare_exchange_strong(expected_is_closed,
                                                 true) == false)
    {
        goto end;
    }

    {
        std::unique_lock<std::mutex> lock(g_gate.mutex);

        result = g_gate.cv.wait_for(lock,
                                    std::chrono::milliseconds(in_timeout_ms),
                                    [&]() { return g_gate.n_threads_inside.load() <= n_own_threads; });
    }

    if (result == false)
    {
        resume_api_calls();
    }

end:
    return result;
}
