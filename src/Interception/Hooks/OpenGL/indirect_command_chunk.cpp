/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Interception/Hooks/OpenGL/indirect_command_chunk.h"
#include "Interception/Hooks/OpenGL/state_tracker.h"

Interception::Hooks::OpenGL::IndirectCommandChunk::IndirectCommandChunk()
{
    /* Stub */
}

Interception::Hooks::OpenGL::IndirectCommandChunk::IndirectCommandChunk(const void*     in_indirect_ptr,
                                                                        const uint64_t& in_n_bytes,
                                                                        const bool&     in_is_buffer_offset)
    :BufferOffsetOrMemoryChunk(in_indirect_ptr,
                               in_n_bytes,
                               in_is_buffer_offset)
{
    /* Stub */
}

Interception::Hooks::OpenGL::IndirectCommandChunk Interception::Hooks::OpenGL::IndirectCommandChunk::create(const void*     in_indirect_ptr,
                                                                                                            const int64_t&  in_n_commands,
                                                                                                            const uint32_t& in_stride,
                                                                                                            const uint32_t& in_command_n_bytes)
{
    const auto&    context = get_context_state();
    uint64_t       n_bytes = 0;
    const uint64_t stride  = (in_stride != 0) ? in_stride
                                              : in_command_n_bytes;

    if (in_n_commands > 0)
    {
        n_bytes = static_cast<uint64_t>(in_n_commands - 1) * stride + in_command_n_bytes;
    }

    return IndirectCommandChunk(in_indirect_ptr,
                                n_bytes,
                                context.buffer_manager.get_bound_buffer(BufferBindingTarget::DRAW_INDIRECT_BUFFER) != 0);
}

Interception::Hooks::OpenGL::IndirectCommandChunk Interception::Hooks::OpenGL::IndirectCommandChunk::create_for_draw_arrays(const void*     in_indirect_ptr,
                                                                                                                            const int64_t&  in_n_commands,
                                                                                                                            const uint32_t& in_stride)
{
    /* DrawArraysIndirectCommand: count, instanceCount, first, baseInstance. */
    constexpr uint32_t N_FIELDS = 4;

    return create(in_indirect_ptr,
                  in_n_commands,
                  in_stride,
                  N_FIELDS * sizeof(uint32_t) );
}

Interception::Hooks::OpenGL::IndirectCommandChunk Interception::Hooks::OpenGL::IndirectCommandChunk::create_for_draw_elements(const void*     in_indirect_ptr,
                                                                                                                              const int64_t&  in_n_commands,
                                                                                                                              const uint32_t& in_stride)
{
    /* DrawElementsIndirectCommand: count, instanceCount, firstIndex, baseVertex, baseInstance. */
    constexpr uint32_t N_FIELDS = 5;

    return create(in_indirect_ptr,
                  in_n_commands,
                  in_stride,
                  N_FIELDS * sizeof(uint32_t) );
}
