/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/api_call_gate.h"
#include "Common/callback_registry.h"
#include "Common/callbacks.h"
#include "Common/data_chunk_store.h"

void APIInterceptor::disable_callbacks_for_this_thread()
{
    CallbackRegistry::get_ptr()->disable_for_this_thread();
}

bool APIInterceptor::get_data_chunk(const DataChunkID& in_data_chunk_id,
                                    const void**       out_data_ptr_ptr,
                                    uint32_t*          out_n_bytes_ptr)
{
    return DataChunkStore::get_ptr()->get(in_data_chunk_id,
                                          out_data_ptr_ptr,
                                          out_n_bytes_ptr);
}

uint32_t APIInterceptor::get_n_data_chunks()
{
    return DataChunkStore::get_ptr()->get_n_chunks();
}

bool APIInterceptor::get_post_callback_for_function(const APIFunction&       in_api_func,
                                                    PFNPOSTCALLBACKFUNCPROC* out_callback_func_ptr,
                                                    void**                   out_user_arg_ptr)
{
    return CallbackRegistry::get_ptr()->get_post_callback(in_api_func,
                                                          out_callback_func_ptr,
                                                          out_user_arg_ptr);
}

bool APIInterceptor::get_pre_callback_for_function(const APIFunction&                      in_api_func,
                                                   APIInterceptor::PFNPRECALLBACKFUNCPROC* out_callback_func_ptr,
                                                   void**                                  out_user_arg_ptr)
{
    return CallbackRegistry::get_ptr()->get_pre_callback(in_api_func,
                                                         out_callback_func_ptr,
                                                         out_user_arg_ptr);
}

void APIInterceptor::on_api_call_interception_finished()
{
    ApiCallGate::get_ptr()->on_api_call_interception_finished();
}

bool APIInterceptor::on_api_call_interception_started()
{
    return ApiCallGate::get_ptr()->on_api_call_interception_started();
}

void APIInterceptor::on_gate_scope_entered()
{
    ApiCallGate::get_ptr()->on_scope_entered();
}

void APIInterceptor::on_gate_scope_left()
{
    ApiCallGate::get_ptr()->on_scope_left();
}

APIInterceptor::DataChunkID APIInterceptor::register_data_chunk(const void*     in_data_ptr,
                                                                const uint32_t& in_n_bytes)
{
    return DataChunkStore::get_ptr()->register_chunk(in_data_ptr,
                                                     in_n_bytes);
}

void APIInterceptor::register_for_post_callback(APIFunction                             in_function,
                                                APIInterceptor::PFNPOSTCALLBACKFUNCPROC in_callback_func_ptr,
                                                void*                                   in_func_user_arg)
{
    CallbackRegistry::get_ptr()->register_post_callback(in_function,
                                                        in_callback_func_ptr,
                                                        in_func_user_arg);
}

void APIInterceptor::register_for_pre_callback(APIFunction                            in_function,
                                               APIInterceptor::PFNPRECALLBACKFUNCPROC in_callback_func_ptr,
                                               void*                                  in_func_user_arg)
{
    CallbackRegistry::get_ptr()->register_pre_callback(in_function,
                                                       in_callback_func_ptr,
                                                       in_func_user_arg);
}

void APIInterceptor::release_data_chunk(const DataChunkID& in_data_chunk_id)
{
    DataChunkStore::get_ptr()->release(in_data_chunk_id);
}

void APIInterceptor::resume_api_calls()
{
    ApiCallGate::get_ptr()->resume();
}

bool APIInterceptor::take_data_chunk(const DataChunkID&    in_data_chunk_id,
                                     std::vector<uint8_t>* out_data_chunk_ptr)
{
    return DataChunkStore::get_ptr()->take(in_data_chunk_id,
                                           out_data_chunk_ptr);
}

void APIInterceptor::take_data_chunks(const DataChunkID&                  in_first_data_chunk_id,
                                      const uint32_t&                     in_n_data_chunks,
                                      std::vector<std::vector<uint8_t> >* out_data_chunk_vec_ptr)
{
    DataChunkStore::get_ptr()->take_range(in_first_data_chunk_id,
                                          in_n_data_chunks,
                                          out_data_chunk_vec_ptr);
}

bool APIInterceptor::try_quiesce_api_calls(const uint32_t& in_timeout_ms)
{
    return ApiCallGate::get_ptr()->try_quiesce(in_timeout_ms);
}
