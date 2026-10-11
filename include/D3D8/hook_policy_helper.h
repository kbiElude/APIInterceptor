/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Helpers of the hook policies (see D3D8/hook_policy.h).
 */
#ifndef D3D8_HOOK_POLICY_HELPER_H
#define D3D8_HOOK_POLICY_HELPER_H

#include "D3D8/types.h"

namespace D3D8
{
    class HookPolicyHelper
    {
    public:
        /* Captures the contents of the region which is about to be unlocked. */
        static APIInterceptor::APIFunctionArgument create_locked_data_argument(const void*     in_object_ptr,
                                                                               const uint32_t& in_level);

        /* Cube map faces are tracked as levels of their own. */
        static uint32_t get_cube_face_level_key(const D3DCUBEMAP_FACES& in_face,
                                                const uint32_t&         in_level);

        /* Number of tokens of a vertex or pixel shader (version 1.x), the end token included. Shaders are not
         * length-prefixed.
         */
        static uint32_t get_n_shader_function_tokens(const DWORD* in_function_ptr);

        /* Number of tokens of a vertex shader declaration, the end token included. */
        static uint32_t get_n_vertex_declaration_tokens(const DWORD* in_declaration_ptr);

        /* Number of vertices which a draw call consumes. */
        static uint32_t get_n_vertices(const D3DPRIMITIVETYPE& in_primitive_type,
                                       const uint32_t&         in_primitive_count);

        /* Bytes of the pixels in rows of a surface, for a given format. Compressed formats are counted in 4x4 blocks. */
        static uint32_t get_surface_region_n_bytes(const D3DFORMAT& in_format,
                                                   const uint32_t&  in_width,
                                                   const uint32_t&  in_height,
                                                   const uint32_t&  in_pitch);

        /* Remembers a locked box of a volume (a volume texture level is a volume). */
        static void on_box_locked(const void*           in_object_ptr,
                                  const uint32_t&       in_level,
                                  const D3DVOLUME_DESC& in_description,
                                  const D3DLOCKED_BOX*  in_locked_box_ptr,
                                  const D3DBOX*         in_box_ptr,
                                  const DWORD&          in_flags);

        /* Remembers a locked range of a buffer; a size of 0 locks everything from the offset. */
        static void on_buffer_locked(const void*     in_object_ptr,
                                     const uint32_t& in_buffer_n_bytes,
                                     const UINT&     in_offset_to_lock,
                                     const UINT&     in_size_to_lock,
                                     BYTE* const*    in_data_ptr_ptr,
                                     const DWORD&    in_flags);

        /* Remembers a locked rectangle of a surface (a texture level is a surface). */
        static void on_rect_locked(const void*            in_object_ptr,
                                   const uint32_t&        in_level,
                                   const D3DSURFACE_DESC& in_description,
                                   const D3DLOCKED_RECT*  in_locked_rect_ptr,
                                   const RECT*            in_rect_ptr,
                                   const DWORD&           in_flags);
    };
}

#endif /* D3D8_HOOK_POLICY_HELPER_H */
