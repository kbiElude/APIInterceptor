/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "stub_call_executor.h"

bool Tests::StubCallExecutor::execute(const Capture::APIDumpLoader::DumpedAPICall& in_call,
                                      const Replay::ReplayEngineDLL::IChunkSource& in_chunk_source,
                                      std::string*                                 out_error_ptr)
{
    (void) in_call;
    (void) in_chunk_source;
    (void) out_error_ptr;

    return true;
}

void Tests::StubCallExecutor::on_frame_presented()
{
    /* Stub */
}

void Tests::StubCallExecutor::reset()
{
    /* Stub */
}
