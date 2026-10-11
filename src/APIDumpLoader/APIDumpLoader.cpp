/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * A workload file is a sequence of segments (one per spill of the dumper's memory to disk). Each one holds three
 * uint32_t counts (API calls, data chunks, surfaces), followed by those items. Data chunk IDs count across segments.
 */
#include "APIDumpLoader/APIDumpLoader.h"
#include "APIDumpLoader/WorkloadReader.h"

APIDumpLoader::WorkloadUniquePtr APIDumpLoader::create_workload_from_file(const char* in_filename_ptr)
{
    WorkloadReaderUniquePtr reader_ptr = WorkloadReader::create(in_filename_ptr);
    WorkloadUniquePtr       result_ptr;

    if (reader_ptr != nullptr)
    {
        Workload segment;

        result_ptr.reset                         (new Workload           () );
        result_ptr->dumped_api_call_vec_ptr.reset(new DumpedAPICallVector() );
        result_ptr->dumped_surface_vec_ptr.reset (new DumpedSurfaceVector() );

        while (reader_ptr->read_next_segment(&segment) )
        {
            for (auto& current_api_call : *segment.dumped_api_call_vec_ptr)
            {
                result_ptr->dumped_api_call_vec_ptr->emplace_back(std::move(current_api_call) );
            }

            for (auto& current_data_chunk_ptr : segment.data_chunk_ptr_vec)
            {
                result_ptr->data_chunk_ptr_vec.emplace_back(std::move(current_data_chunk_ptr) );
            }

            for (auto& current_surface : *segment.dumped_surface_vec_ptr)
            {
                result_ptr->dumped_surface_vec_ptr->emplace_back(std::move(current_surface) );
            }
        }
    }

    return result_ptr;
}

const APIDumpLoader::DataChunk* APIDumpLoader::get_data_chunk_ptr(const Workload& in_workload,
                                                                  const uint32_t& in_data_chunk_id)
{
    const DataChunk* result = nullptr;

    if (in_data_chunk_id                                    >= in_workload.first_data_chunk_id &&
        in_data_chunk_id - in_workload.first_data_chunk_id  <  in_workload.data_chunk_ptr_vec.size() )
    {
        result = in_workload.data_chunk_ptr_vec.at(in_data_chunk_id - in_workload.first_data_chunk_id).get();
    }

    return result;
}
