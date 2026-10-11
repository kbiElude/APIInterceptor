/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Minimal Direct3D 8 types (the Windows SDK has none), then the interceptor's helper types. Interfaces are opaque.
 * Types are alphabetical unless a dependency prevents it; the fields of D3D8 structures follow the ABI.
 */
#ifndef D3D8_TYPES_H
#define D3D8_TYPES_H

#include "Common/types.h"
#include <Windows.h>
#include <cstdint>
#include <type_traits>
#include <vector>

namespace D3D8
{
    struct D3DADAPTER_IDENTIFIER8
    {
        char          Driver[512];
        char          Description[512];
        LARGE_INTEGER DriverVersion;
        DWORD         VendorId;
        DWORD         DeviceId;
        DWORD         SubSysId;
        DWORD         Revision;
        GUID          DeviceIdentifier;
        DWORD         WHQLLevel;
    };

    enum D3DBACKBUFFER_TYPE
    {
        D3DBACKBUFFER_TYPE_MONO        = 0,
        D3DBACKBUFFER_TYPE_LEFT        = 1,
        D3DBACKBUFFER_TYPE_RIGHT       = 2,
        D3DBACKBUFFER_TYPE_FORCE_DWORD = 0x7fffffff
    };

    enum D3DBASISTYPE
    {
        D3DBASIS_BEZIER      = 0,
        D3DBASIS_BSPLINE     = 1,
        D3DBASIS_INTERPOLATE = 2,
        D3DBASIS_FORCE_DWORD = 0x7fffffff
    };

    struct D3DBOX
    {
        UINT Left;
        UINT Top;
        UINT Right;
        UINT Bottom;
        UINT Front;
        UINT Back;
    };

    /* Never decoded. */
    struct D3DCAPS8;

    struct D3DCLIPSTATUS8
    {
        DWORD ClipUnion;
        DWORD ClipIntersection;
    };

    typedef DWORD D3DCOLOR;

    struct D3DCOLORVALUE
    {
        float r;
        float g;
        float b;
        float a;
    };

    enum D3DCUBEMAP_FACES
    {
        D3DCUBEMAP_FACE_POSITIVE_X  = 0,
        D3DCUBEMAP_FACE_NEGATIVE_X  = 1,
        D3DCUBEMAP_FACE_POSITIVE_Y  = 2,
        D3DCUBEMAP_FACE_NEGATIVE_Y  = 3,
        D3DCUBEMAP_FACE_POSITIVE_Z  = 4,
        D3DCUBEMAP_FACE_NEGATIVE_Z  = 5,
        D3DCUBEMAP_FACE_FORCE_DWORD = 0xffffffff
    };

    enum D3DDEVTYPE
    {
        D3DDEVTYPE_HAL         = 1,
        D3DDEVTYPE_REF         = 2,
        D3DDEVTYPE_SW          = 3,
        D3DDEVTYPE_FORCE_DWORD = 0xffffffff
    };

    struct D3DDEVICE_CREATION_PARAMETERS
    {
        UINT       AdapterOrdinal;
        D3DDEVTYPE DeviceType;
        HWND       hFocusWindow;
        DWORD      BehaviorFlags;
    };

    enum D3DFORMAT
    {
        D3DFMT_UNKNOWN       = 0,
        D3DFMT_R8G8B8        = 20,
        D3DFMT_A8R8G8B8      = 21,
        D3DFMT_X8R8G8B8      = 22,
        D3DFMT_R5G6B5        = 23,
        D3DFMT_X1R5G5B5      = 24,
        D3DFMT_A1R5G5B5      = 25,
        D3DFMT_A4R4G4B4      = 26,
        D3DFMT_R3G3B2        = 27,
        D3DFMT_A8            = 28,
        D3DFMT_A8R3G3B2      = 29,
        D3DFMT_X4R4G4B4      = 30,
        D3DFMT_A2B10G10R10   = 31,
        D3DFMT_G16R16        = 34,
        D3DFMT_A8P8          = 40,
        D3DFMT_P8            = 41,
        D3DFMT_L8            = 50,
        D3DFMT_A8L8          = 51,
        D3DFMT_A4L4          = 52,
        D3DFMT_V8U8          = 60,
        D3DFMT_L6V5U5        = 61,
        D3DFMT_X8L8V8U8      = 62,
        D3DFMT_Q8W8V8U8      = 63,
        D3DFMT_V16U16        = 64,
        D3DFMT_W11V11U10     = 65,
        D3DFMT_A2W10V10U10   = 67,
        D3DFMT_UYVY          = 0x59565955, /* 'UYVY' */
        D3DFMT_YUY2          = 0x32595559, /* 'YUY2' */
        D3DFMT_DXT1          = 0x31545844, /* 'DXT1' */
        D3DFMT_DXT2          = 0x32545844, /* 'DXT2' */
        D3DFMT_DXT3          = 0x33545844, /* 'DXT3' */
        D3DFMT_DXT4          = 0x34545844, /* 'DXT4' */
        D3DFMT_DXT5          = 0x35545844, /* 'DXT5' */
        D3DFMT_D16_LOCKABLE  = 70,
        D3DFMT_D32           = 71,
        D3DFMT_D15S1         = 73,
        D3DFMT_D24S8         = 75,
        D3DFMT_D16           = 80,
        D3DFMT_D24X8         = 77,
        D3DFMT_D24X4S4       = 79,
        D3DFMT_VERTEXDATA    = 100,
        D3DFMT_INDEX16       = 101,
        D3DFMT_INDEX32       = 102,
        D3DFMT_FORCE_DWORD   = 0xffffffff
    };

