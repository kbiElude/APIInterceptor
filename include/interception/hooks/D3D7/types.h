/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Minimal DirectDraw 7 and Direct3D 7 types (the Windows SDK has none), then the interceptor's helper types. Interfaces are
 * opaque. The layouts are those of the 32-bit headers of DirectX 7: DirectDraw exists for 32-bit programs of that time.
 * Types are alphabetical unless a dependency prevents it; the fields of the structures follow the ABI.
 */
#ifndef D3D7_TYPES_H
#define D3D7_TYPES_H

#include "common/types.h"
#include "interception/core/common/signature_info.h"
#include "interception/hooks/common/types.h"
#include <Windows.h>
#include <cstdint>

namespace Interception
{
    namespace Hooks
    {
        namespace D3D7
        {
            struct D3DCLIPPLANE
            {
                float dvPlaneEquation[4];
            };

            struct D3DCLIPSTATUS
            {
                DWORD dwFlags;
                DWORD dwStatus;
                float minx;
                float maxx;
                float miny;
                float maxy;
                float minz;
                float maxz;
            };

            struct D3DCOLORVALUE
            {
                float r;
                float g;
                float b;
                float a;
            };

            struct D3DLIGHT7
            {
                DWORD         dltType;
                D3DCOLORVALUE dcvDiffuse;
                D3DCOLORVALUE dcvSpecular;
                D3DCOLORVALUE dcvAmbient;
                float         dvPosition[3];
                float         dvDirection[3];
                float         dvRange;
                float         dvFalloff;
                float         dvAttenuation0;
                float         dvAttenuation1;
                float         dvAttenuation2;
                float         dvTheta;
                float         dvPhi;
            };

            struct D3DMATERIAL7
            {
                D3DCOLORVALUE dcvDiffuse;
                D3DCOLORVALUE dcvAmbient;
                D3DCOLORVALUE dcvSpecular;
                D3DCOLORVALUE dcvEmissive;
                float         dvPower;
            };

            struct D3DMATRIX
            {
                float m[4][4];
            };

            struct D3DPRIMCAPS
            {
                DWORD dwSize;
                DWORD dwMiscCaps;
                DWORD dwRasterCaps;
                DWORD dwZCmpCaps;
                DWORD dwSrcBlendCaps;
                DWORD dwDestBlendCaps;
                DWORD dwAlphaCmpCaps;
                DWORD dwShadeCaps;
                DWORD dwTextureCaps;
                DWORD dwTextureFilterCaps;
                DWORD dwTextureBlendCaps;
                DWORD dwTextureAddressCaps;
                DWORD dwStippleWidth;
                DWORD dwStippleHeight;
            };

            struct D3DDEVICEDESC7
            {
                DWORD       dwDevCaps;
                D3DPRIMCAPS dpcLineCaps;
                D3DPRIMCAPS dpcTriCaps;
                DWORD       dwDeviceRenderBitDepth;
                DWORD       dwDeviceZBufferBitDepth;
                DWORD       dwMinTextureWidth;
                DWORD       dwMinTextureHeight;
                DWORD       dwMaxTextureWidth;
                DWORD       dwMaxTextureHeight;
                DWORD       dwMaxTextureRepeat;
                DWORD       dwMaxTextureAspectRatio;
                DWORD       dwMaxAnisotropy;
                float       dvGuardBandLeft;
                float       dvGuardBandTop;
                float       dvGuardBandRight;
                float       dvGuardBandBottom;
                float       dvExtentsAdjust;
                DWORD       dwStencilCaps;
                DWORD       dwFVFCaps;
                DWORD       dwTextureOpCaps;
                WORD        wMaxTextureBlendStages;
                WORD        wMaxSimultaneousTextures;
                DWORD       dwMaxActiveLights;
                float       dvMaxVertexW;
                GUID        deviceGUID;
                WORD        wMaxUserClipPlanes;
                WORD        wMaxVertexBlendMatrices;
                DWORD       dwVertexProcessingCaps;
                DWORD       dwReserved1;
                DWORD       dwReserved2;
                DWORD       dwReserved3;
                DWORD       dwReserved4;
            };

            /* A source of the vertices of a strided draw: the first element, and the distance to the next one. */
            struct D3DDP_PTRSTRIDE
            {
                void* lpvData;
                DWORD dwStride;
            };

