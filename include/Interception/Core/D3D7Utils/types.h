/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Compile-time description of D3D7 argument types. Shared by the interceptor (what to capture) and the printer (how to
 * decode it).
 */
#ifndef D3D7UTILS_TYPES_H
#define D3D7UTILS_TYPES_H

#include "Interception/Hooks/D3D7/types.h"
#include <type_traits>

namespace Interception
{
    namespace Core
    {
        namespace D3D7Utils
        {
            /* How an argument is captured (see Hooks/Common/types.h). */
            typedef Interception::Hooks::Common::ArgumentCategory ArgumentCategory;

            enum class ObjectType
            {
                NONE,
                CLIPPER,
                COLOR_CONTROL,
                DEVICE,
                DIRECT3D7,
                DIRECT_DRAW,
                DIRECT_DRAW7,
                GAMMA_CONTROL,
                PALETTE,
                SURFACE,
                VERTEX_BUFFER
            };

            /* D3D7 interfaces. Interface::UNKNOWN means the interface has no entry in the method table. */
            template<typename T>
            struct InterfaceTraits
            {
                static const bool                                 is_object       = false;
                static const Interception::Hooks::D3D7::Interface interface_value = Interception::Hooks::D3D7::Interface::UNKNOWN;
                static const ObjectType                           object_type     = ObjectType::NONE;
            };

            /* The pointed-to type of a pointer argument, without cv-qualifiers. */
            template<typename T>
            using PointeeOf = Interception::Hooks::Common::PointeeOf<T>;

            /* Integers which can be written through a pointer. */
            template<typename T>
            struct ScalarOutTraits
            {
                static const bool is_supported = false;
            };

            /* Structures which are captured when passed by pointer. A structure which is both read and written by a call (the
             * descriptions of a surface are) is captured before the call, too.
             */
            template<typename T>
            struct StructTraits
            {
                static const bool                                  is_captured     = false;
                static const bool                                  is_input_output = false;
                static const Interception::Hooks::D3D7::ValueKind  kind            = Interception::Hooks::D3D7::ValueKind::PLAIN;
            };

            /* Meaning of a scalar. */
            template<typename T>
            struct ValueKindOf
            {
                static const Interception::Hooks::D3D7::ValueKind kind = Interception::Hooks::D3D7::ValueKind::PLAIN;
            };

            #define D3D7_INTERFACE_TRAITS(type, interface_name, object_type_name) \
                template<> struct InterfaceTraits<type> \
                { \
                    static const bool                                 is_object       = true; \
                    static const Interception::Hooks::D3D7::Interface interface_value = Interception::Hooks::D3D7::Interface::interface_name; \
                    static const ObjectType                           object_type     = ObjectType::object_type_name; \
                };

            D3D7_INTERFACE_TRAITS(Interception::Hooks::D3D7::IDirect3D7,               IDIRECT3D7,               DIRECT3D7)
            D3D7_INTERFACE_TRAITS(Interception::Hooks::D3D7::IDirect3DDevice7,         IDIRECT3DDEVICE7,         DEVICE)
            D3D7_INTERFACE_TRAITS(Interception::Hooks::D3D7::IDirect3DVertexBuffer7,   IDIRECT3DVERTEXBUFFER7,   VERTEX_BUFFER)
            D3D7_INTERFACE_TRAITS(Interception::Hooks::D3D7::IDirectDraw,              IDIRECTDRAW,              DIRECT_DRAW)
            D3D7_INTERFACE_TRAITS(Interception::Hooks::D3D7::IDirectDraw7,             IDIRECTDRAW7,             DIRECT_DRAW7)
            D3D7_INTERFACE_TRAITS(Interception::Hooks::D3D7::IDirectDrawClipper,       IDIRECTDRAWCLIPPER,       CLIPPER)
            D3D7_INTERFACE_TRAITS(Interception::Hooks::D3D7::IDirectDrawColorControl,  IDIRECTDRAWCOLORCONTROL,  COLOR_CONTROL)
            D3D7_INTERFACE_TRAITS(Interception::Hooks::D3D7::IDirectDrawGammaControl,  IDIRECTDRAWGAMMACONTROL,  GAMMA_CONTROL)
            D3D7_INTERFACE_TRAITS(Interception::Hooks::D3D7::IDirectDrawPalette,       IDIRECTDRAWPALETTE,       PALETTE)
            D3D7_INTERFACE_TRAITS(Interception::Hooks::D3D7::IDirectDrawSurface7,      IDIRECTDRAWSURFACE7,      SURFACE)
            #undef D3D7_INTERFACE_TRAITS

            #define D3D7_SCALAR_OUT_TRAITS(type) \
                template<> struct ScalarOutTraits<type> { static const bool is_supported = true; };

            D3D7_SCALAR_OUT_TRAITS(int)
            D3D7_SCALAR_OUT_TRAITS(long)
            D3D7_SCALAR_OUT_TRAITS(unsigned int)
            D3D7_SCALAR_OUT_TRAITS(unsigned long)
            #undef D3D7_SCALAR_OUT_TRAITS

            #define D3D7_STRUCT_TRAITS(type, kind_value, is_input_output_value) \
                template<> struct StructTraits<type> \
                { \
                    static const bool                                  is_captured     = true; \
                    static const bool                                  is_input_output = is_input_output_value; \
                    static const Interception::Hooks::D3D7::ValueKind  kind            = Interception::Hooks::D3D7::ValueKind::kind_value; \
                };

