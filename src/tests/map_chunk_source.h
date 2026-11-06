/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Holds chunks, as a segment does, for the tests of the replayer.
 */
#ifndef TESTS_MAP_CHUNK_SOURCE_H
#define TESTS_MAP_CHUNK_SOURCE_H

#include "i_chunk_source.h"
#include <map>
#include <stdint.h>

namespace Tests
{
    /* Holds chunks, as a segment does. */
    class MapChunkSource : public Replay::ReplayEngineDLL::IChunkSource
    {
    public:
        const Capture::APIDumpLoader::DataChunk* get_data_chunk_ptr (const uint32_t& in_data_chunk_id) const override;
        uint32_t                                 get_pointer_n_bytes()                                 const override;

        std::map<uint32_t, Capture::APIDumpLoader::DataChunk> chunk_map;
        uint32_t                                              pointer_n_bytes = 4;
    };
}

#endif /* TESTS_MAP_CHUNK_SOURCE_H */
