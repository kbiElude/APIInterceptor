/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef COMMON_CALLBACK_REGISTRY_H
#define COMMON_CALLBACK_REGISTRY_H

#include "common/callbacks.h"
#include "common/globals.h"
#include <atomic>
#include <utility>
#include <vector>

namespace APIInterceptor
{
    /* The callbacks that are called before and after the calls of each function. They are registered while the process starts, before
     * the hooks can run, and are not changed after that.
     */
    class CallbackRegistry
    {
    public:
        CallbackRegistry();

        /* Stops the callbacks for the calling thread, for good (the thread belongs to the interceptor). */
        void disable_for_this_thread();

        /* Return false if the callbacks are disabled for the thread, or the function has none. */
        bool get_post_callback(const APIFunction&       in_api_func,
                               PFNPOSTCALLBACKFUNCPROC* out_callback_func_ptr,
                               void**                   out_user_arg_ptr) const;
        bool get_pre_callback (const APIFunction&       in_api_func,
                               PFNPRECALLBACKFUNCPROC*  out_callback_func_ptr,
                               void**                   out_user_arg_ptr) const;

        void register_post_callback(const APIFunction&      in_function,
                                    PFNPOSTCALLBACKFUNCPROC in_callback_func_ptr,
                                    void*                   in_func_user_arg);
        void register_pre_callback (const APIFunction&      in_function,
                                    PFNPRECALLBACKFUNCPROC  in_callback_func_ptr,
                                    void*                   in_func_user_arg);

        /* Every hooked call asks for the registry (twice, with the post callback), so this is a load of a pointer and a test, not a function-local
         * static, whose guard costs a thread-local read each time.
         */
        static CallbackRegistry* get_ptr()
        {
            CallbackRegistry* result_ptr = m_instance_ptr.load(std::memory_order_acquire);

            if (result_ptr == nullptr)
            {
                result_ptr = create_instance_ptr();
            }

            return result_ptr;
        }

    private:
        typedef std::pair<PFNPOSTCALLBACKFUNCPROC, void*> PostCallback;
        typedef std::pair<PFNPRECALLBACKFUNCPROC,  void*> PreCallback;

        std::vector<PostCallback> m_post_callback_vec;
        std::vector<PreCallback>  m_pre_callback_vec;

        /* Makes the registry the first time it is asked for. Two threads can race to it; one registry wins and is never destroyed. */
        static CallbackRegistry* create_instance_ptr();

        static AI_THREADLOCAL bool            m_are_callbacks_enabled;
        static std::atomic<CallbackRegistry*> m_instance_ptr;
    };
}

#endif /* COMMON_CALLBACK_REGISTRY_H */
