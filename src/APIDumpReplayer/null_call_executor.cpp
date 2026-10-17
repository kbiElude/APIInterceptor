/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "null_call_executor.h"

APIDumpReplayer::NullCallExecutor::NullCallExecutor()
{
    /* Stub */
}

bool APIDumpReplayer::NullCallExecutor::execute(const APIDumpLoader::DumpedAPICall& in_call,
                                                const CallWalker&                   in_walker,
                                                std::string*                        out_error_ptr)
{
    (void) in_call;
    (void) in_walker;
    (void) out_error_ptr;

    return true;
}

void APIDumpReplayer::NullCallExecutor::on_frame_presented()
{
    /* Stub */
}

void APIDumpReplayer::NullCallExecutor::reset()
{
    /* Stub */
}