            /* A D3DRECT is not here: the rectangles of a Clear are an array (see HookPolicy). */
            D3D7_STRUCT_TRAITS(::POINT,                                                      POINT,              false)
            D3D7_STRUCT_TRAITS(::RECT,                                                       RECT,               false)
            D3D7_STRUCT_TRAITS(Interception::Hooks::D3D7::D3DCLIPPLANE,                      CLIP_PLANE,         false)
            D3D7_STRUCT_TRAITS(Interception::Hooks::D3D7::D3DCLIPSTATUS,                     CLIP_STATUS,        false)
            D3D7_STRUCT_TRAITS(Interception::Hooks::D3D7::D3DDEVICEDESC7,                    DEVICE_DESC,        false)
            D3D7_STRUCT_TRAITS(Interception::Hooks::D3D7::D3DDRAWPRIMITIVESTRIDEDDATA,       STRIDED_DATA,       false)
            D3D7_STRUCT_TRAITS(Interception::Hooks::D3D7::D3DLIGHT7,                         LIGHT,              false)
            D3D7_STRUCT_TRAITS(Interception::Hooks::D3D7::D3DMATERIAL7,                      MATERIAL,           false)
            D3D7_STRUCT_TRAITS(Interception::Hooks::D3D7::D3DMATRIX,                         MATRIX,             false)
            D3D7_STRUCT_TRAITS(Interception::Hooks::D3D7::D3DVERTEXBUFFERDESC,               VERTEX_BUFFER_DESC, true)
            D3D7_STRUCT_TRAITS(Interception::Hooks::D3D7::D3DVIEWPORT7,                      VIEWPORT,           false)
            D3D7_STRUCT_TRAITS(Interception::Hooks::D3D7::DDBLTFX,                           BLT_FX,             false)
            D3D7_STRUCT_TRAITS(Interception::Hooks::D3D7::DDCAPS,                            CAPS,               false)
            D3D7_STRUCT_TRAITS(Interception::Hooks::D3D7::DDCOLORCONTROL,                    COLOR_CONTROL,      false)
            D3D7_STRUCT_TRAITS(Interception::Hooks::D3D7::DDCOLORKEY,                        COLOR_KEY,          false)
            D3D7_STRUCT_TRAITS(Interception::Hooks::D3D7::DDDEVICEIDENTIFIER2,               DEVICE_IDENTIFIER,  false)
            D3D7_STRUCT_TRAITS(Interception::Hooks::D3D7::DDGAMMARAMP,                       GAMMA_RAMP,         false)
            D3D7_STRUCT_TRAITS(Interception::Hooks::D3D7::DDOVERLAYFX,                       OVERLAY_FX,         false)
            D3D7_STRUCT_TRAITS(Interception::Hooks::D3D7::DDPIXELFORMAT,                     PIXEL_FORMAT,       false)
            D3D7_STRUCT_TRAITS(Interception::Hooks::D3D7::DDSCAPS2,                          SURFACE_CAPS,       false)
            D3D7_STRUCT_TRAITS(Interception::Hooks::D3D7::DDSURFACEDESC2,                    SURFACE_DESC,       true)
            #undef D3D7_STRUCT_TRAITS

            #define D3D7_VALUE_KIND_OF(type, kind_value) \
                template<> struct ValueKindOf<type> { static const Interception::Hooks::D3D7::ValueKind kind = Interception::Hooks::D3D7::ValueKind::kind_value; };

            D3D7_VALUE_KIND_OF(Interception::Hooks::D3D7::D3DPRIMITIVETYPE,       PRIMITIVE_TYPE)
            D3D7_VALUE_KIND_OF(Interception::Hooks::D3D7::D3DRENDERSTATETYPE,     RENDER_STATE_TYPE)
            D3D7_VALUE_KIND_OF(Interception::Hooks::D3D7::D3DSTATEBLOCKTYPE,      STATE_BLOCK_TYPE)
            D3D7_VALUE_KIND_OF(Interception::Hooks::D3D7::D3DTEXTURESTAGESTATETYPE, TEXTURE_STAGE_STATE_TYPE)
            D3D7_VALUE_KIND_OF(Interception::Hooks::D3D7::D3DTRANSFORMSTATETYPE,  TRANSFORM_STATE_TYPE)
            D3D7_VALUE_KIND_OF(int,                                                BOOLEAN) /* BOOL */
            D3D7_VALUE_KIND_OF(long,                                               HRESULT)
            #undef D3D7_VALUE_KIND_OF

            template<typename T>
            struct ArgumentCategoryOf
            {
                static const ArgumentCategory value = ArgumentCategory::SCALAR;
            };

            template<typename S>
            struct ArgumentCategoryOf<const S*>
            {
                static const ArgumentCategory value = StructTraits<S>::is_captured ? ArgumentCategory::CONST_STRUCT
                                                                                   : ArgumentCategory::SCALAR;
            };

            template<typename S>
            struct ArgumentCategoryOf<S*>
            {
                static const ArgumentCategory value = StructTraits<S>::is_captured     ? ArgumentCategory::MUTABLE_STRUCT
                                                    : InterfaceTraits<S>::is_object    ? ArgumentCategory::OBJECT
                                                    : ScalarOutTraits<S>::is_supported ? ArgumentCategory::SCALAR_OUT
                                                                                       : ArgumentCategory::SCALAR;
            };

            template<typename I>
            struct ArgumentCategoryOf<I**>
            {
                static const ArgumentCategory value = InterfaceTraits<I>::is_object ? ArgumentCategory::OBJECT_OUT
                                                                                    : ArgumentCategory::SCALAR;
            };

            template<>
            struct ArgumentCategoryOf<void**>
            {
                static const ArgumentCategory value = ArgumentCategory::POINTER_OUT;
            };

            template<>
            struct ArgumentCategoryOf<const GUID&>
            {
                static const ArgumentCategory value = ArgumentCategory::GUID;
            };
        }
    }
}

#endif /* D3D7UTILS_TYPES_H */
