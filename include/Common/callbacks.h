/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef COMMON_CALLBACKS_H
#define COMMON_CALLBACKS_H

#include "types.h"

namespace APIInterceptor
{
    /* Callback done prior to the API call being invoked. */
    typedef void (*PFNPRECALLBACKFUNCPROC)(APIFunction                in_api_func,
                                           uint32_t                   in_n_args,
                                           const APIFunctionArgument* in_args_ptr,
                                           void*                      in_user_arg_ptr,
                                           bool*                      out_should_pass_through_ptr);

    /* Callback done after the API call is invoked. */
    typedef void (*PFNPOSTCALLBACKFUNCPROC)(APIFunction                in_api_func,
                                            void*                      in_user_arg_ptr,
                                            const APIFunctionArgument* out_returned_value_ptr);

    void disable_callbacks_for_this_thread();
    bool get_post_callback_for_function   (const APIFunction&                      in_api_func,
                                           PFNPOSTCALLBACKFUNCPROC*                out_callback_func_ptr,
                                           void**                                  out_user_arg_ptr);
    bool get_pre_callback_for_function    (const APIFunction&                      in_api_func,
                                           PFNPRECALLBACKFUNCPROC*                 out_callback_func_ptr,
                                           void**                                  out_user_arg_ptr);
    void register_for_pre_callback        (APIFunction                             in_function,
                                           APIInterceptor::PFNPRECALLBACKFUNCPROC  in_callback_func_ptr,
                                           void*                                   in_func_user_arg);
    void register_for_post_callback       (APIFunction                             in_function,
                                           APIInterceptor::PFNPOSTCALLBACKFUNCPROC in_callback_func_ptr,
                                           void*                                   in_func_user_arg);
}

#endif /* COMMON_CALLBACKS_H */