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
    DataChunkID register_data_chunk(const void*        in_data_ptr,
                                    const uint32_t&    in_n_bytes);
    void        release_data_chunk (const DataChunkID& in_data_chunk_id);

    /* Moves the contents of the data chunks out of the store, in one go. A chunk which is not there comes out empty. */
    void take_data_chunks(const DataChunkID&                  in_first_data_chunk_id,
                          const uint32_t&                     in_n_data_chunks,
                          std::vector<std::vector<uint8_t> >* out_data_chunk_vec_ptr);

    /* The dumper cuts the workload into segments, and a cut must not fall between the moment a call registers its data
     * chunks and the moment the call is recorded. For that, it closes a gate which every thread passes when it enters
     * an intercepted API call (see Tracker and GateScope), and waits for the threads which are inside one to leave.
     *
     * Must be called from within an intercepted API call (e.g. from a callback). Returns false, and leaves the gate
     * open, if other threads are still inside intercepted calls after in_timeout_ms. Otherwise, other threads are held
     * back from entering intercepted calls until resume_api_calls() is called.
     */
    void resume_api_calls     ();
    bool try_quiesce_api_calls(const uint32_t& in_timeout_ms);

    void on_api_call_interception_finished();
    bool on_api_call_interception_started ();

    /* Used by Tracker and GateScope: the thread counts as being inside an intercepted API call from the first scope it
     * enters to the last one it leaves.
     */
    void on_gate_scope_entered();
    void on_gate_scope_left   ();
}

#endif /* COMMON_CALLBACKS_H */