            struct D3DDRAWPRIMITIVESTRIDEDDATA
            {
                D3DDP_PTRSTRIDE position;
                D3DDP_PTRSTRIDE normal;
                D3DDP_PTRSTRIDE diffuse;
                D3DDP_PTRSTRIDE specular;
                D3DDP_PTRSTRIDE textureCoords[8];
            };

            struct D3DRECT
            {
                LONG x1;
                LONG y1;
                LONG x2;
                LONG y2;
            };

            struct D3DVERTEXBUFFERDESC
            {
                DWORD dwSize;
                DWORD dwCaps;
                DWORD dwFVF;
                DWORD dwNumVertices;
            };

            struct D3DVIEWPORT7
            {
                DWORD dwX;
                DWORD dwY;
                DWORD dwWidth;
                DWORD dwHeight;
                float dvMinZ;
                float dvMaxZ;
            };

            struct DDCOLORCONTROL
            {
                DWORD dwSize;
                DWORD dwFlags;
                LONG  lBrightness;
                LONG  lContrast;
                LONG  lHue;
                LONG  lSaturation;
                LONG  lSharpness;
                LONG  lGamma;
                LONG  lColorEnable;
                DWORD dwReserved1;
            };

            struct DDCOLORKEY
            {
                DWORD dwColorSpaceLowValue;
                DWORD dwColorSpaceHighValue;
            };

            /* The unions of the original are flattened to their first member; pointers to surfaces are stored as DWORDs. */
            struct DDBLTFX
            {
                DWORD      dwSize;
                DWORD      dwDDFX;
                DWORD      dwROP;
                DWORD      dwDDROP;
                DWORD      dwRotationAngle;
                DWORD      dwZBufferOpCode;
                DWORD      dwZBufferLow;
                DWORD      dwZBufferHigh;
                DWORD      dwZBufferBaseDest;
                DWORD      dwZDestConstBitDepth;
                DWORD      dwZDestConst;
                DWORD      dwZSrcConstBitDepth;
                DWORD      dwZSrcConst;
                DWORD      dwAlphaEdgeBlendBitDepth;
                DWORD      dwAlphaEdgeBlend;
                DWORD      dwReserved;
                DWORD      dwAlphaDestConstBitDepth;
                DWORD      dwAlphaDestConst;
                DWORD      dwAlphaSrcConstBitDepth;
                DWORD      dwAlphaSrcConst;
                DWORD      dwFillColor;
                DDCOLORKEY ddckDestColorkey;
                DDCOLORKEY ddckSrcColorkey;
            };

            struct DDSCAPS2
            {
                DWORD dwCaps;
                DWORD dwCaps2;
                DWORD dwCaps3;
                DWORD dwCaps4;
            };

            struct DDCAPS
            {
                DWORD    dwSize;
                DWORD    dwCaps;
                DWORD    dwCaps2;
                DWORD    dwCKeyCaps;
                DWORD    dwFXCaps;
                DWORD    dwFXAlphaCaps;
                DWORD    dwPalCaps;
                DWORD    dwSVCaps;
                DWORD    dwAlphaBltConstBitDepths;
                DWORD    dwAlphaBltPixelBitDepths;
                DWORD    dwAlphaBltSurfaceBitDepths;
                DWORD    dwAlphaOverlayConstBitDepths;
                DWORD    dwAlphaOverlayPixelBitDepths;
                DWORD    dwAlphaOverlaySurfaceBitDepths;
                DWORD    dwZBufferBitDepths;
                DWORD    dwVidMemTotal;
                DWORD    dwVidMemFree;
                DWORD    dwMaxVisibleOverlays;
                DWORD    dwCurrVisibleOverlays;
                DWORD    dwNumFourCCCodes;
                DWORD    dwAlignBoundarySrc;
                DWORD    dwAlignSizeSrc;
                DWORD    dwAlignBoundaryDest;
                DWORD    dwAlignSizeDest;
                DWORD    dwAlignStrideAlign;
                DWORD    dwRops[8];
                DWORD    ddsOldCaps;
                DWORD    dwMinOverlayStretch;
                DWORD    dwMaxOverlayStretch;
                DWORD    dwMinLiveVideoStretch;
                DWORD    dwMaxLiveVideoStretch;
                DWORD    dwMinHwCodecStretch;
                DWORD    dwMaxHwCodecStretch;
                DWORD    dwReserved1;
                DWORD    dwReserved2;
                DWORD    dwReserved3;
                DWORD    dwSVBCaps;
                DWORD    dwSVBCKeyCaps;
                DWORD    dwSVBFXCaps;
                DWORD    dwSVBRops[8];
                DWORD    dwVSBCaps;
                DWORD    dwVSBCKeyCaps;
                DWORD    dwVSBFXCaps;
                DWORD    dwVSBRops[8];
                DWORD    dwSSBCaps;
                DWORD    dwSSBCKeyCaps;
                DWORD    dwSSBFXCaps;
                DWORD    dwSSBRops[8];
                DWORD    dwMaxVideoPorts;
                DWORD    dwCurrVideoPorts;
                DWORD    dwSVBCaps2;
                DWORD    dwNLVBCaps;
                DWORD    dwNLVBCaps2;
                DWORD    dwNLVBCKeyCaps;
                DWORD    dwNLVBFXCaps;
                DWORD    dwNLVBRops[8];
                DDSCAPS2 ddsCaps;
            };

