/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef COMMON_DATA_CHUNK_STORE_H
#define COMMON_DATA_CHUNK_STORE_H

#include "Common/types.h"
#include <deque>
#include <memory>
#include <mutex>
#include <vector>

namespace APIInterceptor
{
    /* The data of the structures that the arguments of intercepted calls point to, kept until the consumer of the call takes them.
     *
     * The chunks are numbered as they come, and a number is never used again, but the store holds only those from the oldest one
     * which was not taken or released: the ones before it are gone, and are dropped from the front as soon as they are, or the store
     * would grow for as long as the process runs. Any thread.
     */
    class DataChunkStore
    {
    public:
        /* Returns false if there is no such chunk (it was taken, or released, or never made). The data stays valid until the chunk is
         * taken or released.
         */
        bool get(const DataChunkID& in_data_chunk_id,
                 const void**       out_data_ptr_ptr,
                 uint32_t*          out_n_bytes_ptr);

        /* The numbers which were given out so far: the ones which are gone count. */
        uint32_t get_n_chunks();

        DataChunkID register_chunk(const void*        in_data_ptr,
                                   const uint32_t&    in_n_bytes);
        void        release       (const DataChunkID& in_data_chunk_id);

        /* Moves the contents of one chunk out of the store: the vector and the chunk change contents, so nothing is allocated.
         * Returns false if there is no such chunk, and the vector is left as it is.
         */
        bool take(const DataChunkID&    in_data_chunk_id,
                  std::vector<uint8_t>* out_data_chunk_ptr);

        /* Moves the contents of the chunks out of the store, in one go. A chunk which is not there comes out empty. */
        void take_range(const DataChunkID&                  in_first_data_chunk_id,
                        const uint32_t&                     in_n_data_chunks,
                        std::vector<std::vector<uint8_t> >* out_data_chunk_vec_ptr);

        static DataChunkStore* get_ptr();

    private:
        typedef std::unique_ptr<std::vector<uint8_t> > ChunkUniquePtr;

        /* The chunks, and the mutex that guards them: all accesses to the members must be done with it held. */
        struct Chunks
        {
            std::deque<ChunkUniquePtr> chunk_deque; /* chunk_deque.front() is the chunk numbered first_id */
            uint32_t                   first_id = 0;
            std::mutex                 mutex;
        };

        /* The chunk of the number, or nullptr if there is none. */
        ChunkUniquePtr* find_chunk_ptr(const DataChunkID& in_data_chunk_id);

        /* Drops the chunks which are gone from the front. */
        void trim();

        Chunks m_chunks;
    };
}

#endif /* COMMON_DATA_CHUNK_STORE_H */
