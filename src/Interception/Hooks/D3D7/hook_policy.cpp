/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Interception/Hooks/Common/argument_factory.h"
#include "Interception/Hooks/Common/lock_tracker.h"
#include "Interception/Hooks/D3D7/hook_policy.h"
#include "Interception/Hooks/D3D7/hook_policy_helper.h"
#include "Interception/Core/D3D7Utils/palette_layout.h"
#include "Interception/Core/D3D7Utils/vertex_format.h"
#include <algorithm>

void Interception::Hooks::D3D7::HookPolicy<APIInterceptor::APIFUNCTION_D3D7_DIRECTDRAWCREATEEX>::on_call_finished(const bool& in_is_success,
                                                                                                                  GUID*       in_guid_ptr,
                                                                                                                  void**      in_direct_draw_ptr_ptr,
                                                                                                                  const GUID& in_iid,
                                                                                                                  IUnknown*   in_outer_ptr)
{
    (void) in_guid_ptr;
    (void) in_outer_ptr;

    if (in_is_success                    &&
        in_direct_draw_ptr_ptr != nullptr)
    {
        HookPolicyHelper::patch_object_for_iid(in_iid,
                                              *in_direct_draw_ptr_ptr);
    }
}

void Interception::Hooks::D3D7::HookPolicy<APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAWSURFACE7_BLT>::create_extra_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                                                                                                            IDirectDrawSurface7*                 in_self,
                                                                                                                            const RECT*                          in_destination_rect_ptr,
                                                                                                                            IDirectDrawSurface7*                 in_source_ptr,
                                                                                                                            const RECT*                          in_source_rect_ptr,
                                                                                                                            DWORD                                in_flags,
                                                                                                                            const DDBLTFX*                       in_effects_ptr)
{
    (void) in_destination_rect_ptr;
    (void) in_source_ptr;
    (void) in_source_rect_ptr;
    (void) in_flags;
    (void) in_effects_ptr;

    out_arguments_ptr[0] = Interception::Hooks::Common::ArgumentFactory::create_scalar(HookPolicyHelper::is_primary_surface(in_self) ? 1u
                                                                                                                                      : 0u);
}

void Interception::Hooks::D3D7::HookPolicy<APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAWSURFACE7_BLTFAST>::create_extra_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                                                                                                                IDirectDrawSurface7*                 in_self,
                                                                                                                                DWORD                                in_x,
                                                                                                                                DWORD                                in_y,
                                                                                                                                IDirectDrawSurface7*                 in_source_ptr,
                                                                                                                                const RECT*                          in_source_rect_ptr,
                                                                                                                                DWORD                                in_transfer_flags)
{
    (void) in_x;
    (void) in_y;
    (void) in_source_ptr;
    (void) in_source_rect_ptr;
    (void) in_transfer_flags;

    out_arguments_ptr[0] = Interception::Hooks::Common::ArgumentFactory::create_scalar(HookPolicyHelper::is_primary_surface(in_self) ? 1u
                                                                                                                                      : 0u);
}

void Interception::Hooks::D3D7::HookPolicy<APIInterceptor::APIFUNCTION_D3D7_IDIRECT3DDEVICE7_CLEAR>::create_extra_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                                                                                                            IDirect3DDevice7*                    in_self,
                                                                                                                            DWORD                                in_count,
                                                                                                                            const D3DRECT*                       in_rects_ptr,
                                                                                                                            DWORD                                in_flags,
                                                                                                                            DWORD                                in_color,
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

    out_arguments_ptr[0] = Interception::Hooks::Common::ArgumentFactory::create_chunk(in_rects_ptr,
                                                                                      n_rects * static_cast<uint32_t>(sizeof(D3DRECT) ));
}