    struct D3DDISPLAYMODE
    {
        UINT      Width;
        UINT      Height;
        UINT      RefreshRate;
        D3DFORMAT Format;
    };

    struct D3DGAMMARAMP
    {
        WORD red  [256];
        WORD green[256];
        WORD blue [256];
    };

    enum D3DLIGHTTYPE
    {
        D3DLIGHT_POINT       = 1,
        D3DLIGHT_SPOT        = 2,
        D3DLIGHT_DIRECTIONAL = 3,
        D3DLIGHT_FORCE_DWORD = 0x7fffffff
    };

    struct D3DLOCKED_BOX
    {
        INT   RowPitch;
        INT   SlicePitch;
        void* pBits;
    };

    struct D3DLOCKED_RECT
    {
        INT   Pitch;
        void* pBits;
    };

    struct D3DMATERIAL8
    {
        D3DCOLORVALUE Diffuse;
        D3DCOLORVALUE Ambient;
        D3DCOLORVALUE Specular;
        D3DCOLORVALUE Emissive;
        float         Power;
    };

    struct D3DMATRIX
    {
        float m[4][4];
    };

    enum D3DMULTISAMPLE_TYPE
    {
        D3DMULTISAMPLE_NONE        = 0,
        D3DMULTISAMPLE_2_SAMPLES   = 2,
        D3DMULTISAMPLE_3_SAMPLES   = 3,
        D3DMULTISAMPLE_4_SAMPLES   = 4,
        D3DMULTISAMPLE_5_SAMPLES   = 5,
        D3DMULTISAMPLE_6_SAMPLES   = 6,
        D3DMULTISAMPLE_7_SAMPLES   = 7,
        D3DMULTISAMPLE_8_SAMPLES   = 8,
        D3DMULTISAMPLE_9_SAMPLES   = 9,
        D3DMULTISAMPLE_10_SAMPLES  = 10,
        D3DMULTISAMPLE_11_SAMPLES  = 11,
        D3DMULTISAMPLE_12_SAMPLES  = 12,
        D3DMULTISAMPLE_13_SAMPLES  = 13,
        D3DMULTISAMPLE_14_SAMPLES  = 14,
        D3DMULTISAMPLE_15_SAMPLES  = 15,
        D3DMULTISAMPLE_16_SAMPLES  = 16,
        D3DMULTISAMPLE_FORCE_DWORD = 0x7fffffff
    };

    enum D3DORDERTYPE
    {
        D3DORDER_LINEAR      = 1,
        D3DORDER_QUADRATIC   = 2,
        D3DORDER_CUBIC       = 3,
        D3DORDER_QUINTIC     = 5,
        D3DORDER_FORCE_DWORD = 0x7fffffff
    };

    enum D3DPOOL
    {
        D3DPOOL_DEFAULT     = 0,
        D3DPOOL_MANAGED     = 1,
        D3DPOOL_SYSTEMMEM   = 2,
        D3DPOOL_SCRATCH     = 3,
        D3DPOOL_FORCE_DWORD = 0x7fffffff
    };

