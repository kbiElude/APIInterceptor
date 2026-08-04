/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_TYPES_STRUCTS_H
#define AI_TYPES_STRUCTS_H

#include "OpenGL/types_interfaces.h"

namespace OpenGL
{
    struct BufferMappingState
    {
        BufferMappingAccess access     = BufferMappingAccess::UNKNOWN;
        void*               mapped_ptr = nullptr;
    };

    struct BufferProps
    {
        BufferMappingState mapping_state;
        uint32_t           size_bytes    = 0;
    };

    typedef std::unique_ptr<BufferProps> BufferPropsUniquePtr;

    struct TextureLevelProps
    {
        uint32_t compressed_size_bytes = 0;
        uint32_t depth                 = 0;
        uint32_t height                = 0;
        uint32_t width                 = 0;
    };

    struct ContextState
    {
        GLuint                                           bound_buffers[static_cast<size_t>(BufferBindingTarget::COUNT)];
        GLuint                                           bound_textures[static_cast<size_t>(TextureBindingTarget::COUNT)];
        std::unordered_map<GLuint, BufferPropsUniquePtr> buffer_object_id_to_buffer_props_ptr_map;

        /* Keyed by (texture_object_id * 1000 + level). Stores per-level dimensions set by TexImage* and CopyTexImage*. */
        std::unordered_map<uint64_t, TextureLevelProps>  texture_level_props_map;

        ContextState();

        TextureLevelProps get_texture_level_props(GLuint   in_texture_id,
                                                  GLint    in_level) const;
        void              set_texture_level_props(GLuint   in_texture_id,
                                                  GLint    in_level,
                                                  uint32_t in_width,
                                                  uint32_t in_height,
                                                  uint32_t in_depth);
    };

    struct DispatchTable
    {
        Context* bound_context_ptr;

        DispatchTable();
    };
}

#endif /* AI_TYPES_STRUCTS_H */