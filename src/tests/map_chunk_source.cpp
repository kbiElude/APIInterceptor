/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "map_chunk_source.h"

const Capture::APIDumpLoader::DataChunk* Tests::MapChunkSource::get_data_chunk_ptr(const uint32_t& in_data_chunk_id) const
{
    const auto iterator = chunk_map.find(in_data_chunk_id);

    return (iterator != chunk_map.end() ) ? &iterator->second
                                          : nullptr;
}

uint32_t Tests::MapChunkSource::get_pointer_n_bytes() const
{
    return pointer_n_bytes;
}
