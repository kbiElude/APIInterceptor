/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_TYPES_STRUCTS_H
#define AI_TYPES_STRUCTS_H

#include "Interception/Hooks/OpenGL/buffer_manager.h"
#include "Interception/Hooks/OpenGL/buffer_mapping_manager.h"
#include "Interception/Hooks/OpenGL/client_array_manager.h"
#include "Interception/Hooks/OpenGL/pixel_store_manager.h"
#include "Interception/Hooks/OpenGL/texture_manager.h"
#include "Interception/Hooks/OpenGL/types_interfaces.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            struct ContextState
            {
                BufferManager         buffer_manager;
                BufferMappingManager  buffer_mapping_manager;
                ClientArrayManager    client_array_manager;
                PixelStoreManager     pixel_store_manager;
                TextureManager        texture_manager;
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