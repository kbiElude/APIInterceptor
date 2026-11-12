/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Checks of the store of the data chunks: what a chunk is given back as, whether the vectors of small chunks that are kept make a difference to what comes out,
 * and that taking the chunks of a call in one go is what taking them one at a time is.
 */
#include <gtest/gtest.h>
#include "common/chunk_pool.h"
#include "common/data_chunk_store.h"
#include <thread>
#include <vector>

namespace
{
    std::vector<uint8_t> make_bytes(const uint8_t& in_first_value,
                                    const size_t&  in_n_bytes)
    {
        std::vector<uint8_t> result_u8_vec(in_n_bytes);

        for (size_t n_byte = 0;
                    n_byte < in_n_bytes;
                  ++n_byte)
        {
            result_u8_vec.at(n_byte) = static_cast<uint8_t>(in_first_value + n_byte);
        }

        return result_u8_vec;
    }

    std::vector<uint8_t> read_chunk(APIInterceptor::DataChunkStore* inout_store_ptr,
                                    const uint32_t&                 in_chunk_id,
                                    bool*                           out_is_there_ptr)
    {
        const void*          data_ptr = nullptr;
        uint32_t             n_bytes  = 0;
        std::vector<uint8_t> result_u8_vec;

        *out_is_there_ptr = inout_store_ptr->get(in_chunk_id,
                                                &data_ptr,
                                                &n_bytes);

        if (*out_is_there_ptr)
        {
            result_u8_vec.assign(static_cast<const uint8_t*>(data_ptr),
                                 static_cast<const uint8_t*>(data_ptr) + n_bytes);
        }

        return result_u8_vec;
    }
}

TEST(DataChunkStore, GivesBackWhatWasRegisteredForSmallAndLargeChunks)
{
    APIInterceptor::DataChunkStore store;
    bool                           is_there = false;

    const auto small_bytes = make_bytes(1,
                                        12);
    const auto large_bytes = make_bytes(9,
                                        APIInterceptor::ChunkPool::get_small_chunk_max_n_bytes() + 50);

    const auto small_id = store.register_chunk(small_bytes.data(),
                                               static_cast<uint32_t>(small_bytes.size() ) );
    const auto large_id = store.register_chunk(large_bytes.data(),
                                               static_cast<uint32_t>(large_bytes.size() ) );

    EXPECT_EQ(read_chunk(&store,
                         small_id,
                        &is_there),
              small_bytes);
    EXPECT_TRUE(is_there);
    EXPECT_EQ(read_chunk(&store,
                         large_id,
                        &is_there),
              large_bytes);
    EXPECT_TRUE(is_there);
    EXPECT_EQ(store.get_n_chunks(),
              2u);
    EXPECT_EQ(store.get_n_held_chunks(),
              2u);
}

TEST(DataChunkStore, AChunkThatReusesAVectorHasTheSizeAndBytesOfItsOwnData)
{
    APIInterceptor::DataChunkStore store;
    bool                           is_there = false;

    const auto first_bytes  = make_bytes(1,
                                         40);
    const auto second_bytes = make_bytes(100,
                                         3);

    const auto first_id = store.register_chunk(first_bytes.data(),
                                               static_cast<uint32_t>(first_bytes.size() ) );

    store.release(first_id);

    /* The vector of the first one is the one that the second is made in: it had room for 40 bytes, and holds 3. */
    const auto second_id = store.register_chunk(second_bytes.data(),
                                                static_cast<uint32_t>(second_bytes.size() ) );

    EXPECT_EQ(read_chunk(&store,
                         second_id,
                        &is_there),
              second_bytes);
    EXPECT_TRUE(is_there);

    read_chunk(&store,
               first_id,
              &is_there);

    EXPECT_FALSE(is_there);
    EXPECT_NE(first_id,
              second_id);
}

TEST(DataChunkStore, ATakenChunkIsExactlyWhatWasRegisteredAndIsGoneFromTheStore)
{
    APIInterceptor::DataChunkStore store;
    std::vector<uint8_t>           taken_u8_vec = make_bytes(50,
                                                             20);

    const auto bytes = make_bytes(3,
                                  12);
    const auto id    = store.register_chunk(bytes.data(),
                                            static_cast<uint32_t>(bytes.size() ) );

    ASSERT_TRUE(store.take(id,
                          &taken_u8_vec) );

    EXPECT_EQ(taken_u8_vec,
              bytes);
    EXPECT_FALSE(store.take(id,
                           &taken_u8_vec) );
    EXPECT_EQ(store.get_n_held_chunks(),
              0u);
    EXPECT_EQ(store.get_n_chunks(),
              1u);
}

TEST(DataChunkStore, ZeroBytesMakeAnEmptyChunkThatIsThere)
{
    APIInterceptor::DataChunkStore store;
    bool                           is_there = false;

    const auto id = store.register_chunk(nullptr,
                                         0);

    EXPECT_TRUE(read_chunk(&store,
                           id,
                          &is_there).empty() );
    EXPECT_TRUE(is_there);
}

