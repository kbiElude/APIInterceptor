/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Method-specific additions to GenericHook (see D3D8/generic_hook.h): extra arguments holding data which a call refers
 * to, and bookkeeping which follows a call. They follow the method's arguments, and are reported before and after the
 * call.
 */
#ifndef D3D8_HOOK_POLICY_H
#define D3D8_HOOK_POLICY_H

#include "D3D8/hook_policy_base.h"

namespace D3D8
{
    template<APIInterceptor::APIFunction function>
    struct HookPolicy : public HookPolicyBase
    {
        /* Stub */
    };

    template<>
    struct HookPolicy<APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DCUBETEXTURE8_LOCKRECT> : public HookPolicyBase
    {
        static const uint32_t n_extra_arguments = 1; /* locked rectangle */

        static void create_extra_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                           IDirect3DCubeTexture8*               in_self,
                                           D3DCUBEMAP_FACES                     in_face,
                                           UINT                                 in_level,
                                           D3DLOCKED_RECT*                      in_locked_rect_ptr,
                                           const RECT*                          in_rect_ptr,
                                           DWORD                                in_flags);
        static void on_call_finished      (const bool&                          in_is_success,
                                           IDirect3DCubeTexture8*               in_self,
                                           D3DCUBEMAP_FACES                     in_face,
                                           UINT                                 in_level,
                                           D3DLOCKED_RECT*                      in_locked_rect_ptr,
                                           const RECT*                          in_rect_ptr,
                                           DWORD                                in_flags);
    };

    template<>
    struct HookPolicy<APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DCUBETEXTURE8_UNLOCKRECT> : public HookPolicyBase
    {
        static const uint32_t n_extra_arguments = 1; /* locked data */

        static void create_extra_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                           IDirect3DCubeTexture8*               in_self,
                                           D3DCUBEMAP_FACES                     in_face,
                                           UINT                                 in_level);
        static void on_call_finished      (const bool&                          in_is_success,
                                           IDirect3DCubeTexture8*               in_self,
                                           D3DCUBEMAP_FACES                     in_face,
                                           UINT                                 in_level);
    };

    template<>
    struct HookPolicy<APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_CLEAR> : public HookPolicyBase
    {
        static const uint32_t n_extra_arguments = 1; /* rectangles */

        static void create_extra_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                           IDirect3DDevice8*                    in_self,
                                           DWORD                                in_count,
                                           const D3DRECT*                       in_rects_ptr,
                                           DWORD                                in_flags,
                                           D3DCOLOR                             in_color,
                                           float                                in_z,
                                           DWORD                                in_stencil);
    };

    template<>
    struct HookPolicy<APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_COPYRECTS> : public HookPolicyBase
    {
        static const uint32_t n_extra_arguments = 2; /* source rectangles, destination points */

        static void create_extra_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                           IDirect3DDevice8*                    in_self,
                                           IDirect3DSurface8*                   in_source_surface_ptr,
                                           const RECT*                          in_source_rects_ptr,
                                           UINT                                 in_n_rects,
                                           IDirect3DSurface8*                   in_destination_surface_ptr,
                                           const POINT*                         in_destination_points_ptr);
    };

    template<>
    struct HookPolicy<APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_CREATEPIXELSHADER> : public HookPolicyBase
    {
        static const uint32_t n_extra_arguments = 1; /* function tokens */

        static void create_extra_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                           IDirect3DDevice8*                    in_self,
                                           const DWORD*                         in_function_ptr,
                                           DWORD*                               in_handle_ptr);
    };

    template<>
    struct HookPolicy<APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_CREATEVERTEXSHADER> : public HookPolicyBase
    {
        static const uint32_t n_extra_arguments = 2; /* declaration tokens, function tokens */

        static void create_extra_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                           IDirect3DDevice8*                    in_self,
                                           const DWORD*                         in_declaration_ptr,
                                           const DWORD*                         in_function_ptr,
                                           DWORD*                               in_handle_ptr,
                                           DWORD                                in_usage);
    };

    template<>
    struct HookPolicy<APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_DRAWINDEXEDPRIMITIVEUP> : public HookPolicyBase
    {
        static const uint32_t n_extra_arguments = 2; /* index data, vertex data */

        static void create_extra_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                           IDirect3DDevice8*                    in_self,
                                           D3DPRIMITIVETYPE                     in_primitive_type,
                                           UINT                                 in_min_vertex_index,
                                           UINT                                 in_n_vertex_indices,
                                           UINT                                 in_primitive_count,
                                           const void*                          in_index_data_ptr,
                                           D3DFORMAT                            in_index_data_format,
                                           const void*                          in_vertex_data_ptr,
                                           UINT                                 in_vertex_stride);
    };

    template<>
    struct HookPolicy<APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_DRAWPRIMITIVEUP> : public HookPolicyBase
    {
        static const uint32_t n_extra_arguments = 1; /* vertex data */

        static void create_extra_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                           IDirect3DDevice8*                    in_self,
                                           D3DPRIMITIVETYPE                     in_primitive_type,
                                           UINT                                 in_primitive_count,
                                           const void*                          in_vertex_data_ptr,
                                           UINT                                 in_vertex_stride);
    };

    template<>
    struct HookPolicy<APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_SETPALETTEENTRIES> : public HookPolicyBase
    {
        static const uint32_t n_extra_arguments = 1; /* entries */

        static void create_extra_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                           IDirect3DDevice8*                    in_self,
                                           UINT                                 in_palette_number,
                                           const PALETTEENTRY*                  in_entries_ptr);
    };

    template<>
    struct HookPolicy<APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_SETPIXELSHADERCONSTANT> : public HookPolicyBase
    {
        static const uint32_t n_extra_arguments = 1; /* constants */

        static void create_extra_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                           IDirect3DDevice8*                    in_self,
                                           DWORD                                in_register,
                                           const void*                          in_constant_data_ptr,
                                           DWORD                                in_constant_count);
    };

    template<>
    struct HookPolicy<APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_SETVERTEXSHADERCONSTANT> : public HookPolicyBase
    {
        static const uint32_t n_extra_arguments = 1; /* constants */

        static void create_extra_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                           IDirect3DDevice8*                    in_self,
                                           DWORD                                in_register,
                                           const void*                          in_constant_data_ptr,
                                           DWORD                                in_constant_count);
    };

    template<>
    struct HookPolicy<APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DINDEXBUFFER8_LOCK> : public HookPolicyBase
    {
        static void on_call_finished(const bool&            in_is_success,
                                     IDirect3DIndexBuffer8* in_self,
                                     UINT                   in_offset_to_lock,
                                     UINT                   in_size_to_lock,
                                     BYTE**                 in_data_ptr_ptr,
                                     DWORD                  in_flags);
    };

    template<>
    struct HookPolicy<APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DINDEXBUFFER8_UNLOCK> : public HookPolicyBase
    {
        static const uint32_t n_extra_arguments = 1; /* locked data */

        static void create_extra_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                           IDirect3DIndexBuffer8*               in_self);
        static void on_call_finished      (const bool&                          in_is_success,
                                           IDirect3DIndexBuffer8*               in_self);
    };

    template<>
    struct HookPolicy<APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DSURFACE8_LOCKRECT> : public HookPolicyBase
    {
        static const uint32_t n_extra_arguments = 1; /* locked rectangle */

        static void create_extra_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                           IDirect3DSurface8*                   in_self,
                                           D3DLOCKED_RECT*                      in_locked_rect_ptr,
                                           const RECT*                          in_rect_ptr,
                                           DWORD                                in_flags);
        static void on_call_finished      (const bool&                          in_is_success,
                                           IDirect3DSurface8*                   in_self,
                                           D3DLOCKED_RECT*                      in_locked_rect_ptr,
                                           const RECT*                          in_rect_ptr,
                                           DWORD                                in_flags);
    };

    template<>
    struct HookPolicy<APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DSURFACE8_UNLOCKRECT> : public HookPolicyBase
    {
        static const uint32_t n_extra_arguments = 1; /* locked data */

        static void create_extra_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                           IDirect3DSurface8*                   in_self);
        static void on_call_finished      (const bool&                          in_is_success,
                                           IDirect3DSurface8*                   in_self);
    };

    template<>
    struct HookPolicy<APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DTEXTURE8_LOCKRECT> : public HookPolicyBase
    {
        static const uint32_t n_extra_arguments = 1; /* locked rectangle */

        static void create_extra_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                           IDirect3DTexture8*                   in_self,
                                           UINT                                 in_level,
                                           D3DLOCKED_RECT*                      in_locked_rect_ptr,
                                           const RECT*                          in_rect_ptr,
                                           DWORD                                in_flags);
        static void on_call_finished      (const bool&                          in_is_success,
                                           IDirect3DTexture8*                   in_self,
                                           UINT                                 in_level,
                                           D3DLOCKED_RECT*                      in_locked_rect_ptr,
                                           const RECT*                          in_rect_ptr,
                                           DWORD                                in_flags);
    };

    template<>
    struct HookPolicy<APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DTEXTURE8_UNLOCKRECT> : public HookPolicyBase
    {
        static const uint32_t n_extra_arguments = 1; /* locked data */

        static void create_extra_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                           IDirect3DTexture8*                   in_self,
                                           UINT                                 in_level);
        static void on_call_finished      (const bool&                          in_is_success,
                                           IDirect3DTexture8*                   in_self,
                                           UINT                                 in_level);
    };

    template<>
    struct HookPolicy<APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DVERTEXBUFFER8_LOCK> : public HookPolicyBase
    {
        static void on_call_finished(const bool&             in_is_success,
                                     IDirect3DVertexBuffer8* in_self,
                                     UINT                    in_offset_to_lock,
                                     UINT                    in_size_to_lock,
                                     BYTE**                  in_data_ptr_ptr,
                                     DWORD                   in_flags);
    };

    template<>
    struct HookPolicy<APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DVERTEXBUFFER8_UNLOCK> : public HookPolicyBase
    {
        static const uint32_t n_extra_arguments = 1; /* locked data */

        static void create_extra_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                           IDirect3DVertexBuffer8*              in_self);
        static void on_call_finished      (const bool&                          in_is_success,
                                           IDirect3DVertexBuffer8*              in_self);
    };

    template<>
    struct HookPolicy<APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DVOLUME8_LOCKBOX> : public HookPolicyBase
    {
        static void on_call_finished(const bool&        in_is_success,
                                     IDirect3DVolume8*  in_self,
                                     D3DLOCKED_BOX*     in_locked_box_ptr,
                                     const D3DBOX*      in_box_ptr,
                                     DWORD              in_flags);
    };

    template<>
    struct HookPolicy<APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DVOLUME8_UNLOCKBOX> : public HookPolicyBase
    {
        static const uint32_t n_extra_arguments = 1; /* locked data */

        static void create_extra_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                           IDirect3DVolume8*                    in_self);
        static void on_call_finished      (const bool&                          in_is_success,
                                           IDirect3DVolume8*                    in_self);
    };

    template<>
    struct HookPolicy<APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DVOLUMETEXTURE8_LOCKBOX> : public HookPolicyBase
    {
        static void on_call_finished(const bool&             in_is_success,
                                     IDirect3DVolumeTexture8* in_self,
                                     UINT                     in_level,
                                     D3DLOCKED_BOX*           in_locked_box_ptr,
                                     const D3DBOX*            in_box_ptr,
                                     DWORD                    in_flags);
    };

    template<>
    struct HookPolicy<APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DVOLUMETEXTURE8_UNLOCKBOX> : public HookPolicyBase
    {
        static const uint32_t n_extra_arguments = 1; /* locked data */

        static void create_extra_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                           IDirect3DVolumeTexture8*             in_self,
                                           UINT                                 in_level);
        static void on_call_finished      (const bool&                          in_is_success,
                                           IDirect3DVolumeTexture8*             in_self,
                                           UINT                                 in_level);
    };
}

#endif /* D3D8_HOOK_POLICY_H */
