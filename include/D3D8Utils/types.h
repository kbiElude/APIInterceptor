/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Compile-time description of D3D8 argument types. Shared by the interceptor (what to capture) and the printer (how to
 * decode it).
 */
#ifndef D3D8UTILS_TYPES_H
#define D3D8UTILS_TYPES_H

#include "D3D8/types.h"
#include <type_traits>

namespace D3D8
{
    namespace Utils
    {
        /* How an argument is captured. */
        enum class ArgumentCategory
        {
            ConstStruct,   /* const S*: input structure, captured before the call                       */
            Guid,          /* const GUID&                                                               */
            MutableStruct, /* S*: output structure, captured after the call (input/output: before, too) */
            Object,        /* Pointer to a D3D8 interface                                               */
            ObjectOut,     /* Pointer to a pointer to a D3D8 interface, written by the call             */
            Scalar,        /* Integers, floats, enums and any other pointers                            */
            ScalarOut      /* Pointer to an integer, written by the call                                */
        };

        enum class ObjectType
        {
            None,
            BaseTexture,
            CubeTexture,
            Device,
            Direct3D8,
            IndexBuffer,
            Surface,
            SwapChain,
            Texture,
            VertexBuffer,
            Volume,
            VolumeTexture
        };

        /* D3D8 interfaces. Interface::Unknown means the interface has no entry in the method table. */
        template<typename T>
        struct InterfaceTraits
        {
            static const bool       is_object       = false;
            static const Interface  interface_value = Interface::Unknown;
            static const ObjectType object_type     = ObjectType::None;
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
            static const ValueKind kind            = ValueKind::Plain;
        };

        /* Meaning of a scalar. */
        template<typename T>
        struct ValueKindOf
        {
            static const ValueKind kind = ValueKind::Plain;
        };

        #define D3D8_INTERFACE_TRAITS(type, interface_name, object_type_name) \
            template<> struct InterfaceTraits<type> \
            { \
                static const bool       is_object       = true; \
                static const Interface  interface_value = Interface::interface_name; \
                static const ObjectType object_type     = ObjectType::object_type_name; \
            };

        D3D8_INTERFACE_TRAITS(IDirect3D8,              IDIRECT3D8,              Direct3D8)
        D3D8_INTERFACE_TRAITS(IDirect3DBaseTexture8,   Unknown,                 BaseTexture)
        D3D8_INTERFACE_TRAITS(IDirect3DCubeTexture8,   IDIRECT3DCUBETEXTURE8,   CubeTexture)
        D3D8_INTERFACE_TRAITS(IDirect3DDevice8,        IDIRECT3DDEVICE8,        Device)
        D3D8_INTERFACE_TRAITS(IDirect3DIndexBuffer8,   IDIRECT3DINDEXBUFFER8,   IndexBuffer)
        D3D8_INTERFACE_TRAITS(IDirect3DSurface8,       IDIRECT3DSURFACE8,       Surface)
        D3D8_INTERFACE_TRAITS(IDirect3DSwapChain8,     IDIRECT3DSWAPCHAIN8,     SwapChain)
        D3D8_INTERFACE_TRAITS(IDirect3DTexture8,       IDIRECT3DTEXTURE8,       Texture)
        D3D8_INTERFACE_TRAITS(IDirect3DVertexBuffer8,  IDIRECT3DVERTEXBUFFER8,  VertexBuffer)
        D3D8_INTERFACE_TRAITS(IDirect3DVolume8,        IDIRECT3DVOLUME8,        Volume)
        D3D8_INTERFACE_TRAITS(IDirect3DVolumeTexture8, IDIRECT3DVOLUMETEXTURE8, VolumeTexture)
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
                static const ValueKind kind            = ValueKind::kind_value; \
            };

