/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "null_call_executor.h"

Replay::ReplayEngineDLL::NullCallExecutor::NullCallExecutor()
{
    /* Stub */
}

bool Replay::ReplayEngineDLL::NullCallExecutor::execute(const Capture::APIDumpLoader::DumpedAPICall& in_call,
                                                          const IChunkSource&                          in_chunk_source,
                                                          std::string*                                 out_error_ptr)
{
    (void) in_call;
    (void) in_chunk_source;
    (void) out_error_ptr;

    return true;
}

Replay::ReplayEngineDLL::CallSupport Replay::ReplayEngineDLL::NullCallExecutor::get_call_support(const APIInterceptor::APIFunction& in_function) const
{
    (void) in_function;

    return CallSupport::SKIPPED;
}

void Replay::ReplayEngineDLL::NullCallExecutor::on_frame_presented()
{
    /* Stub */
}

void Replay::ReplayEngineDLL::NullCallExecutor::reset()
{
    /* Stub */
}
