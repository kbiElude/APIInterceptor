/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Compile-time description of D3D8 argument types. Shared by the interceptor (what to capture) and the printer (how to
 * decode it).
 */
#ifndef D3D8UTILS_TYPES_H
#define D3D8UTILS_TYPES_H

#include "Interception/Hooks/D3D8/types.h"
#include <type_traits>

namespace Interception
{
    namespace Core
    {
        namespace D3D8Utils
        {
            /* How an argument is captured. */
            enum class ArgumentCategory
            {
                CONST_STRUCT,   /* const S*: input structure, captured before the call                       */
                GUID,           /* const GUID&                                                               */
                MUTABLE_STRUCT, /* S*: output structure, captured after the call (input/output: before, too) */
                OBJECT,         /* Pointer to a D3D8 interface                                               */
                OBJECT_OUT,     /* Pointer to a pointer to a D3D8 interface, written by the call             */
                POINTER_OUT,    /* void**: pointer written by the call, e.g. by QueryInterface               */
                SCALAR,         /* Integers, floats, enums and any other pointers                            */
                SCALAR_OUT      /* Pointer to an integer, written by the call                                */
            };

            enum class ObjectType
            {
                NONE,
                BASE_TEXTURE,
                CUBE_TEXTURE,
                DEVICE,
                DIRECT3D8,
                INDEX_BUFFER,
                SURFACE,
                SWAP_CHAIN,
                TEXTURE,
                VERTEX_BUFFER,
                VOLUME,
                VOLUME_TEXTURE
            };

            /* What a D3DPRESENT_PARAMETERS holds, whatever the pointer size of the dumped process (hDeviceWindow is left out). */
            struct PresentParameters
            {
                Interception::Hooks::D3D8::D3DFORMAT           auto_depth_stencil_format         = Interception::Hooks::D3D8::D3DFMT_UNKNOWN;
                uint32_t            back_buffer_count                 = 0;
                Interception::Hooks::D3D8::D3DFORMAT           back_buffer_format                = Interception::Hooks::D3D8::D3DFMT_UNKNOWN;
                uint32_t            back_buffer_height                = 0;
                uint32_t            back_buffer_width                 = 0;
                bool                enable_auto_depth_stencil         = false;
                uint32_t            flags                             = 0;
                uint32_t            full_screen_presentation_interval = 0;
                uint32_t            full_screen_refresh_rate_in_hz    = 0;
                Interception::Hooks::D3D8::D3DMULTISAMPLE_TYPE multi_sample_type                 = Interception::Hooks::D3D8::D3DMULTISAMPLE_NONE;
                Interception::Hooks::D3D8::D3DSWAPEFFECT       swap_effect                       = Interception::Hooks::D3D8::D3DSWAPEFFECT_DISCARD;
                bool                windowed                          = false;
            };

            /* D3D8 interfaces. Interface::UNKNOWN means the interface has no entry in the method table. */
            template<typename T>
            struct InterfaceTraits
            {
                static const bool       is_object       = false;
                static const Interception::Hooks::D3D8::Interface  interface_value = Interception::Hooks::D3D8::Interface::UNKNOWN;
                static const ObjectType object_type     = ObjectType::NONE;
            };

            /* The pointed-to type of a pointer argument, without cv-qualifiers. */
            template<typename T>
            struct PointeeOf
            {
                typedef typename std::remove_cv<typename std::remove_pointer<T>::type>::type type;
            };

            /* Integers which can be written through a pointer. */
            template<typename T>
            struct ScalarOutTraits
            {
                static const bool is_supported = false;
            };

            /* Structures which are captured when passed by pointer. */
            template<typename T>
            struct StructTraits
            {
                static const bool      is_captured     = false;
                static const bool      is_input_output = false;
                static const Interception::Hooks::D3D8::ValueKind kind            = Interception::Hooks::D3D8::ValueKind::PLAIN;
            };

            /* Meaning of a scalar. */
            template<typename T>
            struct ValueKindOf
            {
                static const Interception::Hooks::D3D8::ValueKind kind = Interception::Hooks::D3D8::ValueKind::PLAIN;
            };

            #define D3D8_INTERFACE_TRAITS(type, interface_name, object_type_name) \
                template<> struct InterfaceTraits<type> \
                { \
                    static const bool       is_object       = true; \
                    static const Interception::Hooks::D3D8::Interface  interface_value = Interception::Hooks::D3D8::Interface::interface_name; \
                    static const ObjectType object_type     = ObjectType::object_type_name; \
                };

