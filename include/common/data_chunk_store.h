/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef COMMON_DATA_CHUNK_STORE_H
#define COMMON_DATA_CHUNK_STORE_H

#include "common/chunk_pool.h"
#include "common/types.h"
#include <atomic>
#include <deque>
#include <functional>
#include <memory>
#include <mutex>
#include <vector>

namespace APIInterceptor
{
    /* The data of the structures that the arguments of intercepted calls point to, kept until the consumer of the call takes them.
     *
     * The chunks are numbered as they come, and a number is never used again, but the store holds only those from the oldest one
     * which was not taken or released: the ones before it are gone, and are dropped from the front as soon as they are, or the store
     * would grow for as long as the process runs. The vectors that held small chunks are kept when the chunks go, to hold the next ones (see ChunkPool), so
     * that a call that makes a chunk does not allocate. Any thread.
     *
     * A consumer that stops taking chunks would leave the store growing for as long as the program makes calls, and a 32-bit program runs out of address
     * space in seconds. So the store can be given a capacity and a drain: a registration that would take the store over its capacity first runs the drain,
     * which frees what the consumer can free, and the registration waits for it (see set_drain()).
     */
    class DataChunkStore
    {
    public:
        /* Frees chunks (take or release them) when the store is full. It runs on the thread that registers a chunk, one at a time. */
        typedef std::function<void()> DrainFunc;

        static DataChunkStore* get_ptr();

        /* Returns false if there is no such chunk (it was taken, or released, or never made). The data stays valid until the chunk is
         * taken or released.
         */
        bool get(const DataChunkID& in_data_chunk_id,
                 const void**       out_data_ptr_ptr,
                 uint32_t*          out_n_bytes_ptr);

        /* The numbers which were given out so far: the ones which are gone count. */
        uint32_t get_n_chunks();

        /* What a chunk costs besides its data: the vector, the pointer to it, the two blocks of the heap and the place in the deque. A program that makes
         * millions of chunks of a few bytes (one for each vertex of a draw) would otherwise hold several times what the bytes say.
         */
        static uint64_t get_chunk_overhead_n_bytes();

        /* How much memory the chunks that the store holds take: their bytes, and get_chunk_overhead_n_bytes() for each. */
        uint64_t get_n_held_bytes() const;

        /* How many chunks the store holds: the ones which were not taken or released. */
        uint32_t get_n_held_chunks();

        DataChunkID register_chunk(const void*        in_data_ptr,
                                   const uint32_t&    in_n_bytes);
        void        release       (const DataChunkID& in_data_chunk_id);

        /* Releases every chunk that the store holds, for a drain whose consumer has no use for them any more (the numbers are not used again). */
        void        release_all   ();

        /* Bounds the store: a chunk that would take the memory held (get_n_held_bytes()) over in_capacity_n_bytes (0: no bound) makes the store run in_drain_func first,
         * and wait for it. If the store still cannot take the chunk after that, the process ends with a message saying so: a chunk that only fails to
         * fit because other chunks are held, in a store that nothing frees, would otherwise be followed by the end of the program anywhere else.
         * A chunk whose memory is larger than the capacity itself is taken when the store is empty.
         */
        void        set_drain     (const uint64_t&  in_capacity_n_bytes,
                                   const DrainFunc& in_drain_func);

        /* Moves the contents of one chunk out of the store: the vector and the chunk change contents, so nothing is allocated.
         * Returns false if there is no such chunk, and the vector is left as it is.
         */
        bool take(const DataChunkID&    in_data_chunk_id,
                  std::vector<uint8_t>* out_data_chunk_ptr);

        /* Moves the contents of the chunks of the numbers out of the store, each into the vector that is given for it (the two change contents: nothing is
         * allocated), with the lock taken once. A chunk which is not there (it was taken, or released, or never made, or is named twice) leaves its vector as
         * it is, and says so in the flags (1 for each that was taken, one for each number); returns how many were taken.
         */
        uint32_t take_chunks(const std::vector<DataChunkID>&           in_data_chunk_id_vec,
                             const std::vector<std::vector<uint8_t>*>& in_destination_ptr_vec,
                             std::vector<uint8_t>*                     out_is_taken_u8_vec_ptr);

        /* Moves the contents of the chunks out of the store, in one go. A chunk which is not there comes out empty. */
        void take_range(const DataChunkID&                  in_first_data_chunk_id,
                        const uint32_t&                     in_n_data_chunks,
                        std::vector<std::vector<uint8_t> >* out_data_chunk_vec_ptr);

    private:
        typedef ChunkPool::ChunkUniquePtr ChunkUniquePtr;

        /* The chunks, and the mutex that guards them: all accesses to the members must be done with it held. */
        struct Chunks
        {
            std::deque<ChunkUniquePtr> chunk_deque; /* chunk_deque.front() is the chunk numbered first_id */
            uint32_t                   first_id = 0;
            std::mutex                 mutex;
            ChunkPool                  pool;        /* the vectors of the small chunks that are gone     */
        };

        /* The chunk of the number, or nullptr if there is none. */
        ChunkUniquePtr* find_chunk_ptr(const DataChunkID& in_data_chunk_id);

        /* Runs the drain if a chunk of in_n_data_bytes of data would take the store over its capacity. Called without the lock of the chunks. */
        void make_room(const uint64_t& in_n_data_bytes);

        /* Drops the chunks which are gone from the front. */
        void trim();

        std::atomic<uint64_t> m_capacity_n_bytes = {0};
        Chunks                m_chunks;
        DrainFunc             m_drain_func;
        std::mutex            m_drain_mutex;       /* one drain at a time; guards m_drain_func */
        std::atomic<uint64_t> m_n_held_bytes       = {0}; /* changed with the lock of the chunks held; read without it */
    };
}

#endif /* COMMON_DATA_CHUNK_STORE_H */