    enum D3DPRIMITIVETYPE
    {
        D3DPT_POINTLIST     = 1,
        D3DPT_LINELIST      = 2,
        D3DPT_LINESTRIP     = 3,
        D3DPT_TRIANGLELIST  = 4,
        D3DPT_TRIANGLESTRIP = 5,
        D3DPT_TRIANGLEFAN   = 6,
        D3DPT_FORCE_DWORD   = 0x7fffffff
    };

    struct D3DRASTER_STATUS
    {
        BOOL InVBlank;
        UINT ScanLine;
    };

    struct D3DRECT
    {
        LONG x1;
        LONG y1;
        LONG x2;
        LONG y2;
    };

    struct D3DRECTPATCH_INFO
    {
        UINT          StartVertexOffsetWidth;
        UINT          StartVertexOffsetHeight;
        UINT          Width;
        UINT          Height;
        UINT          Stride;
        D3DBASISTYPE  Basis;
        D3DORDERTYPE  Order;
    };

    enum D3DRENDERSTATETYPE
    {
        D3DRS_ZENABLE                   = 7,
        D3DRS_FILLMODE                  = 8,
        D3DRS_SHADEMODE                 = 9,
        D3DRS_LINEPATTERN               = 10,
        D3DRS_ZWRITEENABLE              = 14,
        D3DRS_ALPHATESTENABLE           = 15,
        D3DRS_LASTPIXEL                 = 16,
        D3DRS_SRCBLEND                  = 19,
        D3DRS_DESTBLEND                 = 20,
        D3DRS_CULLMODE                  = 22,
        D3DRS_ZFUNC                     = 23,
        D3DRS_ALPHAREF                  = 24,
        D3DRS_ALPHAFUNC                 = 25,
        D3DRS_DITHERENABLE              = 26,
        D3DRS_ALPHABLENDENABLE          = 27,
        D3DRS_FOGENABLE                 = 28,
        D3DRS_SPECULARENABLE            = 29,
        D3DRS_ZVISIBLE                  = 30,
        D3DRS_FOGCOLOR                  = 34,
        D3DRS_FOGTABLEMODE              = 35,
        D3DRS_FOGSTART                  = 36,
        D3DRS_FOGEND                    = 37,
        D3DRS_FOGDENSITY                = 38,
        D3DRS_EDGEANTIALIAS             = 40,
        D3DRS_ZBIAS                     = 47,
        D3DRS_RANGEFOGENABLE            = 48,
        D3DRS_STENCILENABLE             = 52,
        D3DRS_STENCILFAIL               = 53,
        D3DRS_STENCILZFAIL              = 54,
        D3DRS_STENCILPASS               = 55,
        D3DRS_STENCILFUNC               = 56,
        D3DRS_STENCILREF                = 57,
        D3DRS_STENCILMASK               = 58,
        D3DRS_STENCILWRITEMASK          = 59,
        D3DRS_TEXTUREFACTOR             = 60,
        D3DRS_WRAP0                     = 128,
        D3DRS_WRAP1                     = 129,
        D3DRS_WRAP2                     = 130,
        D3DRS_WRAP3                     = 131,
        D3DRS_WRAP4                     = 132,
        D3DRS_WRAP5                     = 133,
        D3DRS_WRAP6                     = 134,
        D3DRS_WRAP7                     = 135,
        D3DRS_CLIPPING                  = 136,
        D3DRS_LIGHTING                  = 137,
        D3DRS_AMBIENT                   = 139,
        D3DRS_FOGVERTEXMODE             = 140,
        D3DRS_COLORVERTEX               = 141,
        D3DRS_LOCALVIEWER               = 142,
        D3DRS_NORMALIZENORMALS          = 143,
        D3DRS_DIFFUSEMATERIALSOURCE     = 145,
        D3DRS_SPECULARMATERIALSOURCE    = 146,
        D3DRS_AMBIENTMATERIALSOURCE     = 147,
        D3DRS_EMISSIVEMATERIALSOURCE    = 148,
        D3DRS_VERTEXBLEND               = 151,
        D3DRS_CLIPPLANEENABLE           = 152,
        D3DRS_SOFTWAREVERTEXPROCESSING  = 153,
        D3DRS_POINTSIZE                 = 154,
        D3DRS_POINTSIZE_MIN             = 155,
        D3DRS_POINTSPRITEENABLE         = 156,
        D3DRS_POINTSCALEENABLE          = 157,
        D3DRS_POINTSCALE_A              = 158,
        D3DRS_POINTSCALE_B              = 159,
        D3DRS_POINTSCALE_C              = 160,
        D3DRS_MULTISAMPLEANTIALIAS      = 161,
        D3DRS_MULTISAMPLEMASK           = 162,
        D3DRS_PATCHEDGESTYLE            = 163,
        D3DRS_PATCHSEGMENTS             = 164,
        D3DRS_DEBUGMONITORTOKEN         = 165,
        D3DRS_POINTSIZE_MAX             = 166,
        D3DRS_INDEXEDVERTEXBLENDENABLE  = 167,
        D3DRS_COLORWRITEENABLE          = 168,
        D3DRS_TWEENFACTOR               = 170,
        D3DRS_BLENDOP                   = 171,
        D3DRS_POSITIONORDER             = 172,
        D3DRS_NORMALORDER               = 173,
        D3DRS_FORCE_DWORD               = 0x7fffffff
    };