            D3D8_INTERFACE_TRAITS(Interception::Hooks::D3D8::IDirect3D8,              IDIRECT3D8,              DIRECT3D8)
            D3D8_INTERFACE_TRAITS(Interception::Hooks::D3D8::IDirect3DBaseTexture8,   UNKNOWN,                 BASE_TEXTURE)
            D3D8_INTERFACE_TRAITS(Interception::Hooks::D3D8::IDirect3DCubeTexture8,   IDIRECT3DCUBETEXTURE8,   CUBE_TEXTURE)
            D3D8_INTERFACE_TRAITS(Interception::Hooks::D3D8::IDirect3DDevice8,        IDIRECT3DDEVICE8,        DEVICE)
            D3D8_INTERFACE_TRAITS(Interception::Hooks::D3D8::IDirect3DIndexBuffer8,   IDIRECT3DINDEXBUFFER8,   INDEX_BUFFER)
            D3D8_INTERFACE_TRAITS(Interception::Hooks::D3D8::IDirect3DSurface8,       IDIRECT3DSURFACE8,       SURFACE)
            D3D8_INTERFACE_TRAITS(Interception::Hooks::D3D8::IDirect3DSwapChain8,     IDIRECT3DSWAPCHAIN8,     SWAP_CHAIN)
            D3D8_INTERFACE_TRAITS(Interception::Hooks::D3D8::IDirect3DTexture8,       IDIRECT3DTEXTURE8,       TEXTURE)
            D3D8_INTERFACE_TRAITS(Interception::Hooks::D3D8::IDirect3DVertexBuffer8,  IDIRECT3DVERTEXBUFFER8,  VERTEX_BUFFER)
            D3D8_INTERFACE_TRAITS(Interception::Hooks::D3D8::IDirect3DVolume8,        IDIRECT3DVOLUME8,        VOLUME)
            D3D8_INTERFACE_TRAITS(Interception::Hooks::D3D8::IDirect3DVolumeTexture8, IDIRECT3DVOLUMETEXTURE8, VOLUME_TEXTURE)
            #undef D3D8_INTERFACE_TRAITS

            #define D3D8_SCALAR_OUT_TRAITS(type) \
                template<> struct ScalarOutTraits<type> { static const bool is_supported = true; };

            D3D8_SCALAR_OUT_TRAITS(int)
            D3D8_SCALAR_OUT_TRAITS(unsigned int)
            D3D8_SCALAR_OUT_TRAITS(unsigned long)
            #undef D3D8_SCALAR_OUT_TRAITS

            #define D3D8_STRUCT_TRAITS(type, kind_value, is_input_output_value) \
                template<> struct StructTraits<type> \
                { \
                    static const bool      is_captured     = true; \
                    static const bool      is_input_output = is_input_output_value; \
                    static const Interception::Hooks::D3D8::ValueKind kind            = Interception::Hooks::D3D8::ValueKind::kind_value; \
                };

