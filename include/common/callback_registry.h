/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef COMMON_CALLBACK_REGISTRY_H
#define COMMON_CALLBACK_REGISTRY_H

#include "common/callbacks.h"
#include "common/globals.h"
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

        static CallbackRegistry* get_ptr();

    private:
        typedef std::pair<PFNPOSTCALLBACKFUNCPROC, void*> PostCallback;
        typedef std::pair<PFNPRECALLBACKFUNCPROC,  void*> PreCallback;

        std::vector<PostCallback> m_post_callback_vec;
        std::vector<PreCallback>  m_pre_callback_vec;

        static AI_THREADLOCAL bool m_are_callbacks_enabled;
    };
}

#endif /* COMMON_CALLBACK_REGISTRY_H */
