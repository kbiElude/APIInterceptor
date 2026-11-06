/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Method-specific additions to the common hook (see common/generic_hook.h): extra arguments holding data which a call refers
 * to, and bookkeeping which follows a call. They follow the method's arguments, and are reported before and after the call.
 */
#ifndef D3D7_HOOK_POLICY_H
#define D3D7_HOOK_POLICY_H

#include "common/api_function_argument.h"
#include "interception/hooks/common/hook_policy_base.h"
#include "interception/hooks/D3D7/hook_policy_helper.h"

namespace Interception
{
    namespace Hooks
    {
        namespace D3D7
        {
            typedef Interception::Hooks::Common::HookPolicyBase HookPolicyBase;

            template<APIInterceptor::APIFunction function>
            struct HookPolicy : public HookPolicyBase
            {
                /* Stub */
            };

            /* The interfaces which a program asks an object for are hooked, so that what a program does with them is known. */
            template<typename ObjectType>
            struct QueryInterfaceHookPolicy : public HookPolicyBase
            {
                static void on_call_finished(const bool& in_is_success,
                                             ObjectType* in_self,
                                             const GUID& in_iid,
                                             void**      in_object_ptr_ptr);
            };

            #define D3D7_QUERY_INTERFACE_POLICY(INTERFACE_TAG, interface_name) \
                template<> \
                struct HookPolicy<APIInterceptor::APIFUNCTION_D3D7_##INTERFACE_TAG##_QUERYINTERFACE> : public QueryInterfaceHookPolicy<interface_name> \
                { \
                    /* Stub */ \
                };

            D3D7_QUERY_INTERFACE_POLICY(IDIRECT3D7,             IDirect3D7)
            D3D7_QUERY_INTERFACE_POLICY(IDIRECT3DDEVICE7,       IDirect3DDevice7)
            D3D7_QUERY_INTERFACE_POLICY(IDIRECT3DVERTEXBUFFER7, IDirect3DVertexBuffer7)
            D3D7_QUERY_INTERFACE_POLICY(IDIRECTDRAW,            IDirectDraw)
            D3D7_QUERY_INTERFACE_POLICY(IDIRECTDRAW7,           IDirectDraw7)
            D3D7_QUERY_INTERFACE_POLICY(IDIRECTDRAWCLIPPER,     IDirectDrawClipper)
            D3D7_QUERY_INTERFACE_POLICY(IDIRECTDRAWCOLORCONTROL, IDirectDrawColorControl)
            D3D7_QUERY_INTERFACE_POLICY(IDIRECTDRAWGAMMACONTROL, IDirectDrawGammaControl)
            D3D7_QUERY_INTERFACE_POLICY(IDIRECTDRAWPALETTE,     IDirectDrawPalette)
            D3D7_QUERY_INTERFACE_POLICY(IDIRECTDRAWSURFACE7,    IDirectDrawSurface7)
            #undef D3D7_QUERY_INTERFACE_POLICY

            /* The object that DirectDrawCreateEx makes is of the interface that was asked for. */
            template<>
            struct HookPolicy<APIInterceptor::APIFUNCTION_D3D7_DIRECTDRAWCREATEEX> : public HookPolicyBase
            {
                static void on_call_finished(const bool& in_is_success,
                                             GUID*       in_guid_ptr,
                                             void**      in_direct_draw_ptr_ptr,
                                             const GUID& in_iid,
                                             IUnknown*   in_outer_ptr);
            };

            /* Whether the blit goes to the primary surface (see APIInterceptor::D3D7_BLT_PRESENTS_ARGUMENT). */
            template<>
            struct HookPolicy<APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAWSURFACE7_BLT> : public HookPolicyBase
            {
                static const uint32_t n_extra_arguments = 1; /* is the destination the primary surface */

                static void create_extra_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                                   IDirectDrawSurface7*                 in_self,
                                                   const RECT*                          in_destination_rect_ptr,
                                                   IDirectDrawSurface7*                 in_source_ptr,
                                                   const RECT*                          in_source_rect_ptr,
                                                   DWORD                                in_flags,
                                                   const DDBLTFX*                       in_effects_ptr);
            };

            template<>
            struct HookPolicy<APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAWSURFACE7_BLTFAST> : public HookPolicyBase
            {
                static const uint32_t n_extra_arguments = 1; /* is the destination the primary surface */

                static void create_extra_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                                   IDirectDrawSurface7*                 in_self,
                                                   DWORD                                in_x,
                                                   DWORD                                in_y,
                                                   IDirectDrawSurface7*                 in_source_ptr,
                                                   const RECT*                          in_source_rect_ptr,
                                                   DWORD                                in_transfer_flags);
            };

