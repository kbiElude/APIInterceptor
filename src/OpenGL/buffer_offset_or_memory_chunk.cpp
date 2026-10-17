/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/buffer_offset_or_memory_chunk.h"

OpenGL::BufferOffsetOrMemoryChunk::BufferOffsetOrMemoryChunk()
    :m_chunk           (nullptr,
                        0,
                        sizeof(uint8_t) ),
     m_is_buffer_offset(false),
     m_ptr             (nullptr)
{
    /* Stub */
}

OpenGL::BufferOffsetOrMemoryChunk::BufferOffsetOrMemoryChunk(const void*     in_ptr,
                                                             const uint64_t& in_n_bytes,
                                                             const bool&     in_is_buffer_offset)
    :m_chunk           (in_ptr,
                        static_cast<int64_t>(in_n_bytes),
                        sizeof(uint8_t) ),
     m_is_buffer_offset(in_is_buffer_offset),
     m_ptr             (in_ptr)
{
    /* Stub */
}

APIInterceptor::APIFunctionArgument OpenGL::BufferOffsetOrMemoryChunk::get_arg()
{
    APIInterceptor::APIFunctionArgument result;

    if (m_is_buffer_offset)
    {
        result = APIInterceptor::APIFunctionArgument::create_void_ptr(m_ptr);
    }
    else
    {
        result = APIInterceptor::APIFunctionArgument::create_data_chunk_id(m_chunk.get_id() );
    }

    return result;
}
