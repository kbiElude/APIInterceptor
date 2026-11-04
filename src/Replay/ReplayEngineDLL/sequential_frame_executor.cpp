/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Capture/APIDumpLoader/api_info.h"
#include "sequential_frame_executor.h"

bool Replay::ReplayEngineDLL::SequentialFrameExecutor::execute_frame(IFrameHost* in_host_ptr,
                                                                     bool*       out_has_workload_ended_ptr)
{
    bool has_boundary = false;
    bool result       = true;

    *out_has_workload_ended_ptr = false;

    while (has_boundary == false)
    {
        const Capture::APIDumpLoader::DumpedAPICall* call_ptr = nullptr;

        if (in_host_ptr->read_next_call(&call_ptr) == false)
        {
            *out_has_workload_ended_ptr = true;

            break;
        }

        if (in_host_ptr->execute_call(*call_ptr,
                                      in_host_ptr->get_chunk_source() ) == false)
        {
            result = false;

            break;
        }

        has_boundary = Capture::APIDumpLoader::is_frame_boundary(*call_ptr);
    }

    return result;
}