            template<>
            struct HookPolicy<APIInterceptor::APIFUNCTION_D3D7_IDIRECT3DDEVICE7_CLEAR> : public HookPolicyBase
            {
                static const uint32_t n_extra_arguments = 1; /* rectangles */

                static void create_extra_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                                   IDirect3DDevice7*                    in_self,
                                                   DWORD                                in_count,
                                                   const D3DRECT*                       in_rects_ptr,
                                                   DWORD                                in_flags,
                                                   DWORD                                in_color,
                                                   float                                in_z,
                                                   DWORD                                in_stencil);
            };

            template<>
            struct HookPolicy<APIInterceptor::APIFUNCTION_D3D7_IDIRECT3DDEVICE7_COMPUTESPHEREVISIBILITY> : public HookPolicyBase
            {
                static const uint32_t n_extra_arguments = 2; /* centers, radii */

                static void create_extra_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                                   IDirect3DDevice7*                    in_self,
                                                   void*                                in_centers_ptr,
                                                   float*                               in_radii_ptr,
                                                   DWORD                                in_n_spheres,
                                                   DWORD                                in_flags,
                                                   DWORD*                               in_results_ptr);
            };

            template<>
            struct HookPolicy<APIInterceptor::APIFUNCTION_D3D7_IDIRECT3DDEVICE7_DRAWINDEXEDPRIMITIVE> : public HookPolicyBase
            {
                static const uint32_t n_extra_arguments = 2; /* indices, vertices */

                static void create_extra_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                                   IDirect3DDevice7*                    in_self,
                                                   D3DPRIMITIVETYPE                     in_primitive_type,
                                                   DWORD                                in_vertex_format,
                                                   void*                                in_vertices_ptr,
                                                   DWORD                                in_n_vertices,
                                                   WORD*                                in_indices_ptr,
                                                   DWORD                                in_n_indices,
                                                   DWORD                                in_flags);
            };

            template<>
            struct HookPolicy<APIInterceptor::APIFUNCTION_D3D7_IDIRECT3DDEVICE7_DRAWINDEXEDPRIMITIVESTRIDED> : public HookPolicyBase
            {
                static const uint32_t n_extra_arguments = 2; /* indices, the arrays of the vertices (see HookPolicyHelper) */

                static void create_extra_arguments(APIInterceptor::APIFunctionArgument*  out_arguments_ptr,
                                                   IDirect3DDevice7*                     in_self,
                                                   D3DPRIMITIVETYPE                      in_primitive_type,
                                                   DWORD                                 in_vertex_format,
                                                   const D3DDRAWPRIMITIVESTRIDEDDATA*    in_vertex_array_ptr,
                                                   DWORD                                 in_n_vertices,
                                                   WORD*                                 in_indices_ptr,
                                                   DWORD                                 in_n_indices,
                                                   DWORD                                 in_flags);
            };

            template<>
            struct HookPolicy<APIInterceptor::APIFUNCTION_D3D7_IDIRECT3DDEVICE7_DRAWINDEXEDPRIMITIVEVB> : public HookPolicyBase
            {
                static const uint32_t n_extra_arguments = 1; /* indices */

                static void create_extra_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                                   IDirect3DDevice7*                    in_self,
                                                   D3DPRIMITIVETYPE                     in_primitive_type,
                                                   IDirect3DVertexBuffer7*              in_vertex_buffer_ptr,
                                                   DWORD                                in_start_vertex,
                                                   DWORD                                in_n_vertices,
                                                   WORD*                                in_indices_ptr,
                                                   DWORD                                in_n_indices,
                                                   DWORD                                in_flags);
            };

            template<>
            struct HookPolicy<APIInterceptor::APIFUNCTION_D3D7_IDIRECT3DDEVICE7_DRAWPRIMITIVE> : public HookPolicyBase
            {
                static const uint32_t n_extra_arguments = 1; /* vertices */

                static void create_extra_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                                   IDirect3DDevice7*                    in_self,
                                                   D3DPRIMITIVETYPE                     in_primitive_type,
                                                   DWORD                                in_vertex_format,
                                                   void*                                in_vertices_ptr,
                                                   DWORD                                in_n_vertices,
                                                   DWORD                                in_flags);
            };

            template<>
            struct HookPolicy<APIInterceptor::APIFUNCTION_D3D7_IDIRECT3DDEVICE7_DRAWPRIMITIVESTRIDED> : public HookPolicyBase
            {
                static const uint32_t n_extra_arguments = 1; /* the arrays of the vertices (see HookPolicyHelper) */

                static void create_extra_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                                   IDirect3DDevice7*                    in_self,
                                                   D3DPRIMITIVETYPE                     in_primitive_type,
                                                   DWORD                                in_vertex_format,
                                                   const D3DDRAWPRIMITIVESTRIDEDDATA*   in_vertex_array_ptr,
                                                   DWORD                                in_n_vertices,
                                                   DWORD                                in_flags);
            };

            template<>
            struct HookPolicy<APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAW7_CREATEPALETTE> : public HookPolicyBase
            {
                static const uint32_t n_extra_arguments = 1; /* entries */

                static void create_extra_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                                   IDirectDraw7*                        in_self,
                                                   DWORD                                in_flags,
                                                   const PALETTEENTRY*                  in_entries_ptr,
                                                   IDirectDrawPalette**                 in_palette_ptr_ptr,
                                                   IUnknown*                            in_outer_ptr);
            };

            template<>
            struct HookPolicy<APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAWPALETTE_INITIALIZE> : public HookPolicyBase
            {
                static const uint32_t n_extra_arguments = 1; /* entries */

                static void create_extra_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                                   IDirectDrawPalette*                  in_self,
                                                   IDirectDraw*                         in_direct_draw_ptr,
                                                   DWORD                                in_flags,
                                                   const PALETTEENTRY*                  in_entries_ptr);
            };

            template<>
            struct HookPolicy<APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAWPALETTE_SETENTRIES> : public HookPolicyBase
            {
                static const uint32_t n_extra_arguments = 1; /* entries */

                static void create_extra_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                                   IDirectDrawPalette*                  in_self,
                                                   DWORD                                in_flags,
                                                   DWORD                                in_first_entry,
                                                   DWORD                                in_n_entries,
                                                   const PALETTEENTRY*                  in_entries_ptr);
            };

            template<>
            struct HookPolicy<APIInterceptor::APIFUNCTION_D3D7_IDIRECT3DVERTEXBUFFER7_LOCK> : public HookPolicyBase
            {
                static void on_call_finished(const bool&             in_is_success,
                                             IDirect3DVertexBuffer7* in_self,
                                             DWORD                   in_flags,
                                             void**                  in_data_ptr_ptr,
                                             DWORD*                  in_size_ptr);
            };

            template<>
            struct HookPolicy<APIInterceptor::APIFUNCTION_D3D7_IDIRECT3DVERTEXBUFFER7_UNLOCK> : public HookPolicyBase
            {
                static const uint32_t n_extra_arguments = 1; /* locked data */

                static void create_extra_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                                   IDirect3DVertexBuffer7*              in_self);
                static void on_call_finished      (const bool&                          in_is_success,
                                                   IDirect3DVertexBuffer7*              in_self);
            };

            template<>
            struct HookPolicy<APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAWSURFACE7_LOCK> : public HookPolicyBase
            {
                static void on_call_finished(const bool&     in_is_success,
                                             IDirectDrawSurface7* in_self,
                                             const RECT*     in_rect_ptr,
                                             DDSURFACEDESC2* in_description_ptr,
                                             DWORD           in_flags,
                                             HANDLE          in_event);
            };

            template<>
            struct HookPolicy<APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAWSURFACE7_UNLOCK> : public HookPolicyBase
            {
                static const uint32_t n_extra_arguments = 1; /* locked data */

                static void create_extra_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                                   IDirectDrawSurface7*                 in_self,
                                                   const RECT*                          in_rect_ptr);
                static void on_call_finished      (const bool&                          in_is_success,
                                                   IDirectDrawSurface7*                 in_self,
                                                   const RECT*                          in_rect_ptr);
            };
        }
    }
}

template<typename ObjectType>
void Interception::Hooks::D3D7::QueryInterfaceHookPolicy<ObjectType>::on_call_finished(const bool& in_is_success,
                                                                                       ObjectType* in_self,
                                                                                       const GUID& in_iid,
                                                                                       void**      in_object_ptr_ptr)
{
    (void) in_self;

    if (in_is_success                &&
        in_object_ptr_ptr != nullptr)
    {
        HookPolicyHelper::patch_object_for_iid(in_iid,
                                              *in_object_ptr_ptr);
    }
}

/* The policies of the functions that take callbacks. */
#include "interception/hooks/D3D7/enum_callback_policy.h"

#endif /* D3D7_HOOK_POLICY_H */
