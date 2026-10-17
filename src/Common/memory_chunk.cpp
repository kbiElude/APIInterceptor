/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/macros.h"
#include "Common/memory_chunk.h"

APIInterceptor::MemoryChunk::MemoryChunk(const void*    in_data_ptr,
                                         const int64_t& in_n_elements,
                                         const size_t&  in_element_n_bytes)
    :m_data_ptr       (in_data_ptr),
     m_element_n_bytes(in_element_n_bytes),
     m_id             (0),
     m_is_registered  (false),
     m_n_elements     (in_n_elements)
{
    /* Stub */
}

APIInterceptor::DataChunkID APIInterceptor::MemoryChunk::get_id()
{
    if (m_is_registered == false)
    {
        uint64_t n_bytes = 0;

        if (m_data_ptr   != nullptr &&
            m_n_elements >  0)
        {
            n_bytes = static_cast<uint64_t>(m_n_elements) * m_element_n_bytes;
        }

        /* Chunk sizes are 32-bit. */
        AI_ASSERT(n_bytes <= UINT32_MAX);

        if (n_bytes > UINT32_MAX)
        {
            n_bytes = 0;
        }

        m_id            = APIInterceptor::register_data_chunk(m_data_ptr,
                                                              static_cast<uint32_t>(n_bytes) );
        m_is_registered = true;
    }

    return m_id;
}
