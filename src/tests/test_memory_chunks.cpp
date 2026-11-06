/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Checks of the chunks which hold a copy of the memory passed to the API.
 */
#include <gtest/gtest.h>
#include "common/callbacks.h"
#include "common/memory_chunk.h"
#include <vector>

static std::vector<uint8_t> get_chunk_contents(const APIInterceptor::DataChunkID& in_chunk_id)
{
    const void*          data_ptr = nullptr;
    uint32_t             n_bytes  = 0;
    std::vector<uint8_t> result_u8_vec;

    if (APIInterceptor::get_data_chunk(in_chunk_id,
                                      &data_ptr,
                                      &n_bytes) )
    {
        result_u8_vec.assign(static_cast<const uint8_t*>(data_ptr),
                             static_cast<const uint8_t*>(data_ptr) + n_bytes);
    }

    return result_u8_vec;
}

TEST(MemoryChunk, CopiesTheElementsOnceAndOnlyWhenAsked)
{
    const uint32_t values_u32vec3[] = {1, 2, 3};
    const auto     n_chunks_before  = APIInterceptor::get_n_data_chunks();

    APIInterceptor::MemoryChunk chunk(values_u32vec3,
                             3,
                             sizeof(uint32_t) );

    EXPECT_EQ(APIInterceptor::get_n_data_chunks(),
              n_chunks_before);

    const auto first_id  = chunk.get_id();
    const auto second_id = chunk.get_id();

    EXPECT_EQ(first_id,
              second_id);
    EXPECT_EQ(APIInterceptor::get_n_data_chunks(),
              n_chunks_before + 1);
    EXPECT_EQ(get_chunk_contents(first_id).size(),
              sizeof(values_u32vec3) );
}

TEST(MemoryChunk, IsEmptyWhenThereIsNothingToCopy)
{
    const uint32_t values_u32vec1[] = {1};

    APIInterceptor::MemoryChunk negative_count_chunk(values_u32vec1,
                                            -1,
                                            sizeof(uint32_t) );
    APIInterceptor::MemoryChunk no_pointer_chunk    (nullptr,
                                            4,
                                            sizeof(uint32_t) );
    APIInterceptor::MemoryChunk zero_count_chunk    (values_u32vec1,
                                            0,
                                            sizeof(uint32_t) );

    EXPECT_TRUE(get_chunk_contents(negative_count_chunk.get_id() ).empty() );
    EXPECT_TRUE(get_chunk_contents(no_pointer_chunk.get_id() ).empty() );
    EXPECT_TRUE(get_chunk_contents(zero_count_chunk.get_id() ).empty() );
}

TEST(MemoryChunk, TakingOneChunkEmptiesItAndKeepsTheNumbersGoing)
{
    const uint32_t       values_u32vec2[] = {5, 6};
    std::vector<uint8_t> taken_u8vec;

    APIInterceptor::MemoryChunk first_chunk (values_u32vec2,
                                             2,
                                             sizeof(uint32_t) );
    APIInterceptor::MemoryChunk second_chunk(values_u32vec2,
                                             2,
                                             sizeof(uint32_t) );

    const auto first_id        = first_chunk.get_id();
    const auto second_id       = second_chunk.get_id();
    const auto n_chunks_before = APIInterceptor::get_n_data_chunks();

    EXPECT_TRUE(APIInterceptor::take_data_chunk(first_id,
                                               &taken_u8vec) );
    EXPECT_EQ(taken_u8vec.size(),
              sizeof(values_u32vec2) );
    EXPECT_FALSE(APIInterceptor::take_data_chunk(first_id,
                                                &taken_u8vec) );
    EXPECT_TRUE(get_chunk_contents(first_id).empty() );
    EXPECT_EQ(get_chunk_contents(second_id).size(),
              sizeof(values_u32vec2) );
    EXPECT_EQ(APIInterceptor::get_n_data_chunks(),
              n_chunks_before);
}