    enum D3DRESOURCETYPE
    {
        D3DRTYPE_SURFACE       = 1,
        D3DRTYPE_VOLUME        = 2,
        D3DRTYPE_TEXTURE       = 3,
        D3DRTYPE_VOLUMETEXTURE = 4,
        D3DRTYPE_CUBETEXTURE   = 5,
        D3DRTYPE_VERTEXBUFFER  = 6,
        D3DRTYPE_INDEXBUFFER   = 7,
        D3DRTYPE_FORCE_DWORD   = 0x7fffffff
    };

    struct D3DINDEXBUFFER_DESC
    {
        D3DFORMAT       Format;
        D3DRESOURCETYPE Type;
        DWORD           Usage;
        D3DPOOL         Pool;
        UINT            Size;
    };

    enum D3DSTATEBLOCKTYPE
    {
        D3DSBT_ALL         = 1,
        D3DSBT_PIXELSTATE  = 2,
        D3DSBT_VERTEXSTATE = 3,
        D3DSBT_FORCE_DWORD = 0xffffffff
    };

    struct D3DSURFACE_DESC
    {
        D3DFORMAT           Format;
        D3DRESOURCETYPE     Type;
        DWORD               Usage;
        D3DPOOL             Pool;
        UINT                Size;
        D3DMULTISAMPLE_TYPE MultiSampleType;
        UINT                Width;
        UINT                Height;
    };

    enum D3DSWAPEFFECT
    {
        D3DSWAPEFFECT_DISCARD     = 1,
        D3DSWAPEFFECT_FLIP        = 2,
        D3DSWAPEFFECT_COPY        = 3,
        D3DSWAPEFFECT_COPY_VSYNC  = 4,
        D3DSWAPEFFECT_FORCE_DWORD = 0xffffffff
    };

    struct D3DPRESENT_PARAMETERS
    {
        UINT                BackBufferWidth;
        UINT                BackBufferHeight;
        D3DFORMAT           BackBufferFormat;
        UINT                BackBufferCount;
        D3DMULTISAMPLE_TYPE MultiSampleType;
        D3DSWAPEFFECT       SwapEffect;
        HWND                hDeviceWindow;
        BOOL                Windowed;
        BOOL                EnableAutoDepthStencil;
        D3DFORMAT           AutoDepthStencilFormat;
        DWORD               Flags;
        UINT                FullScreen_RefreshRateInHz;
        UINT                FullScreen_PresentationInterval;
    };

    enum D3DTEXTURESTAGESTATETYPE
    {
        D3DTSS_COLOROP               = 1,
        D3DTSS_COLORARG1             = 2,
        D3DTSS_COLORARG2             = 3,
        D3DTSS_ALPHAOP               = 4,
        D3DTSS_ALPHAARG1             = 5,
        D3DTSS_ALPHAARG2             = 6,
        D3DTSS_BUMPENVMAT00          = 7,
        D3DTSS_BUMPENVMAT01          = 8,
        D3DTSS_BUMPENVMAT10          = 9,
        D3DTSS_BUMPENVMAT11          = 10,
        D3DTSS_TEXCOORDINDEX         = 11,
        D3DTSS_ADDRESSU              = 13,
        D3DTSS_ADDRESSV              = 14,
        D3DTSS_BORDERCOLOR           = 15,
        D3DTSS_MAGFILTER             = 16,
        D3DTSS_MINFILTER             = 17,
        D3DTSS_MIPFILTER             = 18,
        D3DTSS_MIPMAPLODBIAS         = 19,
        D3DTSS_MAXMIPLEVEL           = 20,
        D3DTSS_MAXANISOTROPY         = 21,
        D3DTSS_BUMPENVLSCALE         = 22,
        D3DTSS_BUMPENVLOFFSET        = 23,
        D3DTSS_TEXTURETRANSFORMFLAGS = 24,
        D3DTSS_ADDRESSW              = 25,
        D3DTSS_COLORARG0             = 26,
        D3DTSS_ALPHAARG0             = 27,
        D3DTSS_RESULTARG             = 28,
        D3DTSS_FORCE_DWORD           = 0x7fffffff
    };