TEST(DataChunkStore, TakingTheChunksOfACallInOneGoIsTakingThemOneByOne)
{
    APIInterceptor::DataChunkStore store;
    std::vector<uint32_t>          id_vec;
    std::vector<std::vector<uint8_t> > bytes_vec;

    for (size_t n_chunk = 0;
                n_chunk < 6;
              ++n_chunk)
    {
        bytes_vec.push_back(make_bytes(static_cast<uint8_t>(10 * n_chunk),
                                       (n_chunk == 4) ? APIInterceptor::ChunkPool::get_small_chunk_max_n_bytes() + 10
                                                      : 3 + n_chunk) );

        id_vec.push_back(store.register_chunk(bytes_vec.back().data(),
                                              static_cast<uint32_t>(bytes_vec.back().size() ) ) );
    }

    /* The chunks 1, 4 and 2, the number of a chunk that was never made, and the chunk 1 again. */
    const std::vector<uint32_t> asked_id_vec = {id_vec.at(1), id_vec.at(4), id_vec.at(2), 9999, id_vec.at(1)};

    std::vector<std::vector<uint8_t> >  destination_vec(asked_id_vec.size() );
    std::vector<std::vector<uint8_t>*>  destination_ptr_vec;
    std::vector<uint8_t>                is_taken_u8_vec;

    for (auto& destination : destination_vec)
    {
        destination_ptr_vec.push_back(&destination);
    }

    const uint32_t n_taken = store.take_chunks(asked_id_vec,
                                               destination_ptr_vec,
                                              &is_taken_u8_vec);

    EXPECT_EQ(n_taken,
              3u);
    ASSERT_EQ(is_taken_u8_vec.size(),
              asked_id_vec.size() );
    EXPECT_EQ(is_taken_u8_vec.at(0),
              1);
    EXPECT_EQ(is_taken_u8_vec.at(1),
              1);
    EXPECT_EQ(is_taken_u8_vec.at(2),
              1);
    EXPECT_EQ(is_taken_u8_vec.at(3),
              0);
    EXPECT_EQ(is_taken_u8_vec.at(4),
              0);
    EXPECT_EQ(destination_vec.at(0),
              bytes_vec.at(1) );
    EXPECT_EQ(destination_vec.at(1),
              bytes_vec.at(4) );
    EXPECT_EQ(destination_vec.at(2),
              bytes_vec.at(2) );
    EXPECT_TRUE(destination_vec.at(3).empty() );
    EXPECT_TRUE(destination_vec.at(4).empty() );
    EXPECT_EQ(store.get_n_held_chunks(),
              3u);

    /* What was not taken is still there, and what the store gave up its vectors for is not. */
    bool is_there = false;

    EXPECT_EQ(read_chunk(&store,
                         id_vec.at(5),
                        &is_there),
              bytes_vec.at(5) );
    EXPECT_TRUE(is_there);

    read_chunk(&store,
               id_vec.at(2),
              &is_there);

    EXPECT_FALSE(is_there);
}

TEST(DataChunkStore, TheStoreHoldsNothingAfterEveryChunkWasTakenOrReleasedAndTheNumbersKeepGoing)
{
    APIInterceptor::DataChunkStore store;
    std::vector<uint8_t>           taken_u8_vec;

    for (uint32_t n_turn = 0;
                  n_turn < 50;
                ++n_turn)
    {
        const auto bytes    = make_bytes(static_cast<uint8_t>(n_turn),
                                         1 + n_turn % 20);
        const auto first_id = store.register_chunk(bytes.data(),
                                                   static_cast<uint32_t>(bytes.size() ) );
        const auto second_id = store.register_chunk(bytes.data(),
                                                    static_cast<uint32_t>(bytes.size() ) );

        EXPECT_EQ(second_id,
                  first_id + 1);

        store.release(first_id);

        ASSERT_TRUE(store.take(second_id,
                              &taken_u8_vec) );
        EXPECT_EQ(taken_u8_vec,
                  bytes);
    }

    EXPECT_EQ(store.get_n_held_chunks(),
              0u);
    EXPECT_EQ(store.get_n_chunks(),
              100u);
}

TEST(DataChunkStore, ThreadsThatRegisterAndTakeChunksEachGetTheirOwnBytes)
{
    constexpr uint32_t N_THREADS         = 4;
    constexpr uint32_t N_TURNS_PER_THREAD = 3000;

    APIInterceptor::DataChunkStore store;
    std::vector<uint32_t>          n_wrong_vec(N_THREADS,
                                               0);
    std::vector<std::thread>       thread_vec;

    for (uint32_t n_thread = 0;
                  n_thread < N_THREADS;
                ++n_thread)
    {
        thread_vec.emplace_back([&store, &n_wrong_vec, n_thread, N_TURNS_PER_THREAD]()
        {
            std::vector<uint8_t> taken_u8_vec;

            for (uint32_t n_turn = 0;
                          n_turn < N_TURNS_PER_THREAD;
                        ++n_turn)
            {
                const auto bytes = make_bytes(static_cast<uint8_t>(n_thread * 40 + n_turn),
                                              1 + n_turn % 300);
                const auto id    = store.register_chunk(bytes.data(),
                                                        static_cast<uint32_t>(bytes.size() ) );

                if (store.take(id,
                              &taken_u8_vec) == false ||
                    taken_u8_vec               != bytes)
                {
                    n_wrong_vec.at(n_thread)++;
                }
            }
        });
    }

    for (auto& thread : thread_vec)
    {
        thread.join();
    }

    for (uint32_t n_thread = 0;
                  n_thread < N_THREADS;
                ++n_thread)
    {
        EXPECT_EQ(n_wrong_vec.at(n_thread),
                  0u);
    }

    EXPECT_EQ(store.get_n_held_chunks(),
              0u);
    EXPECT_EQ(store.get_n_chunks(),
              N_THREADS * N_TURNS_PER_THREAD);
}
