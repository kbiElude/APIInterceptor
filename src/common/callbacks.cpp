/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "common/api_call_gate.h"
#include "common/callback_registry.h"
#include "common/callbacks.h"
#include "common/data_chunk_store.h"

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

uint32_t APIInterceptor::get_n_held_data_chunks()
{
    return DataChunkStore::get_ptr()->get_n_held_chunks();
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
    APICallGate::get_ptr()->on_api_call_interception_finished();
}

bool APIInterceptor::on_api_call_interception_started()
{
    return APICallGate::get_ptr()->on_api_call_interception_started();
}

void APIInterceptor::on_gate_scope_entered()
{
    APICallGate::get_ptr()->on_scope_entered();
}

void APIInterceptor::on_gate_scope_left()
{
    APICallGate::get_ptr()->on_scope_left();
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

void APIInterceptor::release_all_data_chunks()
{
    DataChunkStore::get_ptr()->release_all();
}

void APIInterceptor::release_data_chunk(const DataChunkID& in_data_chunk_id)
{
    DataChunkStore::get_ptr()->release(in_data_chunk_id);
}

void APIInterceptor::set_data_chunk_drain(const uint64_t&              in_capacity_n_bytes,
                                          const std::function<void()>& in_drain_func)
{
    DataChunkStore::get_ptr()->set_drain(in_capacity_n_bytes,
                                         in_drain_func);
}

void APIInterceptor::resume_api_call_nesting(const uint32_t& in_depth)
{
    APICallGate::get_ptr()->resume_nesting(in_depth);
}

void APIInterceptor::resume_api_calls()
{
    APICallGate::get_ptr()->resume();
}

uint32_t APIInterceptor::suspend_api_call_nesting()
{
    return APICallGate::get_ptr()->suspend_nesting();
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

uint32_t APIInterceptor::take_data_chunks_by_id(const std::vector<DataChunkID>&           in_data_chunk_id_vec,
                                                const std::vector<std::vector<uint8_t>*>& in_destination_ptr_vec,
                                                std::vector<uint8_t>*                     out_is_taken_u8_vec_ptr)
{
    return DataChunkStore::get_ptr()->take_chunks(in_data_chunk_id_vec,
                                                  in_destination_ptr_vec,
                                                  out_is_taken_u8_vec_ptr);
}

bool APIInterceptor::try_quiesce_api_calls(const uint32_t& in_timeout_ms)
{
    return APICallGate::get_ptr()->try_quiesce(in_timeout_ms);
}
