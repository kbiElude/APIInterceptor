/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "interception/hooks/OpenGL/string_chunk.h"
#include <string.h>

Interception::Hooks::OpenGL::StringChunk::StringChunk(const char* in_string_ptr)
    :m_id           (0),
     m_is_registered(false),
     m_string_ptr   (in_string_ptr)
{
    /* Stub */
}

APIInterceptor::DataChunkID Interception::Hooks::OpenGL::StringChunk::get_id()
{
    if (m_is_registered == false)
    {
        const uint32_t n_bytes = (m_string_ptr != nullptr) ? static_cast<uint32_t>(::strlen(m_string_ptr) + 1)
                                                           : 0;

        m_id            = APIInterceptor::register_data_chunk(m_string_ptr,
                                                              n_bytes);
        m_is_registered = true;
    }

    return m_id;
}
