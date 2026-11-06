/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Executes nothing, and succeeds, for the tests of the replayer.
 */
#ifndef TESTS_STUB_CALL_EXECUTOR_H
#define TESTS_STUB_CALL_EXECUTOR_H

#include "i_call_executor.h"
#include "i_chunk_source.h"
#include <string>

namespace Tests
{
    /* Executes nothing, and succeeds. */
    class StubCallExecutor : public Replay::ReplayEngineDLL::ICallExecutor
    {
    public:
        bool execute           (const Capture::APIDumpLoader::DumpedAPICall& in_call,
                                const Replay::ReplayEngineDLL::IChunkSource& in_chunk_source,
                                std::string*                                 out_error_ptr) override;
        void on_frame_presented() override;
        void reset             () override;
    };
}

#endif /* TESTS_STUB_CALL_EXECUTOR_H */