void Interception::Hooks::D3D7::HookPolicy<APIInterceptor::APIFUNCTION_D3D7_IDIRECT3DDEVICE7_COMPUTESPHEREVISIBILITY>::create_extra_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                                                                                                                              IDirect3DDevice7*                    in_self,
                                                                                                                                              void*                                in_centers_ptr,
                                                                                                                                              float*                               in_radii_ptr,
                                                                                                                                              DWORD                                in_n_spheres,
                                                                                                                                              DWORD                                in_flags,
                                                                                                                                              DWORD*                               in_results_ptr)
{
    constexpr uint32_t N_BYTES_CENTER = 3 * sizeof(float);
    constexpr uint32_t N_BYTES_RADIUS = sizeof(float);

    (void) in_self;
    (void) in_flags;
    (void) in_results_ptr;

    out_arguments_ptr[0] = Interception::Hooks::Common::ArgumentFactory::create_chunk(in_centers_ptr,
                                                                                      in_n_spheres * N_BYTES_CENTER);
    out_arguments_ptr[1] = Interception::Hooks::Common::ArgumentFactory::create_chunk(in_radii_ptr,
                                                                                      in_n_spheres * N_BYTES_RADIUS);
}

void Interception::Hooks::D3D7::HookPolicy<APIInterceptor::APIFUNCTION_D3D7_IDIRECT3DDEVICE7_DRAWINDEXEDPRIMITIVE>::create_extra_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                                                                                                                          IDirect3DDevice7*                    in_self,
                                                                                                                                          D3DPRIMITIVETYPE                     in_primitive_type,
                                                                                                                                          DWORD                                in_vertex_format,
                                                                                                                                          void*                                in_vertices_ptr,
                                                                                                                                          DWORD                                in_n_vertices,
                                                                                                                                          WORD*                                in_indices_ptr,
                                                                                                                                          DWORD                                in_n_indices,
                                                                                                                                          DWORD                                in_flags)
{
    const uint32_t vertex_n_bytes = Interception::Core::D3D7Utils::VertexFormat::get_n_vertex_bytes(in_vertex_format);

    (void) in_self;
    (void) in_primitive_type;
    (void) in_flags;

    out_arguments_ptr[0] = Interception::Hooks::Common::ArgumentFactory::create_chunk(in_indices_ptr,
                                                                                      in_n_indices * static_cast<uint32_t>(sizeof(WORD) ));
    out_arguments_ptr[1] = Interception::Hooks::Common::ArgumentFactory::create_chunk(in_vertices_ptr,
                                                                                      in_n_vertices * vertex_n_bytes);
}

void Interception::Hooks::D3D7::HookPolicy<APIInterceptor::APIFUNCTION_D3D7_IDIRECT3DDEVICE7_DRAWINDEXEDPRIMITIVESTRIDED>::create_extra_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                                                                                                                                   IDirect3DDevice7*                    in_self,
                                                                                                                                                   D3DPRIMITIVETYPE                     in_primitive_type,
                                                                                                                                                   DWORD                                in_vertex_format,
                                                                                                                                                   const D3DDRAWPRIMITIVESTRIDEDDATA*   in_vertex_array_ptr,
                                                                                                                                                   DWORD                                in_n_vertices,
                                                                                                                                                   WORD*                                in_indices_ptr,
                                                                                                                                                   DWORD                                in_n_indices,
                                                                                                                                                   DWORD                                in_flags)
{
    (void) in_self;
    (void) in_primitive_type;
    (void) in_flags;

    out_arguments_ptr[0] = Interception::Hooks::Common::ArgumentFactory::create_chunk(in_indices_ptr,
                                                                                      in_n_indices * static_cast<uint32_t>(sizeof(WORD) ));

    out_arguments_ptr[1] = HookPolicyHelper::create_strided_data_argument(in_vertex_array_ptr,
                                                                          in_vertex_format,
                                                                          in_n_vertices);
}

void Interception::Hooks::D3D7::HookPolicy<APIInterceptor::APIFUNCTION_D3D7_IDIRECT3DDEVICE7_DRAWINDEXEDPRIMITIVEVB>::create_extra_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                                                                                                                            IDirect3DDevice7*                    in_self,
                                                                                                                                            D3DPRIMITIVETYPE                     in_primitive_type,
                                                                                                                                            IDirect3DVertexBuffer7*              in_vertex_buffer_ptr,
                                                                                                                                            DWORD                                in_start_vertex,
                                                                                                                                            DWORD                                in_n_vertices,
                                                                                                                                            WORD*                                in_indices_ptr,
                                                                                                                                            DWORD                                in_n_indices,
                                                                                                                                            DWORD                                in_flags)
{
    (void) in_self;
    (void) in_primitive_type;
    (void) in_vertex_buffer_ptr;
    (void) in_start_vertex;
    (void) in_n_vertices;
    (void) in_flags;

    out_arguments_ptr[0] = Interception::Hooks::Common::ArgumentFactory::create_chunk(in_indices_ptr,
                                                                                      in_n_indices * static_cast<uint32_t>(sizeof(WORD) ));
}

