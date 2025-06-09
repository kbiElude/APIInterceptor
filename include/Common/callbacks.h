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
                                            uint32_t                   in_n_args_out,
                                            const APIFunctionArgument* in_args_out_ptr,
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

    bool        get_data_chunk     (const DataChunkID& in_data_chunk_id,
                                    const void**       out_data_ptr_ptr,
                                    uint32_t*          out_n_bytes_ptr);
    uint32_t    get_n_data_chunks  ();
    DataChunkID register_data_chunk(const void*     in_data_ptr,
                                    const uint32_t& in_n_bytes);

    void on_api_call_interception_finished();
    bool on_api_call_interception_started ();
}

#endif /* COMMON_CALLBACKS_H */