            struct DDDEVICEIDENTIFIER2
            {
                char          szDriver[512];
                char          szDescription[512];
                LARGE_INTEGER liDriverVersion;
                DWORD         dwVendorId;
                DWORD         dwDeviceId;
                DWORD         dwSubSysId;
                DWORD         dwRevision;
                GUID          guidDeviceIdentifier;
                DWORD         dwWHQLLevel;
            };

            struct DDGAMMARAMP
            {
                WORD red[256];
                WORD green[256];
                WORD blue[256];
            };

            struct DDOVERLAYFX
            {
                DWORD      dwSize;
                DWORD      dwAlphaEdgeBlendBitDepth;
                DWORD      dwAlphaEdgeBlend;
                DWORD      dwReserved;
                DWORD      dwAlphaDestConstBitDepth;
                DWORD      dwAlphaDestConst;
                DWORD      dwAlphaSrcConstBitDepth;
                DWORD      dwAlphaSrcConst;
                DDCOLORKEY dckDestColorkey;
                DDCOLORKEY dckSrcColorkey;
                DWORD      dwDDFX;
                DWORD      dwFlags;
            };

            struct DDPIXELFORMAT
            {
                DWORD dwSize;
                DWORD dwFlags;
                DWORD dwFourCC;
                DWORD dwRGBBitCount;
                DWORD dwRBitMask;
                DWORD dwGBitMask;
                DWORD dwBBitMask;
                DWORD dwRGBAlphaBitMask;
            };

            /* The unions of the original are flattened to their first member. */
            struct DDSURFACEDESC2
            {
                DWORD         dwSize;
                DWORD         dwFlags;
                DWORD         dwHeight;
                DWORD         dwWidth;
                LONG          lPitch;
                DWORD         dwBackBufferCount;
                DWORD         dwMipMapCount;
                DWORD         dwAlphaBitDepth;
                DWORD         dwReserved;
                void*         lpSurface;
                DDCOLORKEY    ddckCKDestOverlay;
                DDCOLORKEY    ddckCKDestBlt;
                DDCOLORKEY    ddckCKSrcOverlay;
                DDCOLORKEY    ddckCKSrcBlt;
                DDPIXELFORMAT ddpfPixelFormat;
                DDSCAPS2      ddsCaps;
                DWORD         dwTextureStage;
            };

            enum D3DPRIMITIVETYPE : uint32_t
            {
                D3DPT_POINTLIST     = 1,
                D3DPT_LINELIST      = 2,
                D3DPT_LINESTRIP     = 3,
                D3DPT_TRIANGLELIST  = 4,
                D3DPT_TRIANGLESTRIP = 5,
                D3DPT_TRIANGLEFAN   = 6
            };

            /* Their values are decoded by the printer, which has the lists. */
            enum D3DRENDERSTATETYPE       : uint32_t { D3DRENDERSTATE_FORCE_DWORD       = 0x7fffffff };
            enum D3DSTATEBLOCKTYPE        : uint32_t { D3DSBT_FORCE_DWORD               = 0x7fffffff };
            enum D3DTEXTURESTAGESTATETYPE : uint32_t { D3DTSS_FORCE_DWORD               = 0x7fffffff };
            enum D3DTRANSFORMSTATETYPE    : uint32_t { D3DTRANSFORMSTATE_FORCE_DWORD    = 0x7fffffff };