void Interception::Hooks::D3D7::HookPolicy<APIInterceptor::APIFUNCTION_D3D7_IDIRECT3DDEVICE7_DRAWPRIMITIVE>::create_extra_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                                                                                                                    IDirect3DDevice7*                    in_self,
                                                                                                                                    D3DPRIMITIVETYPE                     in_primitive_type,
                                                                                                                                    DWORD                                in_vertex_format,
                                                                                                                                    void*                                in_vertices_ptr,
                                                                                                                                    DWORD                                in_n_vertices,
                                                                                                                                    DWORD                                in_flags)
{
    const uint32_t vertex_n_bytes = Interception::Core::D3D7Utils::VertexFormat::get_n_vertex_bytes(in_vertex_format);

    (void) in_self;
    (void) in_primitive_type;
    (void) in_flags;

    out_arguments_ptr[0] = Interception::Hooks::Common::ArgumentFactory::create_chunk(in_vertices_ptr,
                                                                                      in_n_vertices * vertex_n_bytes);
}

void Interception::Hooks::D3D7::HookPolicy<APIInterceptor::APIFUNCTION_D3D7_IDIRECT3DDEVICE7_DRAWPRIMITIVESTRIDED>::create_extra_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                                                                                                                           IDirect3DDevice7*                    in_self,
                                                                                                                                           D3DPRIMITIVETYPE                     in_primitive_type,
                                                                                                                                           DWORD                                in_vertex_format,
                                                                                                                                           const D3DDRAWPRIMITIVESTRIDEDDATA*   in_vertex_array_ptr,
                                                                                                                                           DWORD                                in_n_vertices,
                                                                                                                                           DWORD                                in_flags)
{
    (void) in_self;
    (void) in_primitive_type;
    (void) in_flags;

    out_arguments_ptr[0] = HookPolicyHelper::create_strided_data_argument(in_vertex_array_ptr,
                                                                          in_vertex_format,
                                                                          in_n_vertices);
}

void Interception::Hooks::D3D7::HookPolicy<APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAW7_CREATEPALETTE>::create_extra_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                                                                                                                IDirectDraw7*                        in_self,
                                                                                                                                DWORD                                in_flags,
                                                                                                                                const PALETTEENTRY*                  in_entries_ptr,
                                                                                                                                IDirectDrawPalette**                 in_palette_ptr_ptr,
                                                                                                                                IUnknown*                            in_outer_ptr)
{
    const uint32_t n_entries = Interception::Core::D3D7Utils::PaletteLayout::get_n_entries(in_flags);

    (void) in_self;
    (void) in_palette_ptr_ptr;
    (void) in_outer_ptr;

    out_arguments_ptr[0] = Interception::Hooks::Common::ArgumentFactory::create_chunk(in_entries_ptr,
                                                                                      n_entries * static_cast<uint32_t>(sizeof(PALETTEENTRY) ));
}

void Interception::Hooks::D3D7::HookPolicy<APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAWPALETTE_INITIALIZE>::create_extra_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                                                                                                                   IDirectDrawPalette*                  in_self,
                                                                                                                                   IDirectDraw*                         in_direct_draw_ptr,
                                                                                                                                   DWORD                                in_flags,
                                                                                                                                   const PALETTEENTRY*                  in_entries_ptr)
{
    const uint32_t n_entries = Interception::Core::D3D7Utils::PaletteLayout::get_n_entries(in_flags);

    (void) in_self;
    (void) in_direct_draw_ptr;

    out_arguments_ptr[0] = Interception::Hooks::Common::ArgumentFactory::create_chunk(in_entries_ptr,
                                                                                      n_entries * static_cast<uint32_t>(sizeof(PALETTEENTRY) ));
}

