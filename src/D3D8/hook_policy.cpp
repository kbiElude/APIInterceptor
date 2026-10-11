/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "D3D8/argument_factory.h"
#include "D3D8/hook_policy.h"
#include "D3D8/hook_policy_helper.h"
#include "D3D8/lock_tracker.h"
#include "D3D8/vtable_registry.h"
#include <algorithm>

void D3D8::HookPolicy<APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DCUBETEXTURE8_LOCKRECT>::create_extra_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                                                                                               IDirect3DCubeTexture8*               in_self,
                                                                                                               D3DCUBEMAP_FACES                     in_face,
                                                                                                               UINT                                 in_level,
                                                                                                               D3DLOCKED_RECT*                      in_locked_rect_ptr,
                                                                                                               const RECT*                          in_rect_ptr,
                                                                                                               DWORD                                in_flags)
{
    (void) in_self;
    (void) in_face;
    (void) in_level;
    (void) in_locked_rect_ptr;
    (void) in_flags;

    out_arguments_ptr[0] = ArgumentFactory::create_chunk(in_rect_ptr,
                                                         static_cast<uint32_t>(sizeof(RECT) ));
}

void D3D8::HookPolicy<APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DCUBETEXTURE8_LOCKRECT>::on_call_finished(const bool&           in_is_success,
                                                                                                         IDirect3DCubeTexture8* in_self,
                                                                                                         D3DCUBEMAP_FACES       in_face,
                                                                                                         UINT                   in_level,
                                                                                                         D3DLOCKED_RECT*        in_locked_rect_ptr,
                                                                                                         const RECT*            in_rect_ptr,
                                                                                                         DWORD                  in_flags)
{
    if (in_is_success)
    {
        D3DSURFACE_DESC description     = {};
        const auto      get_description = reinterpret_cast<PFN_IDIRECT3DCUBETEXTURE8_GETLEVELDESC>(
                                       VTableRegistry::get_ptr()->get_original_function_ptr(in_self,
                                                                                            VTABLE_INDEX_IDIRECT3DCUBETEXTURE8_GETLEVELDESC) );

        if (get_description != nullptr)
        {
            get_description(in_self,
                            in_level,
                           &description);
        }

        HookPolicyHelper::on_rect_locked(in_self,
                                         HookPolicyHelper::get_cube_face_level_key(in_face,
                                                                                   in_level),
                                         description,
                                         in_locked_rect_ptr,
                                         in_rect_ptr,
                                         in_flags);
    }
}

void D3D8::HookPolicy<APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DCUBETEXTURE8_UNLOCKRECT>::create_extra_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                                                                                                 IDirect3DCubeTexture8*               in_self,
                                                                                                                 D3DCUBEMAP_FACES                     in_face,
                                                                                                                 UINT                                 in_level)
{
    out_arguments_ptr[0] = HookPolicyHelper::create_locked_data_argument(in_self,
                                                                         HookPolicyHelper::get_cube_face_level_key(in_face,
                                                                                                           in_level) );
}

void D3D8::HookPolicy<APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DCUBETEXTURE8_UNLOCKRECT>::on_call_finished(const bool&           in_is_success,
                                                                                                           IDirect3DCubeTexture8* in_self,
                                                                                                           D3DCUBEMAP_FACES       in_face,
                                                                                                           UINT                   in_level)
{
    (void) in_is_success;

    LockTracker::get_ptr()->on_unlocked(in_self,
                                        HookPolicyHelper::get_cube_face_level_key(in_face,
                                                                                  in_level) );
}

