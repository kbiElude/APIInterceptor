/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#if !defined(OPENGL_INDIRECT_COMMAND_CHUNK_H)
#define OPENGL_INDIRECT_COMMAND_CHUNK_H

#include "Interception/Hooks/OpenGL/buffer_offset_or_memory_chunk.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            /* The draw commands which an indirect draw call reads. How they are recorded depends on where they are:
             *  - If a buffer is bound to the draw indirect binding point, the pointer is an offset in that buffer. It is
             *    recorded as it is; the buffer contents get recorded by the calls which fill the buffer.
             *  - Otherwise, the commands are copied into a data chunk, when the argument is asked for for the first time.
             *
             * Must be created from within an intercepted API call.
             */
            class IndirectCommandChunk : public BufferOffsetOrMemoryChunk
            {
            public:
                IndirectCommandChunk();

                /* A stride of zero means that the commands are tightly packed. */
                static IndirectCommandChunk create_for_draw_arrays  (const void*     in_indirect_ptr,
                                                                     const int64_t&  in_n_commands,
                                                                     const uint32_t& in_stride);
                static IndirectCommandChunk create_for_draw_elements(const void*     in_indirect_ptr,
                                                                     const int64_t&  in_n_commands,
                                                                     const uint32_t& in_stride);

            private:
                IndirectCommandChunk(const void*     in_indirect_ptr,
                                     const uint64_t& in_n_bytes,
                                     const bool&     in_is_buffer_offset);

                static IndirectCommandChunk create(const void*     in_indirect_ptr,
                                                   const int64_t&  in_n_commands,
                                                   const uint32_t& in_stride,
                                                   const uint32_t& in_command_n_bytes);
            };
        }
    }
}

#endif /* OPENGL_INDIRECT_COMMAND_CHUNK_H */
