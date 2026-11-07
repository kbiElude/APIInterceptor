/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#if !defined(COMMON_MEMORY_CHUNK_H)
#define COMMON_MEMORY_CHUNK_H

#include "common/callbacks.h"

namespace APIInterceptor
{
    /* Copies an array which an API call reads from client memory into a data chunk. As with StringChunk, the copy is
     * made when the ID is asked for for the first time, and only then.
     *
     * The chunk is empty if the pointer is null, or if there is nothing to copy (e.g. a count which is not positive).
     */
    class MemoryChunk
    {
    public:
        MemoryChunk(const void*   in_data_ptr,
                   const int64_t& in_n_elements,
                   const size_t&  in_element_n_bytes);

        DataChunkID get_id();

    private:
        const void*  m_data_ptr;
        size_t       m_element_n_bytes;
        DataChunkID  m_id;
        bool         m_is_registered;
        int64_t      m_n_elements;
    };
}

#endif /* COMMON_MEMORY_CHUNK_H */