void D3D8::HookPolicy<APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_CLEAR>::create_extra_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                                                                                       IDirect3DDevice8*                    in_self,
                                                                                                       DWORD                                in_count,
                                                                                                       const D3DRECT*                       in_rects_ptr,
                                                                                                       DWORD                                in_flags,
                                                                                                       D3DCOLOR                             in_color,
                                                                                                       float                                in_z,
                                                                                                       DWORD                                in_stencil)
{
    constexpr uint32_t MAX_N_RECTS = 4096; /* sanity limit */

    const uint32_t n_rects = std::min<uint32_t>(in_count,
                                                MAX_N_RECTS);

    (void) in_self;
    (void) in_flags;
    (void) in_color;
    (void) in_z;
    (void) in_stencil;

    out_arguments_ptr[0] = ArgumentFactory::create_chunk(in_rects_ptr,
                                                         n_rects * static_cast<uint32_t>(sizeof(D3DRECT) ));
}

void D3D8::HookPolicy<APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_COPYRECTS>::create_extra_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                                                                                           IDirect3DDevice8*                    in_self,
                                                                                                           IDirect3DSurface8*                   in_source_surface_ptr,
                                                                                                           const RECT*                          in_source_rects_ptr,
                                                                                                           UINT                                 in_n_rects,
                                                                                                           IDirect3DSurface8*                   in_destination_surface_ptr,
                                                                                                           const POINT*                         in_destination_points_ptr)
{
    constexpr uint32_t MAX_N_RECTS = 4096; /* sanity limit */

    const uint32_t n_rects = std::min<uint32_t>(in_n_rects,
                                                MAX_N_RECTS);

    (void) in_self;
    (void) in_source_surface_ptr;
    (void) in_destination_surface_ptr;

    out_arguments_ptr[0] = ArgumentFactory::create_chunk(in_source_rects_ptr,
                                                         n_rects * static_cast<uint32_t>(sizeof(RECT) ));
    out_arguments_ptr[1] = ArgumentFactory::create_chunk(in_destination_points_ptr,
                                                         n_rects * static_cast<uint32_t>(sizeof(POINT) ));
}

void D3D8::HookPolicy<APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_CREATEPIXELSHADER>::create_extra_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                                                                                                   IDirect3DDevice8*                    in_self,
                                                                                                                   const DWORD*                         in_function_ptr,
                                                                                                                   DWORD*                               in_handle_ptr)
{
    (void) in_self;
    (void) in_handle_ptr;

    out_arguments_ptr[0] = ArgumentFactory::create_chunk(in_function_ptr,
                                                         HookPolicyHelper::get_n_shader_function_tokens(in_function_ptr) * static_cast<uint32_t>(sizeof(DWORD) ));
}

void D3D8::HookPolicy<APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_CREATEVERTEXSHADER>::create_extra_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                                                                                                    IDirect3DDevice8*                    in_self,
                                                                                                                    const DWORD*                         in_declaration_ptr,
                                                                                                                    const DWORD*                         in_function_ptr,
                                                                                                                    DWORD*                               in_handle_ptr,
                                                                                                                    DWORD                                in_usage)
{
    (void) in_self;
    (void) in_handle_ptr;
    (void) in_usage;

    out_arguments_ptr[0] = ArgumentFactory::create_chunk(in_declaration_ptr,
                                                         HookPolicyHelper::get_n_vertex_declaration_tokens(in_declaration_ptr) * static_cast<uint32_t>(sizeof(DWORD) ));
    out_arguments_ptr[1] = ArgumentFactory::create_chunk(in_function_ptr,
                                                         HookPolicyHelper::get_n_shader_function_tokens(in_function_ptr) * static_cast<uint32_t>(sizeof(DWORD) ));
}

