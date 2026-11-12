/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Checks of the pool that keeps the vectors of small chunks.
 */
#include <gtest/gtest.h>
#include "common/chunk_pool.h"

TEST(ChunkPool, GivesANewEmptyVectorWhenNothingIsKept)
{
    APIInterceptor::ChunkPool pool;

    const auto chunk_ptr = pool.acquire();

    ASSERT_NE(chunk_ptr,
              nullptr);
    EXPECT_TRUE(chunk_ptr->empty() );
    EXPECT_EQ  (pool.get_n_pooled(),
                0u);
}

TEST(ChunkPool, KeepsASmallVectorWithItsRoomAndGivesItBackEmpty)
{
    APIInterceptor::ChunkPool pool;
    auto                      chunk_ptr = pool.acquire();

    chunk_ptr->assign(100,
                      7);

    const auto* const first_ptr = chunk_ptr.get();
    const size_t      capacity  = chunk_ptr->capacity();

    pool.recycle(&chunk_ptr);

    EXPECT_EQ(chunk_ptr,
              nullptr);
    EXPECT_EQ(pool.get_n_pooled(),
              1u);

    const auto again_ptr = pool.acquire();

    EXPECT_EQ(again_ptr.get(),
              first_ptr);
    EXPECT_TRUE(again_ptr->empty() );
    EXPECT_GE  (again_ptr->capacity(),
                capacity);
    EXPECT_EQ  (pool.get_n_pooled(),
                0u);
}

TEST(ChunkPool, DestroysAVectorThatIsLargerThanASmallChunk)
{
    APIInterceptor::ChunkPool pool;
    auto                      chunk_ptr = pool.acquire();

    chunk_ptr->assign(APIInterceptor::ChunkPool::get_small_chunk_max_n_bytes() + 1,
                      1);

    pool.recycle(&chunk_ptr);

    EXPECT_EQ(chunk_ptr,
              nullptr);
    EXPECT_EQ(pool.get_n_pooled(),
              0u);
}

TEST(ChunkPool, KeepsNoMoreThanItsLimit)
{
    APIInterceptor::ChunkPool pool;
    const uint32_t            max_n_pooled_chunks = APIInterceptor::ChunkPool::get_max_n_pooled_chunks();

    for (uint32_t n_chunk = 0;
                  n_chunk < max_n_pooled_chunks + 5;
                ++n_chunk)
    {
        /* Each is a vector of its own: acquire() would give back the one that was kept in the turn before. */
        APIInterceptor::ChunkPool::ChunkUniquePtr chunk_ptr(new std::vector<uint8_t>(8) );

        pool.recycle(&chunk_ptr);
    }

    EXPECT_EQ(pool.get_n_pooled(),
              max_n_pooled_chunks);
}

TEST(ChunkPool, IgnoresAPointerThatIsNull)
{
    APIInterceptor::ChunkPool           pool;
    APIInterceptor::ChunkPool::ChunkUniquePtr null_ptr;

    pool.recycle(&null_ptr);

    EXPECT_EQ(pool.get_n_pooled(),
              0u);
}
