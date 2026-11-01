/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callback_registry.h"

AI_THREADLOCAL bool APIInterceptor::CallbackRegistry::m_are_callbacks_enabled = true;

APIInterceptor::CallbackRegistry::CallbackRegistry()
    :m_post_callback_vec(APIInterceptor::APIFUNCTION_COUNT),
     m_pre_callback_vec (APIInterceptor::APIFUNCTION_COUNT)
{
    /* Stub */
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

APIInterceptor::CallbackRegistry* APIInterceptor::CallbackRegistry::get_ptr()
{
    /* Never destroyed: hooks can still run during shutdown. */
    static CallbackRegistry* instance_ptr = new CallbackRegistry();

    return instance_ptr;
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