            D3D8_STRUCT_TRAITS(Interception::Hooks::D3D8::D3DADAPTER_IDENTIFIER8,        ADAPTER_IDENTIFIER,  false)
            D3D8_STRUCT_TRAITS(Interception::Hooks::D3D8::D3DBOX,                        BOX,                 false)
            D3D8_STRUCT_TRAITS(Interception::Hooks::D3D8::D3DCAPS8,                      CAPS,                false)
            D3D8_STRUCT_TRAITS(Interception::Hooks::D3D8::D3DCLIPSTATUS8,                CLIP_STATUS,         false)
            D3D8_STRUCT_TRAITS(Interception::Hooks::D3D8::D3DDEVICE_CREATION_PARAMETERS, CREATION_PARAMETERS, false)
            D3D8_STRUCT_TRAITS(Interception::Hooks::D3D8::D3DDISPLAYMODE,                DISPLAY_MODE,        false)
            D3D8_STRUCT_TRAITS(Interception::Hooks::D3D8::D3DGAMMARAMP,                  GAMMA_RAMP,          false)
            D3D8_STRUCT_TRAITS(Interception::Hooks::D3D8::D3DINDEXBUFFER_DESC,           INDEX_BUFFER_DESC,   false)
            D3D8_STRUCT_TRAITS(Interception::Hooks::D3D8::D3DLIGHT8,                     LIGHT,               false)
            D3D8_STRUCT_TRAITS(Interception::Hooks::D3D8::D3DLOCKED_BOX,                 LOCKED_BOX,          false)
            D3D8_STRUCT_TRAITS(Interception::Hooks::D3D8::D3DLOCKED_RECT,                LOCKED_RECT,         false)
            D3D8_STRUCT_TRAITS(Interception::Hooks::D3D8::D3DMATERIAL8,                  MATERIAL,            false)
            D3D8_STRUCT_TRAITS(Interception::Hooks::D3D8::D3DMATRIX,                     MATRIX,              false)
            D3D8_STRUCT_TRAITS(Interception::Hooks::D3D8::D3DPRESENT_PARAMETERS,         PRESENT_PARAMETERS,  true)
            D3D8_STRUCT_TRAITS(Interception::Hooks::D3D8::D3DRASTER_STATUS,              RASTER_STATUS,       false)
            D3D8_STRUCT_TRAITS(Interception::Hooks::D3D8::D3DRECTPATCH_INFO,             RECT_PATCH_INFO,     false)
            D3D8_STRUCT_TRAITS(Interception::Hooks::D3D8::D3DSURFACE_DESC,               SURFACE_DESC,        false)
            D3D8_STRUCT_TRAITS(Interception::Hooks::D3D8::D3DTRIPATCH_INFO,              TRI_PATCH_INFO,      false)
            D3D8_STRUCT_TRAITS(Interception::Hooks::D3D8::D3DVERTEXBUFFER_DESC,          VERTEX_BUFFER_DESC,  false)
            D3D8_STRUCT_TRAITS(Interception::Hooks::D3D8::D3DVIEWPORT8,                  VIEWPORT,            false)
            D3D8_STRUCT_TRAITS(Interception::Hooks::D3D8::D3DVOLUME_DESC,                VOLUME_DESC,         false)
            #undef D3D8_STRUCT_TRAITS

            #define D3D8_VALUE_KIND_OF(type, kind_value) \
                template<> struct ValueKindOf<type> { static const Interception::Hooks::D3D8::ValueKind kind = Interception::Hooks::D3D8::ValueKind::kind_value; };

            D3D8_VALUE_KIND_OF(Interception::Hooks::D3D8::D3DBACKBUFFER_TYPE,       BACK_BUFFER_TYPE)
            D3D8_VALUE_KIND_OF(Interception::Hooks::D3D8::D3DCUBEMAP_FACES,         CUBE_MAP_FACE)
            D3D8_VALUE_KIND_OF(Interception::Hooks::D3D8::D3DDEVTYPE,               DEVICE_TYPE)
            D3D8_VALUE_KIND_OF(Interception::Hooks::D3D8::D3DFORMAT,                FORMAT)
            D3D8_VALUE_KIND_OF(Interception::Hooks::D3D8::D3DMULTISAMPLE_TYPE,      MULTI_SAMPLE_TYPE)
            D3D8_VALUE_KIND_OF(Interception::Hooks::D3D8::D3DPOOL,                  POOL)
            D3D8_VALUE_KIND_OF(Interception::Hooks::D3D8::D3DPRIMITIVETYPE,         PRIMITIVE_TYPE)
            D3D8_VALUE_KIND_OF(Interception::Hooks::D3D8::D3DRENDERSTATETYPE,       RENDER_STATE_TYPE)
            D3D8_VALUE_KIND_OF(Interception::Hooks::D3D8::D3DRESOURCETYPE,          RESOURCE_TYPE)
            D3D8_VALUE_KIND_OF(Interception::Hooks::D3D8::D3DSTATEBLOCKTYPE,        STATE_BLOCK_TYPE)
            D3D8_VALUE_KIND_OF(Interception::Hooks::D3D8::D3DSWAPEFFECT,            SWAP_EFFECT)
            D3D8_VALUE_KIND_OF(Interception::Hooks::D3D8::D3DTEXTURESTAGESTATETYPE, TEXTURE_STAGE_STATE_TYPE)
            D3D8_VALUE_KIND_OF(Interception::Hooks::D3D8::D3DTRANSFORMSTATETYPE,    TRANSFORM_STATE_TYPE)
            D3D8_VALUE_KIND_OF(int,                      BOOLEAN) /* BOOL */
            D3D8_VALUE_KIND_OF(long,                     HRESULT)
            #undef D3D8_VALUE_KIND_OF

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

#endif /* D3D8UTILS_TYPES_H */