void D3D8::HookPolicy<APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_DRAWINDEXEDPRIMITIVEUP>::create_extra_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                                                                                                         IDirect3DDevice8*                    in_self,
                                                                                                                         D3DPRIMITIVETYPE                     in_primitive_type,
                                                                                                                         UINT                                 in_min_vertex_index,
                                                                                                                         UINT                                 in_n_vertex_indices,
                                                                                                                         UINT                                 in_primitive_count,
                                                                                                                         const void*                          in_index_data_ptr,
                                                                                                                         D3DFORMAT                            in_index_data_format,
                                                                                                                         const void*                          in_vertex_data_ptr,
                                                                                                                         UINT                                 in_vertex_stride)
{
    const uint32_t index_stride = (in_index_data_format == D3DFMT_INDEX32) ? sizeof(uint32_t)
                                                                           : sizeof(uint16_t);

    (void) in_self;

    out_arguments_ptr[0] = ArgumentFactory::create_chunk(in_index_data_ptr,
                                                         HookPolicyHelper::get_n_vertices(in_primitive_type,
                                                                                          in_primitive_count) * index_stride);
    out_arguments_ptr[1] = ArgumentFactory::create_chunk(in_vertex_data_ptr,
                                                         (in_min_vertex_index + in_n_vertex_indices) * in_vertex_stride);
}

void D3D8::HookPolicy<APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_DRAWPRIMITIVEUP>::create_extra_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                                                                                                  IDirect3DDevice8*                    in_self,
                                                                                                                  D3DPRIMITIVETYPE                     in_primitive_type,
                                                                                                                  UINT                                 in_primitive_count,
                                                                                                                  const void*                          in_vertex_data_ptr,
                                                                                                                  UINT                                 in_vertex_stride)
{
    (void) in_self;

    out_arguments_ptr[0] = ArgumentFactory::create_chunk(in_vertex_data_ptr,
                                                         HookPolicyHelper::get_n_vertices(in_primitive_type,
                                                                                          in_primitive_count) * in_vertex_stride);
}

void D3D8::HookPolicy<APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_SETPALETTEENTRIES>::create_extra_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                                                                                                  IDirect3DDevice8*                    in_self,
                                                                                                                  UINT                                 in_palette_number,
                                                                                                                  const PALETTEENTRY*                  in_entries_ptr)
{
    constexpr uint32_t PALETTE_N_ENTRIES = 256; /* a palette always has this many entries */

    (void) in_self;
    (void) in_palette_number;

    out_arguments_ptr[0] = ArgumentFactory::create_chunk(in_entries_ptr,
                                                         PALETTE_N_ENTRIES * static_cast<uint32_t>(sizeof(PALETTEENTRY) ));
}

void D3D8::HookPolicy<APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_SETPIXELSHADERCONSTANT>::create_extra_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                                                                                                         IDirect3DDevice8*                    in_self,
                                                                                                                         DWORD                                in_register,
                                                                                                                         const void*                          in_constant_data_ptr,
                                                                                                                         DWORD                                in_constant_count)
{
    constexpr uint32_t N_FLOATS_PER_CONSTANT = 4; /* a constant is a float4 */

    (void) in_self;
    (void) in_register;

    out_arguments_ptr[0] = ArgumentFactory::create_chunk(in_constant_data_ptr,
                                                         in_constant_count * N_FLOATS_PER_CONSTANT * sizeof(float));
}

void D3D8::HookPolicy<APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_SETVERTEXSHADERCONSTANT>::create_extra_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                                                                                                          IDirect3DDevice8*                    in_self,
                                                                                                                          DWORD                                in_register,
                                                                                                                          const void*                          in_constant_data_ptr,
                                                                                                                          DWORD                                in_constant_count)
{
    constexpr uint32_t N_FLOATS_PER_CONSTANT = 4; /* a constant is a float4 */

    (void) in_self;
    (void) in_register;

    out_arguments_ptr[0] = ArgumentFactory::create_chunk(in_constant_data_ptr,
                                                         in_constant_count * N_FLOATS_PER_CONSTANT * sizeof(float));
}

