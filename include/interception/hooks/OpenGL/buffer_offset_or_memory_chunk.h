/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#if !defined(OPENGL_BUFFER_OFFSET_OR_MEMORY_CHUNK_H)
#define OPENGL_BUFFER_OFFSET_OR_MEMORY_CHUNK_H

#include "common/memory_chunk.h"
#include "common/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            /* The data which a call refers to by a pointer that is either an offset in a buffer bound to a binding point, or
             * the address of client memory:
             *  - An offset is recorded as it is, and the memory behind it is not touched.
             *  - Client memory is copied into a data chunk, when the argument is asked for for the first time.
             *
             * Base of the classes which know the size of the data (see PixelDataChunk, IndirectCommandChunk).
             */
            class BufferOffsetOrMemoryChunk
            {
            public:
                BufferOffsetOrMemoryChunk();

                /* The argument which stands for the data: a pointer (an offset in a buffer), or a data chunk ID. */
                APIInterceptor::APIFunctionArgument get_arg();

            protected:
                BufferOffsetOrMemoryChunk(const void*     in_ptr,
                                          const uint64_t& in_n_bytes,
                                          const bool&     in_is_buffer_offset);

            private:
                APIInterceptor::MemoryChunk m_chunk;
                bool                        m_is_buffer_offset;
                const void*                 m_ptr;
            };
        }
    }
}

#endif /* OPENGL_BUFFER_OFFSET_OR_MEMORY_CHUNK_H */
