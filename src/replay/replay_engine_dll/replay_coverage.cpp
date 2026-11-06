/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "capture/api_dump_loader/api_info.h"
#include "replay_coverage.h"

Replay::ReplayEngineDLL::ReplayCoverage::ReplayCoverage(const SupportFunc& in_support_func)
    :m_n_calls      (0),
     m_n_frames     (0),
     m_support_func (in_support_func)
{
    /* Stub */
}

void Replay::ReplayEngineDLL::ReplayCoverage::add_segment(const Capture::APIDumpLoader::Workload& in_segment)
{
    if (in_segment.pointer_n_bytes != 0)
    {
        m_report.pointer_n_bytes = in_segment.pointer_n_bytes;
    }

    for (const auto& call : *in_segment.dumped_api_call_vec_ptr)
    {
        const CallSupport support = m_support_func(call.func);

        if (support != CallSupport::REPLAYED)
        {
            auto entry_iterator = m_function_entry_map.find(call.func);

            if (entry_iterator == m_function_entry_map.end() )
            {
                FunctionEntry entry;

                entry.first_call_index  = m_n_calls;
                entry.first_frame_index = m_n_frames;
                entry.function          = call.func;
                entry.support           = support;

                entry_iterator = m_function_entry_map.emplace(call.func,
                                                              entry).first;
            }

            entry_iterator->second.n_calls++;
        }

        for (const auto* argument_vec_ptr : {&call.arg_in_vec, &call.arg_out_vec})
        {
            for (const auto& argument : *argument_vec_ptr)
            {
                if (argument.type != APIInterceptor::ARGTYPE_DATA_CHUNK_ID)
                {
                    continue;
                }

                const bool is_chunk_present = (Capture::APIDumpLoader::get_data_chunk_ptr(in_segment,
                                                                                         argument.get_data_chunk_id() ) != nullptr);

                if (is_chunk_present)
                {
                    continue;
                }

                if (m_report.n_missing_chunk_references == 0)
                {
                    m_report.first_missing_chunk_call_index  = m_n_calls;
                    m_report.first_missing_chunk_frame_index = m_n_frames;
                    m_report.first_missing_chunk_function    = call.func;
                }

                m_report.n_missing_chunk_references++;
            }
        }

        m_n_calls++;

        if (Capture::APIDumpLoader::is_frame_boundary(call) )
        {
            m_n_frames++;
        }
    }
}

Replay::ReplayEngineDLL::ReplayCoverage::Report Replay::ReplayEngineDLL::ReplayCoverage::get_report() const
{
    Report result = m_report;

    result.n_calls  = m_n_calls;
    result.n_frames = m_n_frames;

    for (const auto& entry_pair : m_function_entry_map)
    {
        result.function_entry_vec.push_back(entry_pair.second);

        if (entry_pair.second.support == CallSupport::UNSUPPORTED)
        {
            result.n_unsupported_calls += entry_pair.second.n_calls;
        }
        else
        {
            result.n_skipped_calls += entry_pair.second.n_calls;
        }
    }

    return result;
}

bool Replay::ReplayEngineDLL::ReplayCoverage::is_replayable(const Report& in_report)
{
    return (in_report.n_unsupported_calls        == 0 &&
            in_report.n_missing_chunk_references == 0);
}
