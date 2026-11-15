/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Captures what the application writes to a locked D3D7 surface or vertex buffer.
 */
#ifndef D3D7_LOCKED_RESOURCE_CAPTURE_H
#define D3D7_LOCKED_RESOURCE_CAPTURE_H

#include "common/api_function_argument.h"
#include "interception/hooks/D3D7/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace D3D7
        {
            class LockedResourceCapture
            {
            public:
                /* The data written to the locked resource (see common/lock_capture.h). */
                static APIInterceptor::APIFunctionArgument create_locked_data_argument(const void*     in_object_ptr,
                                                                                       const uint32_t& in_level);

                /* Remembers the region of a surface that was locked. */
                static void on_surface_locked(const void*           in_surface_ptr,
                                              const RECT*           in_rect_ptr,
                                              const DDSURFACEDESC2* in_locked_description_ptr,
                                              const DWORD&          in_flags);

                /* Remembers the memory of a vertex buffer that was locked. */
                static void on_vertex_buffer_locked(IDirect3DVertexBuffer7* in_vertex_buffer_ptr,
                                                    const DWORD&            in_flags,
                                                    void* const*            in_data_ptr_ptr,
                                                    const DWORD*            in_size_ptr);
            };
        }
    }
}

#endif /* D3D7_LOCKED_RESOURCE_CAPTURE_H */