    enum D3DTRANSFORMSTATETYPE
    {
        D3DTS_VIEW        = 2,
        D3DTS_PROJECTION  = 3,
        D3DTS_TEXTURE0    = 16,
        D3DTS_TEXTURE1    = 17,
        D3DTS_TEXTURE2    = 18,
        D3DTS_TEXTURE3    = 19,
        D3DTS_TEXTURE4    = 20,
        D3DTS_TEXTURE5    = 21,
        D3DTS_TEXTURE6    = 22,
        D3DTS_TEXTURE7    = 23,
        D3DTS_WORLD       = 256,
        D3DTS_WORLD1      = 257,
        D3DTS_WORLD2      = 258,
        D3DTS_WORLD3      = 259,
        D3DTS_FORCE_DWORD = 0x7fffffff
    };

    struct D3DTRIPATCH_INFO
    {
        UINT         StartVertexOffset;
        UINT         NumVertices;
        D3DBASISTYPE Basis;
        D3DORDERTYPE Order;
    };

    struct D3DVECTOR
    {
        float x;
        float y;
        float z;
    };

    struct D3DLIGHT8
    {
        D3DLIGHTTYPE  Type;
        D3DCOLORVALUE Diffuse;
        D3DCOLORVALUE Specular;
        D3DCOLORVALUE Ambient;
        D3DVECTOR     Position;
        D3DVECTOR     Direction;
        float         Range;
        float         Falloff;
        float         Attenuation0;
        float         Attenuation1;
        float         Attenuation2;
        float         Theta;
        float         Phi;
    };

    struct D3DVERTEXBUFFER_DESC
    {
        D3DFORMAT       Format;
        D3DRESOURCETYPE Type;
        DWORD           Usage;
        D3DPOOL         Pool;
        UINT            Size;
        DWORD           FVF;
    };

    struct D3DVIEWPORT8
    {
        DWORD X;
        DWORD Y;
        DWORD Width;
        DWORD Height;
        float MinZ;
        float MaxZ;
    };

    struct D3DVOLUME_DESC
    {
        D3DFORMAT       Format;
        D3DRESOURCETYPE Type;
        DWORD           Usage;
        D3DPOOL         Pool;
        UINT            Size;
        UINT            Width;
        UINT            Height;
        UINT            Depth;
    };

    /* A vtable slot to hook. */
    struct HookEntry
    {
        void*    hook_function_ptr;
        uint32_t vtable_index;
    };

    /* Interfaces (opaque). */
    struct IDirect3D8;
    struct IDirect3DBaseTexture8;
    struct IDirect3DCubeTexture8;
    struct IDirect3DDevice8;
    struct IDirect3DIndexBuffer8;
    struct IDirect3DSurface8;
    struct IDirect3DSwapChain8;
    struct IDirect3DTexture8;
    struct IDirect3DVertexBuffer8;
    struct IDirect3DVolume8;
    struct IDirect3DVolumeTexture8;

    /* Interfaces described by the method table. */
    enum class Interface : uint32_t
    {
        #define D3D8_INTERFACE(INTERFACE_TAG, interface_name) INTERFACE_TAG,
        #define D3D8_METHOD(INTERFACE_TAG, interface_name, METHOD_TAG, method_name, vtable_index, return_type, parameters)
        #include "D3D8/d3d8_methods.inl"
        #undef D3D8_METHOD
        #undef D3D8_INTERFACE

        Count,
        Unknown = Count
    };

    /* A locked region of a resource, as handed out to the application. */
    struct LockRecord
    {
        const uint8_t* data_ptr;
        uint32_t       flags;
        uint32_t       n_bytes;
    };

    struct MethodInfo
    {
        const char*                 full_name_ptr;      /* e.g. IDirect3DDevice8::Present */
        APIInterceptor::APIFunction function;
        const char*                 interface_name_ptr; /* e.g. IDirect3DDevice8          */
        Interface                   interface_type;
        const char*                 method_name_ptr;    /* e.g. Present                   */
        uint32_t                    vtable_index;
    };

