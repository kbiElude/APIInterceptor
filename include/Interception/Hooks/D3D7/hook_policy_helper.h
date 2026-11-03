/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * What the policies of the methods of D3D7 (see D3D7/hook_policy.h) have in common.
 */
#ifndef D3D7_HOOK_POLICY_HELPER_H
#define D3D7_HOOK_POLICY_HELPER_H

#include "Interception/Hooks/D3D7/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace D3D7
        {
            class HookPolicyHelper
            {
            public:
                /* The data written to the locked resource (see Common/lock_capture.h). */
                static APIInterceptor::APIFunctionArgument create_locked_data_argument(const void*     in_object_ptr,
                                                                                       const uint32_t& in_level);

                /* The arrays a strided draw reads its n_vertices vertices from, as one data chunk. The arrays are in the order of the
                 * fields of the structure (the position, the normal, the diffuse and specular colors, and the texture coordinates of
                 * each of the 8 stages); one which the vertex format does not have, or the structure does not point at, is empty.
                 * The chunk is the number of the arrays (a uint32_t), then the size in bytes of each, then the arrays themselves,
                 * one after the other.
                 */
                static APIInterceptor::APIFunctionArgument create_strided_data_argument(const D3DDRAWPRIMITIVESTRIDEDDATA* in_strided_data_ptr,
                                                                                        const uint32_t&                    in_vertex_format,
                                                                                        const uint32_t&                    in_n_vertices);

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

                /* Hooks the object that was asked for with QueryInterface by the interface it was asked for, if it is described. */
                static void patch_object_for_iid(const GUID& in_iid,
                                                 void*       in_object_ptr);
            };
        }
    }
}

#endif /* D3D7_HOOK_POLICY_HELPER_H */