void Interception::Hooks::D3D7::HookPolicy<APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAWPALETTE_SETENTRIES>::create_extra_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                                                                                                                   IDirectDrawPalette*                  in_self,
                                                                                                                                   DWORD                                in_flags,
                                                                                                                                   DWORD                                in_first_entry,
                                                                                                                                   DWORD                                in_n_entries,
                                                                                                                                   const PALETTEENTRY*                  in_entries_ptr)
{
    constexpr uint32_t MAX_N_ENTRIES = 256; /* the most a palette has */

    (void) in_self;
    (void) in_flags;
    (void) in_first_entry;

    out_arguments_ptr[0] = Interception::Hooks::Common::ArgumentFactory::create_chunk(in_entries_ptr,
                                                                                      std::min<uint32_t>(in_n_entries,
                                                                                                         MAX_N_ENTRIES) * static_cast<uint32_t>(sizeof(PALETTEENTRY) ));
}

void Interception::Hooks::D3D7::HookPolicy<APIInterceptor::APIFUNCTION_D3D7_IDIRECT3DVERTEXBUFFER7_LOCK>::on_call_finished(const bool&             in_is_success,
                                                                                                                           IDirect3DVertexBuffer7* in_self,
                                                                                                                           DWORD                   in_flags,
                                                                                                                           void**                  in_data_ptr_ptr,
                                                                                                                           DWORD*                  in_size_ptr)
{
    if (in_is_success                &&
        in_data_ptr_ptr != nullptr   &&
       *in_data_ptr_ptr != nullptr)
    {
        HookPolicyHelper::on_vertex_buffer_locked(in_self,
                                                  in_flags,
                                                  in_data_ptr_ptr,
                                                  in_size_ptr);
    }
}

void Interception::Hooks::D3D7::HookPolicy<APIInterceptor::APIFUNCTION_D3D7_IDIRECT3DVERTEXBUFFER7_UNLOCK>::create_extra_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                                                                                                                  IDirect3DVertexBuffer7*              in_self)
{
    out_arguments_ptr[0] = HookPolicyHelper::create_locked_data_argument(in_self,
                                                                         0); /* in_level */
}

void Interception::Hooks::D3D7::HookPolicy<APIInterceptor::APIFUNCTION_D3D7_IDIRECT3DVERTEXBUFFER7_UNLOCK>::on_call_finished(const bool&             in_is_success,
                                                                                                                             IDirect3DVertexBuffer7* in_self)
{
    (void) in_is_success;

    Interception::Hooks::Common::LockTracker::get_ptr()->on_unlocked(in_self,
                                                                     0); /* in_level */
}

void Interception::Hooks::D3D7::HookPolicy<APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAWSURFACE7_LOCK>::on_call_finished(const bool&          in_is_success,
                                                                                                                       IDirectDrawSurface7* in_self,
                                                                                                                       const RECT*          in_rect_ptr,
                                                                                                                       DDSURFACEDESC2*      in_description_ptr,
                                                                                                                       DWORD                in_flags,
                                                                                                                       HANDLE               in_event)
{
    (void) in_event;

    if (in_is_success                &&
        in_description_ptr != nullptr)
    {
        HookPolicyHelper::on_surface_locked(in_self,
                                            in_rect_ptr,
                                            in_description_ptr,
                                            in_flags);
    }
}

void Interception::Hooks::D3D7::HookPolicy<APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAWSURFACE7_UNLOCK>::create_extra_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                                                                                                                IDirectDrawSurface7*                 in_self,
                                                                                                                                const RECT*                          in_rect_ptr)
{
    (void) in_rect_ptr;

    out_arguments_ptr[0] = HookPolicyHelper::create_locked_data_argument(in_self,
                                                                         0); /* in_level */
}

void Interception::Hooks::D3D7::HookPolicy<APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAWSURFACE7_UNLOCK>::on_call_finished(const bool&          in_is_success,
                                                                                                                           IDirectDrawSurface7* in_self,
                                                                                                                           const RECT*          in_rect_ptr)
{
    (void) in_is_success;
    (void) in_rect_ptr;

    Interception::Hooks::Common::LockTracker::get_ptr()->on_unlocked(in_self,
                                                                     0); /* in_level */
}