    typedef IDirect3D8* (__stdcall* PFNDIRECT3DCREATE8PROC)(UINT);

    /* Function pointer type of each method, e.g. PFN_IDIRECT3DDEVICE8_PRESENT. */
    #define D3D8_METHOD(INTERFACE_TAG, interface_name, METHOD_TAG, method_name, vtable_index, return_type, parameters) \
        typedef return_type (__stdcall *PFN_##INTERFACE_TAG##_##METHOD_TAG) parameters;
    #include "D3D8/d3d8_methods.inl"
    #undef D3D8_METHOD

    /* Meaning of an API call argument; tells the printer how to decode it. */
    enum class ValueKind : uint32_t
    {
        AdapterIdentifier,
        BackBufferType,
        Boolean,
        Box,
        ClearFlags,
        ClipStatus,
        Color,
        CreateFlags,
        CreationParameters,
        CubeMapFace,
        DeviceType,
        DisplayMode,
        Format,
        FvfFlags,
        GammaRamp,
        Guid,
        Hresult,
        IndexBufferDesc,
        Light,
        LightType,
        LockFlags,
        LockedBox,
        LockedRect,
        Material,
        Matrix,
        MultiSampleType,
        Object,
        ObjectOut,
        Plain,
        PointArray,
        Pool,
        PresentParameters,
        PrimitiveType,
        RasterStatus,
        Rect,
        RectArray,
        RenderStateType,
        RenderStateValue,
        ResourceType,
        StateBlockType,
        SurfaceDesc,
        SwapEffect,
        TextureStageStateType,
        TextureStageStateValue,
        TransformStateType,
        UsageFlags,
        VertexBufferDesc,
        Viewport,
        VolumeDesc
    };

    /* Describes an argument or a returned value of a D3D8 method. Follows ValueKind, which it depends on. */
    struct ArgumentInfo
    {
        ValueKind   kind;
        const char* object_type_name_ptr; /* e.g. "Texture"; set for ValueKind::Object and ::ObjectOut only */
    };

    /* DWORD argument which holds flags or a color, or whose meaning depends on another argument. */
    struct ArgumentOverride
    {
        APIInterceptor::APIFunction function;
        ValueKind                   kind;
        uint32_t                    n_argument;
    };

    /* Enums are 32-bit in D3D8. */
    template<typename T, bool is_enum = std::is_enum<T>::value>
    struct ScalarConversion
    {
        typedef T type;
    };

    template<typename T>
    struct ScalarConversion<T, true>
    {
        typedef uint32_t type;
    };

    /* Accessors of the description of a method's signature. */
    struct SignatureEntry
    {
        const std::vector<ArgumentInfo>& (*get_argument_info_vec_func_ptr)();
        ArgumentInfo                     (*get_return_info_func_ptr)();
    };

    /* Vtable slot of each method, e.g. VTABLE_INDEX_IDIRECT3DDEVICE8_PRESENT. */
    enum VtableIndex : uint32_t
    {
        #define D3D8_METHOD(INTERFACE_TAG, interface_name, METHOD_TAG, method_name, vtable_index, return_type, parameters) \
            VTABLE_INDEX_##INTERFACE_TAG##_##METHOD_TAG = vtable_index,
        #include "D3D8/d3d8_methods.inl"
        #undef D3D8_METHOD
    };
    /* Flags. */
    const DWORD D3DCLEAR_TARGET  = 0x00000001;
    const DWORD D3DCLEAR_ZBUFFER = 0x00000002;
    const DWORD D3DCLEAR_STENCIL = 0x00000004;

    const DWORD D3DCREATE_FPU_PRESERVE              = 0x00000002;
    const DWORD D3DCREATE_MULTITHREADED             = 0x00000004;
    const DWORD D3DCREATE_PUREDEVICE                = 0x00000010;
    const DWORD D3DCREATE_SOFTWARE_VERTEXPROCESSING = 0x00000020;
    const DWORD D3DCREATE_HARDWARE_VERTEXPROCESSING = 0x00000040;
    const DWORD D3DCREATE_MIXED_VERTEXPROCESSING     = 0x00000080;

    const DWORD D3DFVF_RESERVED0         = 0x001;
    const DWORD D3DFVF_POSITION_MASK     = 0x00E;
    const DWORD D3DFVF_XYZ               = 0x002;
    const DWORD D3DFVF_XYZRHW            = 0x004;
    const DWORD D3DFVF_XYZB1             = 0x006;
    const DWORD D3DFVF_XYZB2             = 0x008;
    const DWORD D3DFVF_XYZB3             = 0x00a;
    const DWORD D3DFVF_XYZB4             = 0x00c;
    const DWORD D3DFVF_XYZB5             = 0x00e;
    const DWORD D3DFVF_NORMAL            = 0x010;
    const DWORD D3DFVF_PSIZE             = 0x020;
    const DWORD D3DFVF_DIFFUSE           = 0x040;
    const DWORD D3DFVF_SPECULAR          = 0x080;
    const DWORD D3DFVF_TEXCOUNT_MASK     = 0xf00;
    const DWORD D3DFVF_TEXCOUNT_SHIFT    = 8;
    const DWORD D3DFVF_TEX0              = 0x000;
    const DWORD D3DFVF_TEX1              = 0x100;
    const DWORD D3DFVF_TEX2              = 0x200;
    const DWORD D3DFVF_TEX3              = 0x300;
    const DWORD D3DFVF_TEX4              = 0x400;
    const DWORD D3DFVF_TEX5              = 0x500;
    const DWORD D3DFVF_TEX6              = 0x600;
    const DWORD D3DFVF_TEX7              = 0x700;
    const DWORD D3DFVF_TEX8              = 0x800;
    const DWORD D3DFVF_LASTBETA_UBYTE4   = 0x1000;

    const DWORD D3DLOCK_READONLY        = 0x00000010;
    const DWORD D3DLOCK_NOSYSLOCK       = 0x00000800;
    const DWORD D3DLOCK_NOOVERWRITE     = 0x00001000;
    const DWORD D3DLOCK_DISCARD         = 0x00002000;
    const DWORD D3DLOCK_NO_DIRTY_UPDATE = 0x00008000;

    const DWORD D3DPRESENT_INTERVAL_DEFAULT   = 0x00000000;
    const DWORD D3DPRESENT_INTERVAL_ONE       = 0x00000001;
    const DWORD D3DPRESENT_INTERVAL_TWO       = 0x00000002;
    const DWORD D3DPRESENT_INTERVAL_THREE     = 0x00000004;
    const DWORD D3DPRESENT_INTERVAL_FOUR      = 0x00000008;
    const DWORD D3DPRESENT_INTERVAL_IMMEDIATE = 0x80000000;

    const DWORD D3DPRESENTFLAG_LOCKABLE_BACKBUFFER = 0x00000001;

    const DWORD D3DTA_SELECTMASK     = 0x0000000f;
    const DWORD D3DTA_COMPLEMENT     = 0x00000010;
    const DWORD D3DTA_ALPHAREPLICATE = 0x00000020;

    const DWORD D3DTSS_TCI_INDEX_MASK                  = 0x0000ffff;
    const DWORD D3DTSS_TCI_MODE_MASK                   = 0xffff0000;
    const DWORD D3DTSS_TCI_PASSTHRU                    = 0x00000000;
    const DWORD D3DTSS_TCI_CAMERASPACENORMAL           = 0x00010000;
    const DWORD D3DTSS_TCI_CAMERASPACEPOSITION         = 0x00020000;
    const DWORD D3DTSS_TCI_CAMERASPACEREFLECTIONVECTOR = 0x00030000;

    const DWORD D3DTTFF_COUNT_MASK = 0x000000ff;
    const DWORD D3DTTFF_PROJECTED  = 0x00000100;

    const DWORD D3DUSAGE_RENDERTARGET       = 0x00000001;
    const DWORD D3DUSAGE_DEPTHSTENCIL       = 0x00000002;
    const DWORD D3DUSAGE_WRITEONLY          = 0x00000008;
    const DWORD D3DUSAGE_SOFTWAREPROCESSING = 0x00000010;
    const DWORD D3DUSAGE_DONOTCLIP          = 0x00000020;
    const DWORD D3DUSAGE_POINTS             = 0x00000040;
    const DWORD D3DUSAGE_RTPATCHES          = 0x00000080;
    const DWORD D3DUSAGE_NPATCHES           = 0x00000100;
    const DWORD D3DUSAGE_DYNAMIC            = 0x00000200;
}

#endif /* D3D8_TYPES_H */
