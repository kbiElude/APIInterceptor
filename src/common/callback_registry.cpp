/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "common/callback_registry.h"

AI_THREADLOCAL bool                                      APIInterceptor::g_are_callbacks_enabled = true;
APIInterceptor::PostCallbackSlot                         APIInterceptor::g_post_callback_slot_array[APIInterceptor::APIFUNCTION_COUNT];
APIInterceptor::PreCallbackSlot                          APIInterceptor::g_pre_callback_slot_array [APIInterceptor::APIFUNCTION_COUNT];
std::atomic<APIInterceptor::CallbackRegistry*>           APIInterceptor::CallbackRegistry::m_instance_ptr = {nullptr};

APIInterceptor::CallbackRegistry::CallbackRegistry()
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
    g_are_callbacks_enabled = false;
}

void APIInterceptor::CallbackRegistry::register_post_callback(const APIFunction&      in_function,
                                                              PFNPOSTCALLBACKFUNCPROC in_callback_func_ptr,
                                                              void*                   in_func_user_arg)
{
    PostCallbackSlot& slot = g_post_callback_slot_array[static_cast<size_t>(in_function)];

    slot.func_ptr     = in_callback_func_ptr;
    slot.user_arg_ptr = in_func_user_arg;
}

void APIInterceptor::CallbackRegistry::register_pre_callback(const APIFunction&     in_function,
                                                             PFNPRECALLBACKFUNCPROC in_callback_func_ptr,
                                                             void*                  in_func_user_arg)
{
    PreCallbackSlot& slot = g_pre_callback_slot_array[static_cast<size_t>(in_function)];

    slot.func_ptr     = in_callback_func_ptr;
    slot.user_arg_ptr = in_func_user_arg;
}
