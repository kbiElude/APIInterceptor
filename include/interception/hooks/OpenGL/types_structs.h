/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_TYPES_STRUCTS_H
#define AI_TYPES_STRUCTS_H

#include "interception/hooks/OpenGL/buffer_binding_tracker.h"
#include "interception/hooks/OpenGL/mapped_buffer_write_tracker.h"
#include "interception/hooks/OpenGL/client_vertex_array_tracker.h"
#include "interception/hooks/OpenGL/pixel_store_modes.h"
#include "interception/hooks/OpenGL/texture_binding_tracker.h"
#include "interception/hooks/OpenGL/i_context.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            struct ContextState
            {
                BufferBindingTracker     buffer_binding_tracker;
                ClientVertexArrayTracker client_vertex_array_tracker;
                MappedBufferWriteTracker mapped_buffer_write_tracker;
                PixelStoreModes          pixel_store_modes;
                TextureBindingTracker    texture_binding_tracker;
            };

            struct DispatchTable
            {
                Context* bound_context_ptr;

                DispatchTable();
            };
        }
    }
}

#endif /* AI_TYPES_STRUCTS_H */