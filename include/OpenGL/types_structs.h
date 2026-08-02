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

    struct ContextState
    {
        GLuint                                           bound_buffers[static_cast<size_t>(BufferBindingTarget::COUNT)];
        std::unordered_map<GLuint, BufferPropsUniquePtr> buffer_object_id_to_buffer_props_ptr_map;

        ContextState();
    };

    struct DispatchTable
    {
        Context* bound_context_ptr;

        DispatchTable();
    };
}

#endif /* AI_TYPES_STRUCTS_H */