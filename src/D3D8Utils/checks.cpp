/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Compile-time checks of the D3D8 definitions. "binary" = observed in the disassembled target (fr08v101.exe), where
 * a method at vtable offset N * 4 is slot N.
 */
#include "D3D8Utils/methods.h"

/* Structure sizes, identical on x86 and x64. */
static_assert(sizeof(D3D8::D3DCLIPSTATUS8)          == 8,    "D3DCLIPSTATUS8 size mismatch");
static_assert(sizeof(D3D8::D3DCOLORVALUE)           == 16,   "D3DCOLORVALUE size mismatch");
static_assert(sizeof(D3D8::D3DDISPLAYMODE)          == 16,   "D3DDISPLAYMODE size mismatch");
static_assert(sizeof(D3D8::D3DGAMMARAMP)            == 1536, "D3DGAMMARAMP size mismatch");
static_assert(sizeof(D3D8::D3DINDEXBUFFER_DESC)     == 20,   "D3DINDEXBUFFER_DESC size mismatch");
static_assert(sizeof(D3D8::D3DLIGHT8)               == 104,  "D3DLIGHT8 size mismatch");
static_assert(sizeof(D3D8::D3DMATERIAL8)            == 68,   "D3DMATERIAL8 size mismatch");
static_assert(sizeof(D3D8::D3DMATRIX)               == 64,   "D3DMATRIX size mismatch");
static_assert(sizeof(D3D8::D3DRASTER_STATUS)        == 8,    "D3DRASTER_STATUS size mismatch");
static_assert(sizeof(D3D8::D3DRECT)                 == 16,   "D3DRECT size mismatch");
static_assert(sizeof(D3D8::D3DRECTPATCH_INFO)       == 28,   "D3DRECTPATCH_INFO size mismatch");
static_assert(sizeof(D3D8::D3DSURFACE_DESC)         == 32,   "D3DSURFACE_DESC size mismatch");
static_assert(sizeof(D3D8::D3DTRIPATCH_INFO)        == 16,   "D3DTRIPATCH_INFO size mismatch");
static_assert(sizeof(D3D8::D3DVECTOR)               == 12,   "D3DVECTOR size mismatch");
static_assert(sizeof(D3D8::D3DVERTEXBUFFER_DESC)    == 24,   "D3DVERTEXBUFFER_DESC size mismatch");
static_assert(sizeof(D3D8::D3DVIEWPORT8)            == 24,   "D3DVIEWPORT8 size mismatch");

/* Structure sizes which depend on the pointer size. */
#if defined(_WIN64)
    static_assert(sizeof(D3D8::D3DDEVICE_CREATION_PARAMETERS) == 24, "D3DDEVICE_CREATION_PARAMETERS size mismatch");
    static_assert(sizeof(D3D8::D3DLOCKED_RECT)                == 16, "D3DLOCKED_RECT size mismatch");
    static_assert(sizeof(D3D8::D3DPRESENT_PARAMETERS)         == 56, "D3DPRESENT_PARAMETERS size mismatch");
#else
    static_assert(sizeof(D3D8::D3DDEVICE_CREATION_PARAMETERS) == 16, "D3DDEVICE_CREATION_PARAMETERS size mismatch");
    static_assert(sizeof(D3D8::D3DLOCKED_RECT)                == 8,  "D3DLOCKED_RECT size mismatch");
    static_assert(sizeof(D3D8::D3DPRESENT_PARAMETERS)         == 52, "D3DPRESENT_PARAMETERS size mismatch");
#endif

/* Device vtable slots (binary). */
static_assert(D3D8::VTABLE_INDEX_IDIRECT3DDEVICE8_SETRENDERTARGET      * 4 == 0x7c,  "SetRenderTarget slot mismatch");
static_assert(D3D8::VTABLE_INDEX_IDIRECT3DDEVICE8_BEGINSCENE           * 4 == 0x88,  "BeginScene slot mismatch");
static_assert(D3D8::VTABLE_INDEX_IDIRECT3DDEVICE8_ENDSCENE             * 4 == 0x8c,  "EndScene slot mismatch");
static_assert(D3D8::VTABLE_INDEX_IDIRECT3DDEVICE8_CLEAR                * 4 == 0x90,  "Clear slot mismatch");
static_assert(D3D8::VTABLE_INDEX_IDIRECT3DDEVICE8_SETTRANSFORM         * 4 == 0x94,  "SetTransform slot mismatch");
static_assert(D3D8::VTABLE_INDEX_IDIRECT3DDEVICE8_SETVIEWPORT          * 4 == 0xa0,  "SetViewport slot mismatch");
static_assert(D3D8::VTABLE_INDEX_IDIRECT3DDEVICE8_SETMATERIAL          * 4 == 0xa8,  "SetMaterial slot mismatch");
static_assert(D3D8::VTABLE_INDEX_IDIRECT3DDEVICE8_SETRENDERSTATE       * 4 == 0xc8,  "SetRenderState slot mismatch");
static_assert(D3D8::VTABLE_INDEX_IDIRECT3DDEVICE8_SETTEXTURE           * 4 == 0xf4,  "SetTexture slot mismatch");
static_assert(D3D8::VTABLE_INDEX_IDIRECT3DDEVICE8_DRAWINDEXEDPRIMITIVE * 4 == 0x11c, "DrawIndexedPrimitive slot mismatch");
static_assert(D3D8::VTABLE_INDEX_IDIRECT3DDEVICE8_SETVERTEXSHADER      * 4 == 0x130, "SetVertexShader slot mismatch");
static_assert(D3D8::VTABLE_INDEX_IDIRECT3DDEVICE8_SETSTREAMSOURCE      * 4 == 0x14c, "SetStreamSource slot mismatch");
static_assert(D3D8::VTABLE_INDEX_IDIRECT3DDEVICE8_SETINDICES           * 4 == 0x154, "SetIndices slot mismatch");