            #if !defined(_WIN64)
                static_assert(sizeof(D3DCLIPSTATUS)               == 32,   "D3DCLIPSTATUS does not have the size of the DirectX 7 one");
                static_assert(sizeof(D3DDEVICEDESC7)              == 236,  "D3DDEVICEDESC7 does not have the size of the DirectX 7 one");
                static_assert(sizeof(D3DDRAWPRIMITIVESTRIDEDDATA) == 96,   "D3DDRAWPRIMITIVESTRIDEDDATA does not have the size of the DirectX 7 one");
                static_assert(sizeof(D3DLIGHT7)                   == 104,  "D3DLIGHT7 does not have the size of the DirectX 7 one");
                static_assert(sizeof(D3DMATERIAL7)                == 68,   "D3DMATERIAL7 does not have the size of the DirectX 7 one");
                static_assert(sizeof(D3DPRIMCAPS)                 == 56,   "D3DPRIMCAPS does not have the size of the DirectX 7 one");
                static_assert(sizeof(D3DVIEWPORT7)                == 24,   "D3DVIEWPORT7 does not have the size of the DirectX 7 one");
                static_assert(sizeof(DDBLTFX)                     == 100,  "DDBLTFX does not have the size of the DirectX 7 one");
                static_assert(sizeof(DDCAPS)                      == 380,  "DDCAPS does not have the size of the DirectX 7 one");
                static_assert(sizeof(DDCOLORCONTROL)              == 40,   "DDCOLORCONTROL does not have the size of the DirectX 7 one");
                static_assert(sizeof(DDDEVICEIDENTIFIER2)         == 1072, "DDDEVICEIDENTIFIER2 does not have the size of the DirectX 7 one");
                static_assert(sizeof(DDGAMMARAMP)                 == 1536, "DDGAMMARAMP does not have the size of the DirectX 7 one");
                static_assert(sizeof(DDOVERLAYFX)                 == 56,   "DDOVERLAYFX does not have the size of the DirectX 7 one");
                static_assert(sizeof(DDPIXELFORMAT)               == 32,   "DDPIXELFORMAT does not have the size of the DirectX 7 one");
                static_assert(sizeof(DDSCAPS2)                    == 16,   "DDSCAPS2 does not have the size of the DirectX 7 one");
                static_assert(sizeof(DDSURFACEDESC2)              == 124,  "DDSURFACEDESC2 does not have the size of the DirectX 7 one");
            #endif

            /* Interfaces (opaque). IDirectDraw is the first one, of which only the unknown methods are described. */
            struct IDirect3D7;
            struct IDirect3DDevice7;
            struct IDirect3DVertexBuffer7;
            struct IDirectDraw;
            struct IDirectDraw7;
            struct IDirectDrawClipper;
            struct IDirectDrawColorControl;
            struct IDirectDrawGammaControl;
            struct IDirectDrawPalette;
            struct IDirectDrawSurface7;

            /* Interfaces described by the method table. */
            enum class Interface : uint32_t
            {
                #define D3D7_INTERFACE(INTERFACE_TAG, interface_name) INTERFACE_TAG,
                #define D3D7_METHOD(INTERFACE_TAG, interface_name, METHOD_TAG, method_name, vtable_index, return_type, parameters)
                #include "interception/hooks/D3D7/d3d7_methods.inl"
                #undef D3D7_METHOD
                #undef D3D7_INTERFACE

                COUNT,
                UNKNOWN = COUNT
            };

            struct MethodInfo
            {
                const char*                 full_name_ptr;      /* e.g. IDirect3DDevice7::BeginScene */
                APIInterceptor::APIFunction function;
                const char*                 interface_name_ptr; /* e.g. IDirect3DDevice7             */
                Interface                   interface_type;
                const char*                 method_name_ptr;    /* e.g. BeginScene                   */
                uint32_t                    vtable_index;
            };