        D3D8_STRUCT_TRAITS(D3DADAPTER_IDENTIFIER8,        AdapterIdentifier,  false)
        D3D8_STRUCT_TRAITS(D3DBOX,                        Box,                false)
        D3D8_STRUCT_TRAITS(D3DCLIPSTATUS8,                ClipStatus,         false)
        D3D8_STRUCT_TRAITS(D3DDEVICE_CREATION_PARAMETERS, CreationParameters, false)
        D3D8_STRUCT_TRAITS(D3DDISPLAYMODE,                DisplayMode,        false)
        D3D8_STRUCT_TRAITS(D3DGAMMARAMP,                  GammaRamp,          false)
        D3D8_STRUCT_TRAITS(D3DINDEXBUFFER_DESC,           IndexBufferDesc,    false)
        D3D8_STRUCT_TRAITS(D3DLIGHT8,                     Light,              false)
        D3D8_STRUCT_TRAITS(D3DLOCKED_BOX,                 LockedBox,          false)
        D3D8_STRUCT_TRAITS(D3DLOCKED_RECT,                LockedRect,         false)
        D3D8_STRUCT_TRAITS(D3DMATERIAL8,                  Material,           false)
        D3D8_STRUCT_TRAITS(D3DMATRIX,                     Matrix,             false)
        D3D8_STRUCT_TRAITS(D3DPRESENT_PARAMETERS,         PresentParameters,  true)
        D3D8_STRUCT_TRAITS(D3DRASTER_STATUS,              RasterStatus,       false)
        D3D8_STRUCT_TRAITS(D3DSURFACE_DESC,               SurfaceDesc,        false)
        D3D8_STRUCT_TRAITS(D3DVERTEXBUFFER_DESC,          VertexBufferDesc,   false)
        D3D8_STRUCT_TRAITS(D3DVIEWPORT8,                  Viewport,           false)
        D3D8_STRUCT_TRAITS(D3DVOLUME_DESC,                VolumeDesc,         false)
        #undef D3D8_STRUCT_TRAITS

        #define D3D8_VALUE_KIND_OF(type, kind_value) \
            template<> struct ValueKindOf<type> { static const ValueKind kind = ValueKind::kind_value; };

        D3D8_VALUE_KIND_OF(D3DBACKBUFFER_TYPE,       BackBufferType)
        D3D8_VALUE_KIND_OF(D3DCUBEMAP_FACES,         CubeMapFace)
        D3D8_VALUE_KIND_OF(D3DDEVTYPE,               DeviceType)
        D3D8_VALUE_KIND_OF(D3DFORMAT,                Format)
        D3D8_VALUE_KIND_OF(D3DMULTISAMPLE_TYPE,      MultiSampleType)
        D3D8_VALUE_KIND_OF(D3DPOOL,                  Pool)
        D3D8_VALUE_KIND_OF(D3DPRIMITIVETYPE,         PrimitiveType)
        D3D8_VALUE_KIND_OF(D3DRENDERSTATETYPE,       RenderStateType)
        D3D8_VALUE_KIND_OF(D3DRESOURCETYPE,          ResourceType)
        D3D8_VALUE_KIND_OF(D3DSTATEBLOCKTYPE,        StateBlockType)
        D3D8_VALUE_KIND_OF(D3DSWAPEFFECT,            SwapEffect)
        D3D8_VALUE_KIND_OF(D3DTEXTURESTAGESTATETYPE, TextureStageStateType)
        D3D8_VALUE_KIND_OF(D3DTRANSFORMSTATETYPE,    TransformStateType)
        D3D8_VALUE_KIND_OF(int,                      Boolean) /* BOOL */
        D3D8_VALUE_KIND_OF(long,                     Hresult)
        #undef D3D8_VALUE_KIND_OF

        template<typename T>
        struct ArgumentCategoryOf
        {
            static const ArgumentCategory value = ArgumentCategory::Scalar;
        };

        template<typename S>
        struct ArgumentCategoryOf<const S*>
        {
            static const ArgumentCategory value = StructTraits<S>::is_captured ? ArgumentCategory::ConstStruct
                                                                               : ArgumentCategory::Scalar;
        };

        template<typename S>
        struct ArgumentCategoryOf<S*>
        {
            static const ArgumentCategory value = StructTraits<S>::is_captured     ? ArgumentCategory::MutableStruct
                                                : InterfaceTraits<S>::is_object    ? ArgumentCategory::Object
                                                : ScalarOutTraits<S>::is_supported ? ArgumentCategory::ScalarOut
                                                                                   : ArgumentCategory::Scalar;
        };

        template<typename I>
        struct ArgumentCategoryOf<I**>
        {
            static const ArgumentCategory value = InterfaceTraits<I>::is_object ? ArgumentCategory::ObjectOut
                                                                                : ArgumentCategory::Scalar;
        };

        template<>
        struct ArgumentCategoryOf<const GUID&>
        {
            static const ArgumentCategory value = ArgumentCategory::Guid;
        };
    }
}

#endif /* D3D8UTILS_TYPES_H */