/* Device vtable slots (binary, slot numbers only). */
static_assert(D3D8::VTABLE_INDEX_IDIRECT3DDEVICE8_TESTCOOPERATIVELEVEL      == 3,  "TestCooperativeLevel slot mismatch");
static_assert(D3D8::VTABLE_INDEX_IDIRECT3DDEVICE8_RESET                     == 14, "Reset slot mismatch");
static_assert(D3D8::VTABLE_INDEX_IDIRECT3DDEVICE8_PRESENT                   == 15, "Present slot mismatch");
static_assert(D3D8::VTABLE_INDEX_IDIRECT3DDEVICE8_GETBACKBUFFER             == 16, "GetBackBuffer slot mismatch");
static_assert(D3D8::VTABLE_INDEX_IDIRECT3DDEVICE8_GETRASTERSTATUS           == 17, "GetRasterStatus slot mismatch");
static_assert(D3D8::VTABLE_INDEX_IDIRECT3DDEVICE8_GETGAMMARAMP              == 19, "GetGammaRamp slot mismatch");
static_assert(D3D8::VTABLE_INDEX_IDIRECT3DDEVICE8_CREATETEXTURE             == 20, "CreateTexture slot mismatch");
static_assert(D3D8::VTABLE_INDEX_IDIRECT3DDEVICE8_CREATEVERTEXBUFFER        == 23, "CreateVertexBuffer slot mismatch");
static_assert(D3D8::VTABLE_INDEX_IDIRECT3DDEVICE8_CREATEINDEXBUFFER         == 24, "CreateIndexBuffer slot mismatch");
static_assert(D3D8::VTABLE_INDEX_IDIRECT3DDEVICE8_CREATEDEPTHSTENCILSURFACE == 26, "CreateDepthStencilSurface slot mismatch");
static_assert(D3D8::VTABLE_INDEX_IDIRECT3DDEVICE8_GETRENDERTARGET           == 32, "GetRenderTarget slot mismatch");
static_assert(D3D8::VTABLE_INDEX_IDIRECT3DDEVICE8_GETDEPTHSTENCILSURFACE    == 33, "GetDepthStencilSurface slot mismatch");
static_assert(D3D8::VTABLE_INDEX_IDIRECT3DDEVICE8_SETLIGHT                  == 44, "SetLight slot mismatch");
static_assert(D3D8::VTABLE_INDEX_IDIRECT3DDEVICE8_LIGHTENABLE               == 46, "LightEnable slot mismatch");
static_assert(D3D8::VTABLE_INDEX_IDIRECT3DDEVICE8_SETTEXTURESTAGESTATE      == 63, "SetTextureStageState slot mismatch");

/* Texture vtable slots (binary). */
static_assert(D3D8::VTABLE_INDEX_IDIRECT3DTEXTURE8_GETSURFACELEVEL * 4 == 0x3c, "GetSurfaceLevel slot mismatch");

/* Flag and enum values (binary). */
static_assert((D3D8::D3DFVF_XYZ | D3D8::D3DFVF_NORMAL  | D3D8::D3DFVF_DIFFUSE  | D3D8::D3DFVF_TEX1) == 0x152, "FVF 0x152 mismatch");
static_assert((D3D8::D3DFVF_XYZ | D3D8::D3DFVF_DIFFUSE | D3D8::D3DFVF_SPECULAR | D3D8::D3DFVF_TEX2) == 0x2c2, "FVF 0x2c2 mismatch");

static_assert(D3D8::D3DTS_VIEW       == 2,     "D3DTS_VIEW mismatch");
static_assert(D3D8::D3DTS_PROJECTION == 3,     "D3DTS_PROJECTION mismatch");
static_assert(D3D8::D3DTS_WORLD      == 0x100, "D3DTS_WORLD mismatch");
static_assert(D3D8::D3DTS_TEXTURE0   == 0x10,  "D3DTS_TEXTURE0 mismatch");
static_assert(D3D8::D3DTS_TEXTURE1   == 0x11,  "D3DTS_TEXTURE1 mismatch");
