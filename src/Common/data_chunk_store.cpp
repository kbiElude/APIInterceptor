/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/data_chunk_store.h"
#include <string.h>

APIInterceptor::DataChunkStore::ChunkUniquePtr* APIInterceptor::DataChunkStore::find_chunk_ptr(const DataChunkID& in_data_chunk_id)
{
    ChunkUniquePtr* result_ptr = nullptr;

    if (in_data_chunk_id >= m_chunks.first_id)
    {
        const size_t index = in_data_chunk_id - m_chunks.first_id;

        if (index < m_chunks.chunk_deque.size()          &&
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
            *out_data_ptr_ptr = (*slot_ptr)->data ();
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

APIInterceptor::DataChunkStore* APIInterceptor::DataChunkStore::get_ptr()
{
    /* Never destroyed: hooks can still run during shutdown. */
    static DataChunkStore* instance_ptr = new DataChunkStore();

    return instance_ptr;
}

APIInterceptor::DataChunkID APIInterceptor::DataChunkStore::register_chunk(const void*     in_data_ptr,
                                                                           const uint32_t& in_n_bytes)
{
    ChunkUniquePtr new_chunk_ptr(new std::vector<uint8_t>(in_n_bytes) );
    DataChunkID    result = 0;

    if (in_n_bytes != 0)
    {
        ::memcpy(new_chunk_ptr->data(),
                 in_data_ptr,
                 in_n_bytes);
    }

    {
        std::lock_guard<std::mutex> lock(m_chunks.mutex);

        result = m_chunks.first_id + static_cast<uint32_t>(m_chunks.chunk_deque.size() );

        m_chunks.chunk_deque.emplace_back(std::move(new_chunk_ptr) );
    }

    return result;
}

void APIInterceptor::DataChunkStore::release(const DataChunkID& in_data_chunk_id)
{
    std::lock_guard<std::mutex> lock(m_chunks.mutex);

    const auto slot_ptr = find_chunk_ptr(in_data_chunk_id);

    if (slot_ptr != nullptr)
    {
        slot_ptr->reset();

        trim();
    }
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
            /* The buffer which the caller had goes to the store, which frees it: nothing is allocated here. */
            out_data_chunk_ptr->swap(**slot_ptr);

            slot_ptr->reset();

            trim();

            result = true;
        }
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
                out_data_chunk_vec_ptr->at(n_data_chunk) = std::move(**slot_ptr);

                slot_ptr->reset();
            }
        }

        trim();
    }
}

void APIInterceptor::DataChunkStore::trim()
{
    while (m_chunks.chunk_deque.empty() == false &&
           m_chunks.chunk_deque.front()   == nullptr)
    {
        m_chunks.chunk_deque.pop_front();

        m_chunks.first_id++;
    }
}
