/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#if !defined(OPENGL_STRING_ARRAY_CHUNK_H)
#define OPENGL_STRING_ARRAY_CHUNK_H

#include "common/callbacks.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            /* Copies an array of strings, as passed to e.g. glShaderSource, into a data chunk. As with StringChunk, the copy is
             * made when the ID is asked for for the first time.
             *
             * Layout of the chunk: uint32_t n strings, followed by, for each string, uint32_t n characters and the characters
             * (no terminator). The lengths are worked out the way GL does: a string is NUL-terminated if the array of lengths
             * is null, or if its length is negative. A null string is stored as empty. If the array itself is null, or the
             * count is not positive, the chunk is empty.
             */
            class StringArrayChunk
            {
            public:
                StringArrayChunk(const char* const* in_strings_ptr,
                                 const int32_t&     in_n_strings,
                                 const int32_t*     in_lengths_ptr);

                APIInterceptor::DataChunkID get_id();

            private:
                APIInterceptor::DataChunkID m_id;
                bool                        m_is_registered;
                const int32_t*              m_lengths_ptr;
                int32_t                     m_n_strings;
                const char* const*          m_strings_ptr;
            };
        }
    }
}

#endif /* OPENGL_STRING_ARRAY_CHUNK_H */
