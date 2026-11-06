/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Capture/APIDumpLoader/workload_comparison.h"
#include "Capture/APIDumpLoader/workload_reader.h"
#include "Capture/APIDumpLoader/api_info.h"

namespace
{
    /* One workload, read call by call. */
    class CallCursor
    {
    public:
        explicit CallCursor(Capture::APIDumpLoader::WorkloadReaderUniquePtr in_reader_ptr)
            :m_n_call_in_segment(0),
             m_reader_ptr       (std::move(in_reader_ptr) )
        {
            m_summary.pointer_n_bytes = m_reader_ptr->get_pointer_n_bytes();
        }

        /* The call that the cursor is at, or nullptr if there is none left. */
        const Capture::APIDumpLoader::DumpedAPICall* get_call_ptr()
        {
            while (m_segment.dumped_api_call_vec_ptr == nullptr                               ||
                   m_n_call_in_segment >= m_segment.dumped_api_call_vec_ptr->size() )
            {
                if (m_reader_ptr->read_next_segment(&m_segment) == false)
                {
                    m_segment.dumped_api_call_vec_ptr.reset();

                    return nullptr;
                }

                m_n_call_in_segment = 0;

                m_summary.n_chunks   += m_segment.data_chunk_ptr_vec.size();
                m_summary.n_surfaces += m_segment.dumped_surface_vec_ptr->size();

                for (const auto& chunk_ptr : m_segment.data_chunk_ptr_vec)
                {
                    m_summary.n_chunk_bytes += (chunk_ptr != nullptr) ? chunk_ptr->size()
                                                                      : 0;
                }
            }

            return &m_segment.dumped_api_call_vec_ptr->at(m_n_call_in_segment);
        }

        /* Counts the call that the cursor is at, and goes on to the next. */
        void advance()
        {
            const auto& call = m_segment.dumped_api_call_vec_ptr->at(m_n_call_in_segment);

            m_summary.call_count_map[call.func]++;
            m_summary.n_calls++;

            if (Capture::APIDumpLoader::is_frame_boundary(call) )
            {
                m_summary.n_frames++;
            }

            m_n_call_in_segment++;
        }

        const Capture::APIDumpLoader::WorkloadSummary& get_summary() const
        {
            return m_summary;
        }

    private:
        size_t                                         m_n_call_in_segment;
        Capture::APIDumpLoader::WorkloadReaderUniquePtr m_reader_ptr;
        Capture::APIDumpLoader::Workload               m_segment;
        Capture::APIDumpLoader::WorkloadSummary        m_summary;
    };
}

bool Capture::APIDumpLoader::WorkloadComparer::compare(const char*         in_first_filename_ptr,
                                                       const char*         in_second_filename_ptr,
                                                       const uint32_t&     in_n_threads,
                                                       WorkloadComparison* out_comparison_ptr,
                                                       std::string*        out_error_ptr)
{
    WorkloadReader::Options reader_options;
    WorkloadReaderUniquePtr first_reader_ptr;
    WorkloadReaderUniquePtr second_reader_ptr;
    bool                    result = false;

    *out_comparison_ptr = WorkloadComparison();

    reader_options.n_threads = in_n_threads;

    first_reader_ptr = WorkloadReader::create(in_first_filename_ptr,
                                              reader_options,
                                              out_error_ptr);

    if (first_reader_ptr == nullptr)
    {
        *out_error_ptr = std::string(in_first_filename_ptr) + ": " + *out_error_ptr;

        goto end;
    }

    second_reader_ptr = WorkloadReader::create(in_second_filename_ptr,
                                               reader_options,
                                               out_error_ptr);

    if (second_reader_ptr == nullptr)
    {
        *out_error_ptr = std::string(in_second_filename_ptr) + ": " + *out_error_ptr;

        goto end;
    }

    {
        CallCursor first_cursor (std::move(first_reader_ptr) );
        CallCursor second_cursor(std::move(second_reader_ptr) );

        /* The calls are taken two at a time, until they differ; after that, each workload is counted on its own. */
        for (;;)
        {
            const auto* first_call_ptr  = first_cursor.get_call_ptr();
            const auto* second_call_ptr = second_cursor.get_call_ptr();

            if (first_call_ptr  == nullptr &&
                second_call_ptr == nullptr)
            {
                break;
            }

            if (out_comparison_ptr->has_same_call_sequence)
            {
                const bool has_same_function = (first_call_ptr  != nullptr &&
                                                second_call_ptr != nullptr &&
                                                first_call_ptr->func == second_call_ptr->func);

                if (has_same_function == false)
                {
                    out_comparison_ptr->has_same_call_sequence             = false;
                    out_comparison_ptr->first_difference_call_index        = first_cursor.get_summary().n_calls;
                    out_comparison_ptr->first_difference_frame_index       = first_cursor.get_summary().n_frames;
                    out_comparison_ptr->first_difference_first_function    = (first_call_ptr != nullptr)  ? first_call_ptr->func
                                                                                                          : APIInterceptor::APIFUNCTION_UNKNOWN;
                    out_comparison_ptr->first_difference_second_function   = (second_call_ptr != nullptr) ? second_call_ptr->func
                                                                                                          : APIInterceptor::APIFUNCTION_UNKNOWN;
                }
            }

            if (first_call_ptr != nullptr)
            {
                first_cursor.advance();
            }

            if (second_call_ptr != nullptr)
            {
                second_cursor.advance();
            }
        }

        out_comparison_ptr->first  = first_cursor.get_summary();
        out_comparison_ptr->second = second_cursor.get_summary();
    }

    result = true;
end:
    return result;
}
