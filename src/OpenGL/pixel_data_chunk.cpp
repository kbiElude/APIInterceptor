/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/pixel_data_chunk.h"
#include "OpenGL/state_tracker.h"
#include "OpenGL/utils.h"

OpenGL::PixelDataChunk::PixelDataChunk()
{
    /* Stub */
}

OpenGL::PixelDataChunk::PixelDataChunk(const void*     in_pixels_ptr,
                                       const uint64_t& in_n_bytes,
                                       const bool&     in_is_buffer_offset)
    :BufferOffsetOrMemoryChunk(in_pixels_ptr,
                               in_n_bytes,
                               in_is_buffer_offset)
{
    /* Stub */
}

OpenGL::PixelDataChunk OpenGL::PixelDataChunk::create_for_pack(const void*     in_pixels_ptr,
                                                               const int64_t&  in_width,
                                                               const int64_t&  in_height,
                                                               const int64_t&  in_depth,
                                                               const uint32_t& in_format,
                                                               const uint32_t& in_type)
{
    auto& context = get_context_state();

    return PixelDataChunk(in_pixels_ptr,
                          context.pixel_store_manager.get_n_pack_bytes(in_width,
                                                                       in_height,
                                                                       in_depth,
                                                                       in_format,
                                                                       in_type),
                          context.buffer_manager.get_bound_buffer(BufferBindingTarget::PIXEL_PACK_BUFFER) != 0);
}

OpenGL::PixelDataChunk OpenGL::PixelDataChunk::create_for_texel(const void*     in_texel_ptr,
                                                                const uint32_t& in_format,
                                                                const uint32_t& in_type)
{
    return PixelDataChunk(in_texel_ptr,
                          OpenGL::Utils::get_n_texel_bytes(in_format,
                                                           in_type),
                          false /* in_is_buffer_offset */);
}

OpenGL::PixelDataChunk OpenGL::PixelDataChunk::create_for_unpack(const void*     in_pixels_ptr,
                                                                 const int64_t&  in_width,
                                                                 const int64_t&  in_height,
                                                                 const int64_t&  in_depth,
                                                                 const uint32_t& in_format,
                                                                 const uint32_t& in_type)
{
    auto& context = get_context_state();

    return PixelDataChunk(in_pixels_ptr,
                          context.pixel_store_manager.get_n_unpack_bytes(in_width,
                                                                         in_height,
                                                                         in_depth,
                                                                         in_format,
                                                                         in_type),
                          context.buffer_manager.get_bound_buffer(BufferBindingTarget::PIXEL_UNPACK_BUFFER) != 0);
}

OpenGL::PixelDataChunk OpenGL::PixelDataChunk::create_for_unpack_bitmap(const void*    in_bitmap_ptr,
                                                                        const int64_t& in_width,
                                                                        const int64_t& in_height)
{
    auto& context = get_context_state();

    return PixelDataChunk(in_bitmap_ptr,
                          context.pixel_store_manager.get_n_unpack_bitmap_bytes(in_width,
                                                                                in_height),
                          context.buffer_manager.get_bound_buffer(BufferBindingTarget::PIXEL_UNPACK_BUFFER) != 0);
}

OpenGL::PixelDataChunk OpenGL::PixelDataChunk::create_for_unpack_bytes(const void*     in_pixels_ptr,
                                                                       const uint64_t& in_n_bytes)
{
    auto& context = get_context_state();

    return PixelDataChunk(in_pixels_ptr,
                          in_n_bytes,
                          context.buffer_manager.get_bound_buffer(BufferBindingTarget::PIXEL_UNPACK_BUFFER) != 0);
}