void D3D8::HookPolicy<APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DINDEXBUFFER8_LOCK>::on_call_finished(const bool&            in_is_success,
                                                                                                     IDirect3DIndexBuffer8* in_self,
                                                                                                     UINT                   in_offset_to_lock,
                                                                                                     UINT                   in_size_to_lock,
                                                                                                     BYTE**                 in_data_ptr_ptr,
                                                                                                     DWORD                  in_flags)
{
    if (in_is_success)
    {
        D3DINDEXBUFFER_DESC description     = {};
        const auto          get_description = reinterpret_cast<PFN_IDIRECT3DINDEXBUFFER8_GETDESC>(
                                           VTableRegistry::get_ptr()->get_original_function_ptr(in_self,
                                                                                                VTABLE_INDEX_IDIRECT3DINDEXBUFFER8_GETDESC) );

        if (get_description != nullptr)
        {
            get_description(in_self,
                           &description);
        }

        HookPolicyHelper::on_buffer_locked(in_self,
                                           description.Size,
                                           in_offset_to_lock,
                                           in_size_to_lock,
                                           in_data_ptr_ptr,
                                           in_flags);
    }
}

void D3D8::HookPolicy<APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DINDEXBUFFER8_UNLOCK>::create_extra_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                                                                                             IDirect3DIndexBuffer8*               in_self)
{
    out_arguments_ptr[0] = HookPolicyHelper::create_locked_data_argument(in_self,
                                                                         0); /* in_level */
}

void D3D8::HookPolicy<APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DINDEXBUFFER8_UNLOCK>::on_call_finished(const bool&            in_is_success,
                                                                                                       IDirect3DIndexBuffer8* in_self)
{
    (void) in_is_success;

    LockTracker::get_ptr()->on_unlocked(in_self,
                                        0); /* in_level */
}

void D3D8::HookPolicy<APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DSURFACE8_LOCKRECT>::create_extra_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                                                                                           IDirect3DSurface8*                   in_self,
                                                                                                           D3DLOCKED_RECT*                      in_locked_rect_ptr,
                                                                                                           const RECT*                          in_rect_ptr,
                                                                                                           DWORD                                in_flags)
{
    (void) in_self;
    (void) in_locked_rect_ptr;
    (void) in_flags;

    out_arguments_ptr[0] = ArgumentFactory::create_chunk(in_rect_ptr,
                                                         static_cast<uint32_t>(sizeof(RECT) ));
}

void D3D8::HookPolicy<APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DSURFACE8_LOCKRECT>::on_call_finished(const bool&        in_is_success,
                                                                                                     IDirect3DSurface8* in_self,
                                                                                                     D3DLOCKED_RECT*    in_locked_rect_ptr,
                                                                                                     const RECT*        in_rect_ptr,
                                                                                                     DWORD              in_flags)
{
    if (in_is_success)
    {
        D3DSURFACE_DESC description     = {};
        const auto      get_description = reinterpret_cast<PFN_IDIRECT3DSURFACE8_GETDESC>(
                                       VTableRegistry::get_ptr()->get_original_function_ptr(in_self,
                                                                                            VTABLE_INDEX_IDIRECT3DSURFACE8_GETDESC) );

        if (get_description != nullptr)
        {
            get_description(in_self,
                           &description);
        }

        HookPolicyHelper::on_rect_locked(in_self,
                                         0, /* in_level */
                                         description,
                                         in_locked_rect_ptr,
                                         in_rect_ptr,
                                         in_flags);
    }
}

void D3D8::HookPolicy<APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DSURFACE8_UNLOCKRECT>::create_extra_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                                                                                             IDirect3DSurface8*                   in_self)
{
    out_arguments_ptr[0] = HookPolicyHelper::create_locked_data_argument(in_self,
                                                                         0); /* in_level */
}

void D3D8::HookPolicy<APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DSURFACE8_UNLOCKRECT>::on_call_finished(const bool&        in_is_success,
                                                                                                       IDirect3DSurface8* in_self)
{
    (void) in_is_success;

    LockTracker::get_ptr()->on_unlocked(in_self,
                                        0); /* in_level */
}

