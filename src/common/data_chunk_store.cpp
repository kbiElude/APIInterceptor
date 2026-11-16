/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "common/data_chunk_store.h"
#include "common/fatal_error.h"
#include "common/macros.h"
#include <string.h>

APIInterceptor::DataChunkStore::ChunkUniquePtr* APIInterceptor::DataChunkStore::find_chunk_ptr(const DataChunkID& in_data_chunk_id)
{
    ChunkUniquePtr* result_ptr = nullptr;

    if (in_data_chunk_id >= m_chunks.first_id)
    {
        const size_t index = in_data_chunk_id - m_chunks.first_id;

        if (index                          <  m_chunks.chunk_deque.size() &&
            m_chunks.chunk_deque.at(index) != nullptr)
        {
            result_ptr = &m_chunks.chunk_deque.at(index);
        }
    }

    return result_ptr;
}

bool APIInterceptor::DataChunkStore::get(const DataChunkID& in_data_chunk_id,
                                         const void**       out_data_ptr_ptr,
                                         uint32_t*          out_n_bytes_ptr)
{
    bool result = false;

    {
        std::lock_guard<std::mutex> lock(m_chunks.mutex);

        const auto slot_ptr = find_chunk_ptr(in_data_chunk_id);

        if (slot_ptr != nullptr)
        {
            *out_data_ptr_ptr = (*slot_ptr)->data    ();
            *out_n_bytes_ptr  = static_cast<uint32_t>((*slot_ptr)->size() );

            result = true;
        }
    }

    return result;
}

uint32_t APIInterceptor::DataChunkStore::get_n_chunks()
{
    std::lock_guard<std::mutex> lock(m_chunks.mutex);

    return m_chunks.first_id + static_cast<uint32_t>(m_chunks.chunk_deque.size() );
}

uint64_t APIInterceptor::DataChunkStore::get_chunk_overhead_n_bytes()
{
    /* A vector (3 pointers) and the pointer to it, the heap's header for each of the two blocks, and the slot of the deque. */
    constexpr uint64_t CHUNK_OVERHEAD_N_BYTES = 96;

    return CHUNK_OVERHEAD_N_BYTES;
}

uint64_t APIInterceptor::DataChunkStore::get_n_held_bytes() const
{
    return m_n_held_bytes.load();
}

uint32_t APIInterceptor::DataChunkStore::get_n_held_chunks()
{
    uint32_t result = 0;

    {
        std::lock_guard<std::mutex> lock(m_chunks.mutex);

        for (const auto& chunk_ptr : m_chunks.chunk_deque)
        {
            if (chunk_ptr != nullptr)
            {
                result++;
            }
        }
    }

    return result;
}

APIInterceptor::DataChunkStore* APIInterceptor::DataChunkStore::get_ptr()
{
    /* Never destroyed: hooks can still run during shutdown. */
    static DataChunkStore* instance_ptr = new DataChunkStore();

    return instance_ptr;
}

void APIInterceptor::DataChunkStore::make_room(const uint64_t& in_n_data_bytes)
{
    const uint64_t capacity = m_capacity_n_bytes.load();
    const uint64_t n_bytes  = in_n_data_bytes + get_chunk_overhead_n_bytes();

    /* The usual case: it fits, and no lock is taken. */
    if (capacity                           == 0 ||
        m_n_held_bytes.load() + n_bytes    <= capacity)
    {
        goto end;
    }

    {
        std::lock_guard<std::mutex> drain_lock(m_drain_mutex);

        /* Another thread may have drained while this one waited for its turn. */
        if (m_drain_func                      &&
            m_n_held_bytes.load() + n_bytes   >  capacity)
        {
            m_drain_func();

            AI_ASSERT_ALWAYS(m_n_held_bytes.load() == 0 ||
                             m_n_held_bytes.load() + n_bytes <= capacity,
                             "The store of data chunks is full, and what drains it has not freed enough: whatever holds the chunks does not take them. "
                             "Raise the capacity or make the consumer take the chunks before it is full.");
        }
    }

end:
    return;
}

APIInterceptor::DataChunkID APIInterceptor::DataChunkStore::register_chunk(const void*     in_data_ptr,
                                                                           const uint32_t& in_n_bytes)
{
    const bool      is_small      = (in_n_bytes <= ChunkPool::get_small_chunk_max_n_bytes() );
    ChunkUniquePtr  new_chunk_ptr;
    DataChunkID     result        = 0;

    /* Before the chunk is copied, so that what is freed is freed before the copy needs the memory. */
    make_room(in_n_bytes);

    /* A large chunk is made outside the lock: the copy of it can take a while. */
    if (is_small == false)
    {
        new_chunk_ptr.reset(new std::vector<uint8_t>() );

        new_chunk_ptr->assign(static_cast<const uint8_t*>(in_data_ptr),
                              static_cast<const uint8_t*>(in_data_ptr) + in_n_bytes);
    }

    {
        std::lock_guard<std::mutex> lock(m_chunks.mutex);

        /* A small one is a vector that was kept, filled here: a few bytes are less than a second trip for the lock. */
        if (is_small)
        {
            new_chunk_ptr = m_chunks.pool.acquire();

            if (in_n_bytes != 0)
            {
                new_chunk_ptr->assign(static_cast<const uint8_t*>(in_data_ptr),
                                      static_cast<const uint8_t*>(in_data_ptr) + in_n_bytes);
            }
        }

        result = m_chunks.first_id + static_cast<uint32_t>(m_chunks.chunk_deque.size() );

        m_chunks.chunk_deque.emplace_back(std::move(new_chunk_ptr) );

        m_n_held_bytes += static_cast<uint64_t>(in_n_bytes) + get_chunk_overhead_n_bytes();
    }

    return result;
}

