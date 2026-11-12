/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "common/chunk_pool.h"

APIInterceptor::ChunkPool::ChunkPool()
{
    /* Stub */
}

APIInterceptor::ChunkPool::ChunkUniquePtr APIInterceptor::ChunkPool::acquire()
{
    ChunkUniquePtr result_ptr;

    if (m_chunk_ptr_vec.empty() == false)
    {
        result_ptr = std::move(m_chunk_ptr_vec.back() );

        m_chunk_ptr_vec.pop_back();
    }
    else
    {
        result_ptr.reset(new std::vector<uint8_t>() );
    }

    return result_ptr;
}

uint32_t APIInterceptor::ChunkPool::get_max_n_pooled_chunks()
{
    constexpr uint32_t MAX_N_POOLED_CHUNKS = 16384;

    return MAX_N_POOLED_CHUNKS;
}

uint32_t APIInterceptor::ChunkPool::get_n_pooled() const
{
    return static_cast<uint32_t>(m_chunk_ptr_vec.size() );
}

uint32_t APIInterceptor::ChunkPool::get_small_chunk_max_n_bytes()
{
    constexpr uint32_t SMALL_CHUNK_MAX_N_BYTES = 256;

    return SMALL_CHUNK_MAX_N_BYTES;
}

void APIInterceptor::ChunkPool::recycle(ChunkUniquePtr* inout_chunk_ptr_ptr)
{
    const uint32_t max_n_pooled_chunks     = get_max_n_pooled_chunks();
    const uint32_t small_chunk_max_n_bytes = get_small_chunk_max_n_bytes();

    if (*inout_chunk_ptr_ptr != nullptr)
    {
        const size_t capacity = (*inout_chunk_ptr_ptr)->capacity();
        const size_t n_pooled = m_chunk_ptr_vec.size();

        if (capacity <= small_chunk_max_n_bytes &&
            n_pooled <  max_n_pooled_chunks)
        {
            (*inout_chunk_ptr_ptr)->clear();

            m_chunk_ptr_vec.push_back(std::move(*inout_chunk_ptr_ptr) );
        }
    }

    /* A vector that was not kept is destroyed. */
    inout_chunk_ptr_ptr->reset();
}