void D3D8::HookPolicy<APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DTEXTURE8_LOCKRECT>::create_extra_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                                                                                           IDirect3DTexture8*                   in_self,
                                                                                                           UINT                                 in_level,
                                                                                                           D3DLOCKED_RECT*                      in_locked_rect_ptr,
                                                                                                           const RECT*                          in_rect_ptr,
                                                                                                           DWORD                                in_flags)
{
    (void) in_self;
    (void) in_level;
    (void) in_locked_rect_ptr;
    (void) in_flags;

    out_arguments_ptr[0] = ArgumentFactory::create_chunk(in_rect_ptr,
                                                         static_cast<uint32_t>(sizeof(RECT) ));
}

void D3D8::HookPolicy<APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DTEXTURE8_LOCKRECT>::on_call_finished(const bool&        in_is_success,
                                                                                                     IDirect3DTexture8* in_self,
                                                                                                     UINT               in_level,
                                                                                                     D3DLOCKED_RECT*    in_locked_rect_ptr,
                                                                                                     const RECT*        in_rect_ptr,
                                                                                                     DWORD              in_flags)
{
    if (in_is_success)
    {
        D3DSURFACE_DESC description     = {};
        const auto      get_description = reinterpret_cast<PFN_IDIRECT3DTEXTURE8_GETLEVELDESC>(
                                       VTableRegistry::get_ptr()->get_original_function_ptr(in_self,
                                                                                            VTABLE_INDEX_IDIRECT3DTEXTURE8_GETLEVELDESC) );

        if (get_description != nullptr)
        {
            get_description(in_self,
                            in_level,
                           &description);
        }

        HookPolicyHelper::on_rect_locked(in_self,
                                         in_level,
                                         description,
                                         in_locked_rect_ptr,
                                         in_rect_ptr,
                                         in_flags);
    }
}

void D3D8::HookPolicy<APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DTEXTURE8_UNLOCKRECT>::create_extra_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                                                                                             IDirect3DTexture8*                   in_self,
                                                                                                             UINT                                 in_level)
{
    out_arguments_ptr[0] = HookPolicyHelper::create_locked_data_argument(in_self,
                                                                         in_level);
}

void D3D8::HookPolicy<APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DTEXTURE8_UNLOCKRECT>::on_call_finished(const bool&        in_is_success,
                                                                                                       IDirect3DTexture8* in_self,
                                                                                                       UINT               in_level)
{
    (void) in_is_success;

    LockTracker::get_ptr()->on_unlocked(in_self,
                                        in_level);
}

void D3D8::HookPolicy<APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DVERTEXBUFFER8_LOCK>::on_call_finished(const bool&             in_is_success,
                                                                                                      IDirect3DVertexBuffer8* in_self,
                                                                                                      UINT                    in_offset_to_lock,
                                                                                                      UINT                    in_size_to_lock,
                                                                                                      BYTE**                  in_data_ptr_ptr,
                                                                                                      DWORD                   in_flags)
{
    if (in_is_success)
    {
        D3DVERTEXBUFFER_DESC description     = {};
        const auto           get_description = reinterpret_cast<PFN_IDIRECT3DVERTEXBUFFER8_GETDESC>(
                                            VTableRegistry::get_ptr()->get_original_function_ptr(in_self,
                                                                                                 VTABLE_INDEX_IDIRECT3DVERTEXBUFFER8_GETDESC) );

        if (get_description != nullptr)
        {
            get_description(in_self,
                           &description);
        }

        HookPolicyHelper::on_buffer_locked(in_self,
                                           description.Size,
                                           in_offset_to_lock,
                                           in_size_to_lock,
                                           in_data_ptr_ptr,
                                           in_flags);
    }
}

void D3D8::HookPolicy<APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DVERTEXBUFFER8_UNLOCK>::create_extra_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                                                                                              IDirect3DVertexBuffer8*              in_self)
{
    out_arguments_ptr[0] = HookPolicyHelper::create_locked_data_argument(in_self,
                                                                         0); /* in_level */
}

