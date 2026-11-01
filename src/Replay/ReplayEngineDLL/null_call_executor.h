/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef REPLAYENGINEDLL_NULL_CALL_EXECUTOR_H
#define REPLAYENGINEDLL_NULL_CALL_EXECUTOR_H

#include "i_call_executor.h"

namespace Replay
{
    namespace ReplayEngineDLL
    {
        /* Accepts every call and does nothing with it: stands in for the APIs which have no executor yet. */
        class NullCallExecutor : public ICallExecutor
        {
        public:
            NullCallExecutor();

            bool execute           (const Capture::APIDumpLoader::DumpedAPICall& in_call,
                                             const CallWalker&                   in_walker,
                                             std::string*                        out_error_ptr) override;
            void on_frame_presented() override;
            void reset             () override;
        };
    }
}

#endif /* REPLAYENGINEDLL_NULL_CALL_EXECUTOR_H */
