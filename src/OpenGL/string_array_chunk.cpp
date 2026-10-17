/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/string_array_chunk.h"
#include <string.h>
#include <vector>

OpenGL::StringArrayChunk::StringArrayChunk(const char* const* in_strings_ptr,
                                           const int32_t&     in_n_strings,
                                           const int32_t*     in_lengths_ptr)
    :m_id           (0),
     m_is_registered(false),
     m_lengths_ptr  (in_lengths_ptr),
     m_n_strings    (in_n_strings),
     m_strings_ptr  (in_strings_ptr)
{
    /* Stub */
}

APIInterceptor::DataChunkID OpenGL::StringArrayChunk::get_id()
{
    if (m_is_registered == false)
    {
        std::vector<uint8_t> chunk_u8_vec;

        if (m_strings_ptr != nullptr &&
            m_n_strings   >  0)
        {
            const uint32_t n_strings = static_cast<uint32_t>(m_n_strings);

            chunk_u8_vec.insert(chunk_u8_vec.end(),
                                reinterpret_cast<const uint8_t*>(&n_strings),
                                reinterpret_cast<const uint8_t*>(&n_strings) + sizeof(n_strings) );

            for (int32_t n_string = 0;
                         n_string < m_n_strings;
                       ++n_string)
            {
                const bool  is_nul_terminated = (m_lengths_ptr == nullptr || m_lengths_ptr[n_string] < 0);
                uint32_t    n_characters      = 0;
                const char* string_ptr        = m_strings_ptr[n_string];

                if (string_ptr != nullptr)
                {
                    n_characters = is_nul_terminated ? static_cast<uint32_t>(::strlen(string_ptr) )
                                                     : static_cast<uint32_t>(m_lengths_ptr[n_string]);
                }

                chunk_u8_vec.insert(chunk_u8_vec.end(),
                                    reinterpret_cast<const uint8_t*>(&n_characters),
                                    reinterpret_cast<const uint8_t*>(&n_characters) + sizeof(n_characters) );

                if (n_characters != 0)
                {
                    chunk_u8_vec.insert(chunk_u8_vec.end(),
                                        reinterpret_cast<const uint8_t*>(string_ptr),
                                        reinterpret_cast<const uint8_t*>(string_ptr) + n_characters);
                }
            }
        }

        m_id            = APIInterceptor::register_data_chunk(chunk_u8_vec.data(),
                                                              static_cast<uint32_t>(chunk_u8_vec.size() ) );
        m_is_registered = true;
    }

    return m_id;
}