void D3D8::HookPolicy<APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DVERTEXBUFFER8_UNLOCK>::on_call_finished(const bool&             in_is_success,
                                                                                                        IDirect3DVertexBuffer8* in_self)
{
    (void) in_is_success;

    LockTracker::get_ptr()->on_unlocked(in_self,
                                        0); /* in_level */
}

void D3D8::HookPolicy<APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DVOLUME8_LOCKBOX>::on_call_finished(const bool&       in_is_success,
                                                                                                  IDirect3DVolume8* in_self,
                                                                                                  D3DLOCKED_BOX*    in_locked_box_ptr,
                                                                                                  const D3DBOX*     in_box_ptr,
                                                                                                  DWORD             in_flags)
{
    if (in_is_success)
    {
        D3DVOLUME_DESC description     = {};
        const auto     get_description = reinterpret_cast<PFN_IDIRECT3DVOLUME8_GETDESC>(
                                      VTableRegistry::get_ptr()->get_original_function_ptr(in_self,
                                                                                           VTABLE_INDEX_IDIRECT3DVOLUME8_GETDESC) );

        if (get_description != nullptr)
        {
            get_description(in_self,
                           &description);
        }

        HookPolicyHelper::on_box_locked(in_self,
                                        0, /* in_level */
                                        description,
                                        in_locked_box_ptr,
                                        in_box_ptr,
                                        in_flags);
    }
}

void D3D8::HookPolicy<APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DVOLUME8_UNLOCKBOX>::create_extra_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                                                                                           IDirect3DVolume8*                    in_self)
{
    out_arguments_ptr[0] = HookPolicyHelper::create_locked_data_argument(in_self,
                                                                         0); /* in_level */
}

void D3D8::HookPolicy<APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DVOLUME8_UNLOCKBOX>::on_call_finished(const bool&       in_is_success,
                                                                                                     IDirect3DVolume8* in_self)
{
    (void) in_is_success;

    LockTracker::get_ptr()->on_unlocked(in_self,
                                        0); /* in_level */
}

void D3D8::HookPolicy<APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DVOLUMETEXTURE8_LOCKBOX>::on_call_finished(const bool&              in_is_success,
                                                                                                          IDirect3DVolumeTexture8* in_self,
                                                                                                          UINT                     in_level,
                                                                                                          D3DLOCKED_BOX*           in_locked_box_ptr,
                                                                                                          const D3DBOX*            in_box_ptr,
                                                                                                          DWORD                    in_flags)
{
    if (in_is_success)
    {
        D3DVOLUME_DESC description     = {};
        const auto     get_description = reinterpret_cast<PFN_IDIRECT3DVOLUMETEXTURE8_GETLEVELDESC>(
                                      VTableRegistry::get_ptr()->get_original_function_ptr(in_self,
                                                                                           VTABLE_INDEX_IDIRECT3DVOLUMETEXTURE8_GETLEVELDESC) );

        if (get_description != nullptr)
        {
            get_description(in_self,
                            in_level,
                           &description);
        }

        HookPolicyHelper::on_box_locked(in_self,
                                        in_level,
                                        description,
                                        in_locked_box_ptr,
                                        in_box_ptr,
                                        in_flags);
    }
}

void D3D8::HookPolicy<APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DVOLUMETEXTURE8_UNLOCKBOX>::create_extra_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                                                                                                  IDirect3DVolumeTexture8*             in_self,
                                                                                                                  UINT                                 in_level)
{
    out_arguments_ptr[0] = HookPolicyHelper::create_locked_data_argument(in_self,
                                                                         in_level);
}

void D3D8::HookPolicy<APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DVOLUMETEXTURE8_UNLOCKBOX>::on_call_finished(const bool&              in_is_success,
                                                                                                            IDirect3DVolumeTexture8* in_self,
                                                                                                            UINT                     in_level)
{
    (void) in_is_success;

    LockTracker::get_ptr()->on_unlocked(in_self,
                                        in_level);
}