            /* Meaning of an API call argument; tells the printer how to decode it. */
            enum class ValueKind : uint32_t
            {
                BLT_FAST_FLAGS,
                BLT_FLAGS,
                BLT_FX,
                BOOLEAN,
                CAPS,
                CLEAR_FLAGS,
                CLIP_PLANE,
                CLIP_STATUS,
                COLOR,
                COLOR_CONTROL,
                COLOR_KEY,
                COLOR_KEY_FLAGS,
                COOPERATIVE_LEVEL_FLAGS,
                DEVICE_DESC,
                DEVICE_IDENTIFIER,
                DRAW_FLAGS,
                ENUM_DISPLAY_MODES_FLAGS,
                ENUM_SURFACES_FLAGS,
                FLIP_FLAGS,
                FVF_FLAGS,
                GAMMA_RAMP,
                GUID,
                HRESULT,
                LIGHT,
                LOCK_FLAGS,
                MATERIAL,
                MATRIX,
                OBJECT,
                OBJECT_OUT,
                OVERLAY_FLAGS,
                OVERLAY_FX,
                PALETTE_ENTRIES,
                PALETTE_FLAGS,
                PIXEL_FORMAT,
                PLAIN,
                POINT,
                PRIMITIVE_TYPE,
                RECT,
                RECT_ARRAY,
                RENDER_STATE_TYPE,
                RENDER_STATE_VALUE,
                SET_DISPLAY_MODE_FLAGS,
                STATE_BLOCK_TYPE,
                STRIDED_DATA,
                STRIDED_VERTEX_ARRAYS,
                SURFACE_CAPS,
                SURFACE_DESC,
                TEXTURE_STAGE_STATE_TYPE,
                TEXTURE_STAGE_STATE_VALUE,
                TRANSFORM_STATE_TYPE,
                VERTEX_BUFFER_DESC,
                VERTEX_OPERATION_FLAGS,
                VIEWPORT,
                WAIT_FOR_VERTICAL_BLANK_FLAGS
            };

            /* Describes an argument or a returned value of a D3D7 method. Follows ValueKind, which it depends on. */
            struct ArgumentInfo
            {
                ValueKind   kind;
                const char* object_type_name_ptr; /* e.g. "Surface"; set for ValueKind::OBJECT and ::OBJECT_OUT only */
            };

            /* DWORD argument which holds flags or a color, or whose meaning depends on another argument; or an extra argument which a
             * hook adds.
             */
            struct ArgumentOverride
            {
                APIInterceptor::APIFunction function;
                ValueKind                   kind;
                uint32_t                    n_argument;
            };

            /* Accessors of the description of a method's signature. */
            typedef Interception::Core::Common::SignatureEntry<ArgumentInfo> SignatureEntry;

            /* The functions exported by ddraw.dll which are hooked. */
            typedef HRESULT (__stdcall* PFNDIRECTDRAWCREATECLIPPERPROC)(DWORD, IDirectDrawClipper**, IUnknown*);
            typedef HRESULT (__stdcall* PFNDIRECTDRAWCREATEEXPROC)     (GUID*, void**, const GUID&, IUnknown*);
            typedef HRESULT (__stdcall* PFNDIRECTDRAWCREATEPROC)       (GUID*, IDirectDraw**, IUnknown*);
            typedef HRESULT (__stdcall* PFNDIRECTDRAWENUMERATEEXPROC)  (void*, void*, DWORD);
            typedef HRESULT (__stdcall* PFNDIRECTDRAWENUMERATEPROC)    (void*, void*);

            /* Function pointer type of each method, e.g. PFN_IDIRECT3DDEVICE7_BEGINSCENE. */
            #define D3D7_METHOD(INTERFACE_TAG, interface_name, METHOD_TAG, method_name, vtable_index, return_type, parameters) \
                typedef return_type (__stdcall *PFN_##INTERFACE_TAG##_##METHOD_TAG) parameters;
            #include "interception/hooks/D3D7/d3d7_methods.inl"
            #undef D3D7_METHOD

            /* Vtable slot of each method, e.g. VTABLE_INDEX_IDIRECT3DDEVICE7_BEGINSCENE. */
            enum VtableIndex : uint32_t
            {
                #define D3D7_METHOD(INTERFACE_TAG, interface_name, METHOD_TAG, method_name, vtable_index, return_type, parameters) \
                    VTABLE_INDEX_##INTERFACE_TAG##_##METHOD_TAG = vtable_index,
                #include "interception/hooks/D3D7/d3d7_methods.inl"
                #undef D3D7_METHOD
            };
        }
    }
}

#endif /* D3D7_TYPES_H */
