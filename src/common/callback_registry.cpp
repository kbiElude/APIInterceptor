/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "common/callback_registry.h"

AI_THREADLOCAL bool                            APIInterceptor::CallbackRegistry::m_are_callbacks_enabled = true;
std::atomic<APIInterceptor::CallbackRegistry*> APIInterceptor::CallbackRegistry::m_instance_ptr      = {nullptr};

APIInterceptor::CallbackRegistry::CallbackRegistry()
    :m_post_callback_vec(APIInterceptor::APIFUNCTION_COUNT),
     m_pre_callback_vec (APIInterceptor::APIFUNCTION_COUNT)
{
    /* Stub */
}

APIInterceptor::CallbackRegistry* APIInterceptor::CallbackRegistry::create_instance_ptr()
{
    CallbackRegistry* expected_ptr = nullptr;
    CallbackRegistry* new_ptr      = new CallbackRegistry();

    /* Never destroyed: hooks can still run during shutdown. */
    if (m_instance_ptr.compare_exchange_strong(expected_ptr,
                                               new_ptr) == false)
    {
        delete new_ptr;

        new_ptr = expected_ptr;
    }

    return new_ptr;
}

void APIInterceptor::CallbackRegistry::disable_for_this_thread()
{
    m_are_callbacks_enabled = false;
}

bool APIInterceptor::CallbackRegistry::get_post_callback(const APIFunction&       in_api_func,
                                                         PFNPOSTCALLBACKFUNCPROC* out_callback_func_ptr,
                                                         void**                   out_user_arg_ptr) const
{
    bool result = false;

    if (m_are_callbacks_enabled)
    {
        const auto& callback = m_post_callback_vec.at(static_cast<size_t>(in_api_func) );

        *out_callback_func_ptr = callback.first;
        *out_user_arg_ptr      = callback.second;

        result = (callback.first != nullptr);
    }

    return result;
}

bool APIInterceptor::CallbackRegistry::get_pre_callback(const APIFunction&      in_api_func,
                                                        PFNPRECALLBACKFUNCPROC* out_callback_func_ptr,
                                                        void**                  out_user_arg_ptr) const
{
    bool result = false;

    if (m_are_callbacks_enabled)
    {
        const auto& callback = m_pre_callback_vec.at(static_cast<size_t>(in_api_func) );

        *out_callback_func_ptr = callback.first;
        *out_user_arg_ptr      = callback.second;

        result = (callback.first != nullptr);
    }

    return result;
}

void APIInterceptor::CallbackRegistry::register_post_callback(const APIFunction&      in_function,
                                                              PFNPOSTCALLBACKFUNCPROC in_callback_func_ptr,
                                                              void*                   in_func_user_arg)
{
    m_post_callback_vec.at(static_cast<size_t>(in_function) ) = PostCallback{in_callback_func_ptr,
                                                                             in_func_user_arg};
}

void APIInterceptor::CallbackRegistry::register_pre_callback(const APIFunction&     in_function,
                                                             PFNPRECALLBACKFUNCPROC in_callback_func_ptr,
                                                             void*                  in_func_user_arg)
{
    m_pre_callback_vec.at(static_cast<size_t>(in_function) ) = PreCallback{in_callback_func_ptr,
                                                                           in_func_user_arg};
}
