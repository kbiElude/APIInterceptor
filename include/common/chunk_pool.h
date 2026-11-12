/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef COMMON_CHUNK_POOL_H
#define COMMON_CHUNK_POOL_H

#include <memory>
#include <stdint.h>
#include <vector>

namespace APIInterceptor
{
    /* Vectors of bytes that held a small chunk (the data of a pointer that a call is given: a vertex, a color, a matrix) and are kept, with the room
     * they have, to hold the next one: a call of an application that draws with glVertex and glNormal makes thousands of chunks in a frame, each of
     * which was two allocations and two frees. A vector that is large, or one that does not fit when the pool is full, is destroyed, so that what is
     * kept is bounded. The type of the chunks is the one they always had.
     *
     * Not thread-safe: the user holds the lock that guards what it shares, or has the pool to itself.
     */
    class ChunkPool
    {
    public:
        typedef std::unique_ptr<std::vector<uint8_t> > ChunkUniquePtr;

        ChunkPool();

        /* An empty vector: one that was kept, with its room, if there is one; a new one otherwise. */
        ChunkUniquePtr acquire();

        uint32_t get_n_pooled() const;

        /* Keeps the vector, emptied, if it has room for no more than a small chunk and the pool is not full; destroys it otherwise. Leaves the pointer null. */
        void recycle(ChunkUniquePtr* inout_chunk_ptr_ptr);

        /* How many bytes a chunk may be for the vector that held it to be kept, and how many vectors are kept at the most. */
        static uint32_t get_max_n_pooled_chunks();
        static uint32_t get_small_chunk_max_n_bytes();

    private:
        std::vector<ChunkUniquePtr> m_chunk_ptr_vec;
    };
}

#endif /* COMMON_CHUNK_POOL_H */