void APIInterceptor::DataChunkStore::release(const DataChunkID& in_data_chunk_id)
{
    std::lock_guard<std::mutex> lock(m_chunks.mutex);

    const auto slot_ptr = find_chunk_ptr(in_data_chunk_id);

    if (slot_ptr != nullptr)
    {
        m_n_held_bytes -= (*slot_ptr)->size() + get_chunk_overhead_n_bytes();

        m_chunks.pool.recycle(slot_ptr);

        trim();
    }
}

void APIInterceptor::DataChunkStore::release_all()
{
    std::lock_guard<std::mutex> lock(m_chunks.mutex);

    for (auto& chunk_ptr : m_chunks.chunk_deque)
    {
        if (chunk_ptr != nullptr)
        {
            m_n_held_bytes -= chunk_ptr->size() + get_chunk_overhead_n_bytes();

            m_chunks.pool.recycle(&chunk_ptr);
        }
    }

    trim();
}

void APIInterceptor::DataChunkStore::set_drain(const uint64_t&  in_capacity_n_bytes,
                                               const DrainFunc& in_drain_func)
{
    std::lock_guard<std::mutex> drain_lock(m_drain_mutex);

    m_drain_func = in_drain_func;

    m_capacity_n_bytes.store(in_capacity_n_bytes);
}

bool APIInterceptor::DataChunkStore::take(const DataChunkID&    in_data_chunk_id,
                                          std::vector<uint8_t>* out_data_chunk_ptr)
{
    bool result = false;

    {
        std::lock_guard<std::mutex> lock(m_chunks.mutex);

        const auto slot_ptr = find_chunk_ptr(in_data_chunk_id);

        if (slot_ptr != nullptr)
        {
            m_n_held_bytes -= (*slot_ptr)->size() + get_chunk_overhead_n_bytes();

            /* The buffer which the caller had goes to the store, which keeps it if it is small: nothing is allocated here. */
            out_data_chunk_ptr->swap(**slot_ptr);

            m_chunks.pool.recycle(slot_ptr);

            trim();

            result = true;
        }
    }

    return result;
}

uint32_t APIInterceptor::DataChunkStore::take_chunks(const std::vector<DataChunkID>&           in_data_chunk_id_vec,
                                                     const std::vector<std::vector<uint8_t>*>& in_destination_ptr_vec,
                                                     std::vector<uint8_t>*                     out_is_taken_u8_vec_ptr)
{
    const size_t n_data_chunks = (in_data_chunk_id_vec.size() < in_destination_ptr_vec.size() ) ? in_data_chunk_id_vec.size()
                                                                                                : in_destination_ptr_vec.size();
    uint32_t     result        = 0;

    out_is_taken_u8_vec_ptr->assign(in_data_chunk_id_vec.size(),
                                    0);

    {
        std::lock_guard<std::mutex> lock(m_chunks.mutex);

        for (size_t n_data_chunk = 0;
                    n_data_chunk < n_data_chunks;
                  ++n_data_chunk)
        {
            const auto slot_ptr = find_chunk_ptr(in_data_chunk_id_vec.at(n_data_chunk) );

            if (slot_ptr                                    != nullptr &&
                in_destination_ptr_vec.at(n_data_chunk)     != nullptr)
            {
                m_n_held_bytes -= (*slot_ptr)->size() + get_chunk_overhead_n_bytes();

                in_destination_ptr_vec.at(n_data_chunk)->swap(**slot_ptr);

                m_chunks.pool.recycle(slot_ptr);

                out_is_taken_u8_vec_ptr->at(n_data_chunk) = 1;

                result++;
            }
        }

        trim();
    }

    return result;
}

void APIInterceptor::DataChunkStore::take_range(const DataChunkID&                  in_first_data_chunk_id,
                                                const uint32_t&                     in_n_data_chunks,
                                                std::vector<std::vector<uint8_t> >* out_data_chunk_vec_ptr)
{
    out_data_chunk_vec_ptr->clear();
    out_data_chunk_vec_ptr->resize(in_n_data_chunks);

    {
        std::lock_guard<std::mutex> lock(m_chunks.mutex);

        for (uint32_t n_data_chunk = 0;
                      n_data_chunk < in_n_data_chunks;
                    ++n_data_chunk)
        {
            const auto slot_ptr = find_chunk_ptr(in_first_data_chunk_id + n_data_chunk);

            if (slot_ptr != nullptr)
            {
                m_n_held_bytes -= (*slot_ptr)->size() + get_chunk_overhead_n_bytes();

                out_data_chunk_vec_ptr->at(n_data_chunk) = std::move(**slot_ptr);

                m_chunks.pool.recycle(slot_ptr);
            }
        }

        trim();
    }
}

void APIInterceptor::DataChunkStore::trim()
{
    while (m_chunks.chunk_deque.empty() == false   &&
           m_chunks.chunk_deque.front() == nullptr)
    {
        m_chunks.chunk_deque.pop_front();

        m_chunks.first_id++;
    }
}
