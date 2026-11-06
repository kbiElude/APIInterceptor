/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Interception/Hooks/OpenGL/pixel_data_chunk.h"
#include "Interception/Hooks/OpenGL/state_tracker.h"
#include "Interception/Hooks/OpenGL/utils.h"

Interception::Hooks::OpenGL::PixelDataChunk::PixelDataChunk()
{
    /* Stub */
}

Interception::Hooks::OpenGL::PixelDataChunk::PixelDataChunk(const void*     in_pixels_ptr,
                                                            const uint64_t& in_n_bytes,
                                                            const bool&     in_is_buffer_offset)
    :BufferOffsetOrMemoryChunk(in_pixels_ptr,
                               in_n_bytes,
                               in_is_buffer_offset)
{
    /* Stub */
}

Interception::Hooks::OpenGL::PixelDataChunk Interception::Hooks::OpenGL::PixelDataChunk::create_for_pack(const void*     in_pixels_ptr,
                                                                                                         const int64_t&  in_width,
                                                                                                         const int64_t&  in_height,
                                                                                                         const int64_t&  in_depth,
                                                                                                         const uint32_t& in_format,
                                                                                                         const uint32_t& in_type)
{
    auto&          context          = get_context_state();
    const uint32_t bound_buffer     = context.buffer_manager.get_bound_buffer(BufferBindingTarget::PIXEL_PACK_BUFFER);
    const uint64_t n_bytes          = context.pixel_store_manager.get_n_pack_bytes(in_width,
                                                                                   in_height,
                                                                                   in_depth,
                                                                                   in_format,
                                                                                   in_type);
    const bool     is_buffer_offset = (bound_buffer != 0);

    return PixelDataChunk(in_pixels_ptr,
                          n_bytes,
                          is_buffer_offset);
}

Interception::Hooks::OpenGL::PixelDataChunk Interception::Hooks::OpenGL::PixelDataChunk::create_for_texel(const void*     in_texel_ptr,
                                                                                                          const uint32_t& in_format,
                                                                                                          const uint32_t& in_type)
{
    const uint32_t n_bytes = Interception::Hooks::OpenGL::Utils::get_n_texel_bytes(in_format,
                                                                                   in_type);

    return PixelDataChunk(in_texel_ptr,
                          n_bytes,
                          false /* in_is_buffer_offset */);
}

Interception::Hooks::OpenGL::PixelDataChunk Interception::Hooks::OpenGL::PixelDataChunk::create_for_unpack(const void*     in_pixels_ptr,
                                                                                                           const int64_t&  in_width,
                                                                                                           const int64_t&  in_height,
                                                                                                           const int64_t&  in_depth,
                                                                                                           const uint32_t& in_format,
                                                                                                           const uint32_t& in_type)
{
    auto&          context          = get_context_state();
    const uint32_t bound_buffer     = context.buffer_manager.get_bound_buffer(BufferBindingTarget::PIXEL_UNPACK_BUFFER);
    const uint64_t n_bytes          = context.pixel_store_manager.get_n_unpack_bytes(in_width,
                                                                                     in_height,
                                                                                     in_depth,
                                                                                     in_format,
                                                                                     in_type);
    const bool     is_buffer_offset = (bound_buffer != 0);

    return PixelDataChunk(in_pixels_ptr,
                          n_bytes,
                          is_buffer_offset);
}

Interception::Hooks::OpenGL::PixelDataChunk Interception::Hooks::OpenGL::PixelDataChunk::create_for_unpack_bitmap(const void*    in_bitmap_ptr,
                                                                                                                  const int64_t& in_width,
                                                                                                                  const int64_t& in_height)
{
    auto&          context          = get_context_state();
    const uint32_t bound_buffer     = context.buffer_manager.get_bound_buffer(BufferBindingTarget::PIXEL_UNPACK_BUFFER);
    const uint64_t n_bytes          = context.pixel_store_manager.get_n_unpack_bitmap_bytes(in_width,
                                                                                            in_height);
    const bool     is_buffer_offset = (bound_buffer != 0);

    return PixelDataChunk(in_bitmap_ptr,
                          n_bytes,
                          is_buffer_offset);
}

Interception::Hooks::OpenGL::PixelDataChunk Interception::Hooks::OpenGL::PixelDataChunk::create_for_unpack_bytes(const void*     in_pixels_ptr,
                                                                                                                 const uint64_t& in_n_bytes)
{
    auto&          context          = get_context_state();
    const uint32_t bound_buffer     = context.buffer_manager.get_bound_buffer(BufferBindingTarget::PIXEL_UNPACK_BUFFER);
    const bool     is_buffer_offset = (bound_buffer != 0);

    return PixelDataChunk(in_pixels_ptr,
                          in_n_bytes,
                          is_buffer_offset);
}
