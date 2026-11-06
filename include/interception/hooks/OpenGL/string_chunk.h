/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#if !defined(OPENGL_STRING_CHUNK_H)
#define OPENGL_STRING_CHUNK_H

#include "common/callbacks.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            /* Copies a NUL-terminated string into a data chunk. The copy is made when the ID is asked for for the first time,
             * and only then, so that nothing is copied when no callback wants the arguments. Later calls return the same chunk.
             *
             * The chunk holds the characters and the terminator. A null string gives an empty chunk.
             */
            class StringChunk
            {
            public:
                StringChunk(const char* in_string_ptr);

                APIInterceptor::DataChunkID get_id();

            private:
                APIInterceptor::DataChunkID m_id;
                bool                        m_is_registered;
                const char*                 m_string_ptr;
            };
        }
    }
}

#endif /* OPENGL_STRING_CHUNK_H */
