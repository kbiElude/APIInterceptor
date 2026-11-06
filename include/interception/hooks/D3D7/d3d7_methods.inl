/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * D3D7 method table (X-macro), covering DirectDraw 7 and Direct3D 7. Before including, define:
 *   D3D7_METHOD(INTERFACE_TAG, interface_name, METHOD_TAG, method_name, vtable_index, return_type, parameters)
 *   D3D7_INTERFACE(INTERFACE_TAG, interface_name) (optional)
 *
 * Tags are upper-case; parameters start with 'self'. Methods are listed per interface, in vtable order. New interfaces are
 * appended, so that the function IDs in existing dumps stay valid. Types resolve in namespace D3D7. Pointers to callbacks
 * are stored as addresses.
 *
 * IDirectDraw is the interface of DirectDrawCreate. Of it, and of the other versions of the interfaces of DirectDraw which
 * precede the 7th, only the methods of IUnknown are hooked: that is what is needed to get the objects of the 7th version
 * out of them with QueryInterface.
 */
#if !defined(D3D7_METHOD)
    #error D3D7_METHOD must be defined before including d3d7_methods.inl
#endif

#if !defined(D3D7_INTERFACE)
    #define D3D7_INTERFACE(INTERFACE_TAG, interface_name)
    #define D3D7_INTERFACE_DEFINED_BY_METHODS_INL
#endif

#define D3D7_IUNKNOWN_METHODS(INTERFACE_TAG, interface_name) \
    D3D7_METHOD(INTERFACE_TAG, interface_name, QUERYINTERFACE, QueryInterface, 0, HRESULT, (interface_name* self, REFIID riid, void** ppvObj)) \
    D3D7_METHOD(INTERFACE_TAG, interface_name, ADDREF,         AddRef,         1, ULONG,   (interface_name* self))                             \
    D3D7_METHOD(INTERFACE_TAG, interface_name, RELEASE,        Release,        2, ULONG,   (interface_name* self))

#define D3D7_DIRECTDRAW_METHOD(METHOD_TAG, method_name, vtable_index, return_type, parameters) \
    D3D7_METHOD(IDIRECTDRAW7, IDirectDraw7, METHOD_TAG, method_name, vtable_index, return_type, parameters)

D3D7_INTERFACE(IDIRECTDRAW7, IDirectDraw7)

D3D7_IUNKNOWN_METHODS(IDIRECTDRAW7, IDirectDraw7)
D3D7_DIRECTDRAW_METHOD(COMPACT,                Compact,                3,  HRESULT, (IDirectDraw7* self))
D3D7_DIRECTDRAW_METHOD(CREATECLIPPER,          CreateClipper,          4,  HRESULT, (IDirectDraw7* self, DWORD dwFlags, IDirectDrawClipper** lplpDDClipper, IUnknown* pUnkOuter))
D3D7_DIRECTDRAW_METHOD(CREATEPALETTE,          CreatePalette,          5,  HRESULT, (IDirectDraw7* self, DWORD dwFlags, const PALETTEENTRY* lpColorTable, IDirectDrawPalette** lplpDDPalette, IUnknown* pUnkOuter))
D3D7_DIRECTDRAW_METHOD(CREATESURFACE,          CreateSurface,          6,  HRESULT, (IDirectDraw7* self, const DDSURFACEDESC2* lpDDSurfaceDesc2, IDirectDrawSurface7** lplpDDSurface, IUnknown* pUnkOuter))
D3D7_DIRECTDRAW_METHOD(DUPLICATESURFACE,       DuplicateSurface,       7,  HRESULT, (IDirectDraw7* self, IDirectDrawSurface7* lpDDSurface, IDirectDrawSurface7** lplpDupDDSurface))
D3D7_DIRECTDRAW_METHOD(ENUMDISPLAYMODES,       EnumDisplayModes,       8,  HRESULT, (IDirectDraw7* self, DWORD dwFlags, const DDSURFACEDESC2* lpDDSurfaceDesc2, void* lpContext, void* lpEnumModesCallback))
D3D7_DIRECTDRAW_METHOD(ENUMSURFACES,           EnumSurfaces,           9,  HRESULT, (IDirectDraw7* self, DWORD dwFlags, const DDSURFACEDESC2* lpDDSD2, void* lpContext, void* lpEnumSurfacesCallback))
D3D7_DIRECTDRAW_METHOD(FLIPTOGDISURFACE,       FlipToGDISurface,       10, HRESULT, (IDirectDraw7* self))
D3D7_DIRECTDRAW_METHOD(GETCAPS,                GetCaps,                11, HRESULT, (IDirectDraw7* self, DDCAPS* lpDDDriverCaps, DDCAPS* lpDDHELCaps))
D3D7_DIRECTDRAW_METHOD(GETDISPLAYMODE,         GetDisplayMode,         12, HRESULT, (IDirectDraw7* self, DDSURFACEDESC2* lpDDSurfaceDesc2))
D3D7_DIRECTDRAW_METHOD(GETFOURCCCODES,         GetFourCCCodes,         13, HRESULT, (IDirectDraw7* self, DWORD* lpNumCodes, DWORD* lpCodes))
D3D7_DIRECTDRAW_METHOD(GETGDISURFACE,          GetGDISurface,          14, HRESULT, (IDirectDraw7* self, IDirectDrawSurface7** lplpGDIDDSSurface))
D3D7_DIRECTDRAW_METHOD(GETMONITORFREQUENCY,    GetMonitorFrequency,    15, HRESULT, (IDirectDraw7* self, DWORD* lpdwFrequency))
D3D7_DIRECTDRAW_METHOD(GETSCANLINE,            GetScanLine,            16, HRESULT, (IDirectDraw7* self, DWORD* lpdwScanLine))
D3D7_DIRECTDRAW_METHOD(GETVERTICALBLANKSTATUS, GetVerticalBlankStatus, 17, HRESULT, (IDirectDraw7* self, BOOL* lpbIsInVB))
D3D7_DIRECTDRAW_METHOD(INITIALIZE,             Initialize,             18, HRESULT, (IDirectDraw7* self, GUID* lpGUID))
D3D7_DIRECTDRAW_METHOD(RESTOREDISPLAYMODE,     RestoreDisplayMode,     19, HRESULT, (IDirectDraw7* self))
D3D7_DIRECTDRAW_METHOD(SETCOOPERATIVELEVEL,    SetCooperativeLevel,    20, HRESULT, (IDirectDraw7* self, HWND hWnd, DWORD dwFlags))
D3D7_DIRECTDRAW_METHOD(SETDISPLAYMODE,         SetDisplayMode,         21, HRESULT, (IDirectDraw7* self, DWORD dwWidth, DWORD dwHeight, DWORD dwBPP, DWORD dwRefreshRate, DWORD dwFlags))
D3D7_DIRECTDRAW_METHOD(WAITFORVERTICALBLANK,   WaitForVerticalBlank,   22, HRESULT, (IDirectDraw7* self, DWORD dwFlags, HANDLE hEvent))
D3D7_DIRECTDRAW_METHOD(GETAVAILABLEVIDMEM,     GetAvailableVidMem,     23, HRESULT, (IDirectDraw7* self, const DDSCAPS2* lpDDSCaps2, DWORD* lpdwTotal, DWORD* lpdwFree))
D3D7_DIRECTDRAW_METHOD(GETSURFACEFROMDC,       GetSurfaceFromDC,       24, HRESULT, (IDirectDraw7* self, HDC hdc, IDirectDrawSurface7** lpDDS))
D3D7_DIRECTDRAW_METHOD(RESTOREALLSURFACES,     RestoreAllSurfaces,     25, HRESULT, (IDirectDraw7* self))
D3D7_DIRECTDRAW_METHOD(TESTCOOPERATIVELEVEL,   TestCooperativeLevel,   26, HRESULT, (IDirectDraw7* self))
D3D7_DIRECTDRAW_METHOD(GETDEVICEIDENTIFIER,    GetDeviceIdentifier,    27, HRESULT, (IDirectDraw7* self, DDDEVICEIDENTIFIER2* lpdddi, DWORD dwFlags))
D3D7_DIRECTDRAW_METHOD(STARTMODETEST,          StartModeTest,          28, HRESULT, (IDirectDraw7* self, SIZE* lpModesToTest, DWORD dwNumEntries, DWORD dwFlags))
D3D7_DIRECTDRAW_METHOD(EVALUATEMODE,           EvaluateMode,           29, HRESULT, (IDirectDraw7* self, DWORD dwFlags, DWORD* pSecondsUntilTimeout))

#define D3D7_SURFACE_METHOD(METHOD_TAG, method_name, vtable_index, return_type, parameters) \
    D3D7_METHOD(IDIRECTDRAWSURFACE7, IDirectDrawSurface7, METHOD_TAG, method_name, vtable_index, return_type, parameters)

D3D7_INTERFACE(IDIRECTDRAWSURFACE7, IDirectDrawSurface7)

D3D7_IUNKNOWN_METHODS(IDIRECTDRAWSURFACE7, IDirectDrawSurface7)
D3D7_SURFACE_METHOD(ADDATTACHEDSURFACE,     AddAttachedSurface,     3,  HRESULT, (IDirectDrawSurface7* self, IDirectDrawSurface7* lpDDSAttachedSurface))
D3D7_SURFACE_METHOD(ADDOVERLAYDIRTYRECT,    AddOverlayDirtyRect,    4,  HRESULT, (IDirectDrawSurface7* self, const RECT* lpRect))
D3D7_SURFACE_METHOD(BLT,                    Blt,                    5,  HRESULT, (IDirectDrawSurface7* self, const RECT* lpDestRect, IDirectDrawSurface7* lpDDSrcSurface, const RECT* lpSrcRect, DWORD dwFlags, const DDBLTFX* lpDDBltFx))
D3D7_SURFACE_METHOD(BLTBATCH,               BltBatch,               6,  HRESULT, (IDirectDrawSurface7* self, void* lpDDBltBatch, DWORD dwCount, DWORD dwFlags))
D3D7_SURFACE_METHOD(BLTFAST,                BltFast,                7,  HRESULT, (IDirectDrawSurface7* self, DWORD dwX, DWORD dwY, IDirectDrawSurface7* lpDDSrcSurface, const RECT* lpSrcRect, DWORD dwTrans))
D3D7_SURFACE_METHOD(DELETEATTACHEDSURFACE,  DeleteAttachedSurface,  8,  HRESULT, (IDirectDrawSurface7* self, DWORD dwFlags, IDirectDrawSurface7* lpDDSAttachedSurface))
D3D7_SURFACE_METHOD(ENUMATTACHEDSURFACES,   EnumAttachedSurfaces,   9,  HRESULT, (IDirectDrawSurface7* self, void* lpContext, void* lpEnumSurfacesCallback))
D3D7_SURFACE_METHOD(ENUMOVERLAYZORDERS,     EnumOverlayZOrders,     10, HRESULT, (IDirectDrawSurface7* self, DWORD dwFlags, void* lpContext, void* lpfnCallback))
D3D7_SURFACE_METHOD(FLIP,                   Flip,                   11, HRESULT, (IDirectDrawSurface7* self, IDirectDrawSurface7* lpDDSurfaceTargetOverride, DWORD dwFlags))
D3D7_SURFACE_METHOD(GETATTACHEDSURFACE,     GetAttachedSurface,     12, HRESULT, (IDirectDrawSurface7* self, const DDSCAPS2* lpDDSCaps, IDirectDrawSurface7** lplpDDAttachedSurface))
D3D7_SURFACE_METHOD(GETBLTSTATUS,           GetBltStatus,           13, HRESULT, (IDirectDrawSurface7* self, DWORD dwFlags))
D3D7_SURFACE_METHOD(GETCAPS,                GetCaps,                14, HRESULT, (IDirectDrawSurface7* self, DDSCAPS2* lpDDSCaps))
D3D7_SURFACE_METHOD(GETCLIPPER,             GetClipper,             15, HRESULT, (IDirectDrawSurface7* self, IDirectDrawClipper** lplpDDClipper))
D3D7_SURFACE_METHOD(GETCOLORKEY,            GetColorKey,            16, HRESULT, (IDirectDrawSurface7* self, DWORD dwFlags, DDCOLORKEY* lpDDColorKey))
D3D7_SURFACE_METHOD(GETDC,                  GetDC,                  17, HRESULT, (IDirectDrawSurface7* self, HDC* lphDC))
D3D7_SURFACE_METHOD(GETFLIPSTATUS,          GetFlipStatus,          18, HRESULT, (IDirectDrawSurface7* self, DWORD dwFlags))
D3D7_SURFACE_METHOD(GETOVERLAYPOSITION,     GetOverlayPosition,     19, HRESULT, (IDirectDrawSurface7* self, LONG* lplX, LONG* lplY))
D3D7_SURFACE_METHOD(GETPALETTE,             GetPalette,             20, HRESULT, (IDirectDrawSurface7* self, IDirectDrawPalette** lplpDDPalette))
D3D7_SURFACE_METHOD(GETPIXELFORMAT,         GetPixelFormat,         21, HRESULT, (IDirectDrawSurface7* self, DDPIXELFORMAT* lpDDPixelFormat))
D3D7_SURFACE_METHOD(GETSURFACEDESC,         GetSurfaceDesc,         22, HRESULT, (IDirectDrawSurface7* self, DDSURFACEDESC2* lpDDSurfaceDesc))
D3D7_SURFACE_METHOD(INITIALIZE,             Initialize,             23, HRESULT, (IDirectDrawSurface7* self, IDirectDraw7* lpDD, const DDSURFACEDESC2* lpDDSurfaceDesc))
D3D7_SURFACE_METHOD(ISLOST,                 IsLost,                 24, HRESULT, (IDirectDrawSurface7* self))
D3D7_SURFACE_METHOD(LOCK,                   Lock,                   25, HRESULT, (IDirectDrawSurface7* self, const RECT* lpDestRect, DDSURFACEDESC2* lpDDSurfaceDesc, DWORD dwFlags, HANDLE hEvent))
D3D7_SURFACE_METHOD(RELEASEDC,              ReleaseDC,              26, HRESULT, (IDirectDrawSurface7* self, HDC hDC))
D3D7_SURFACE_METHOD(RESTORE,                Restore,                27, HRESULT, (IDirectDrawSurface7* self))
D3D7_SURFACE_METHOD(SETCLIPPER,             SetClipper,             28, HRESULT, (IDirectDrawSurface7* self, IDirectDrawClipper* lpDDClipper))
D3D7_SURFACE_METHOD(SETCOLORKEY,            SetColorKey,            29, HRESULT, (IDirectDrawSurface7* self, DWORD dwFlags, const DDCOLORKEY* lpDDColorKey))
D3D7_SURFACE_METHOD(SETOVERLAYPOSITION,     SetOverlayPosition,     30, HRESULT, (IDirectDrawSurface7* self, LONG lX, LONG lY))
D3D7_SURFACE_METHOD(SETPALETTE,             SetPalette,             31, HRESULT, (IDirectDrawSurface7* self, IDirectDrawPalette* lpDDPalette))
D3D7_SURFACE_METHOD(UNLOCK,                 Unlock,                 32, HRESULT, (IDirectDrawSurface7* self, const RECT* lpRect))
D3D7_SURFACE_METHOD(UPDATEOVERLAY,          UpdateOverlay,          33, HRESULT, (IDirectDrawSurface7* self, const RECT* lpSrcRect, IDirectDrawSurface7* lpDDDestSurface, const RECT* lpDestRect, DWORD dwFlags, const DDOVERLAYFX* lpDDOverlayFx))
D3D7_SURFACE_METHOD(UPDATEOVERLAYDISPLAY,   UpdateOverlayDisplay,   34, HRESULT, (IDirectDrawSurface7* self, DWORD dwFlags))
D3D7_SURFACE_METHOD(UPDATEOVERLAYZORDER,    UpdateOverlayZOrder,    35, HRESULT, (IDirectDrawSurface7* self, DWORD dwFlags, IDirectDrawSurface7* lpDDSReference))
D3D7_SURFACE_METHOD(GETDDINTERFACE,         GetDDInterface,         36, HRESULT, (IDirectDrawSurface7* self, void** lplpDD))
D3D7_SURFACE_METHOD(PAGELOCK,               PageLock,               37, HRESULT, (IDirectDrawSurface7* self, DWORD dwFlags))
D3D7_SURFACE_METHOD(PAGEUNLOCK,             PageUnlock,             38, HRESULT, (IDirectDrawSurface7* self, DWORD dwFlags))
D3D7_SURFACE_METHOD(SETSURFACEDESC,         SetSurfaceDesc,         39, HRESULT, (IDirectDrawSurface7* self, const DDSURFACEDESC2* lpddsd2, DWORD dwFlags))
D3D7_SURFACE_METHOD(SETPRIVATEDATA,         SetPrivateData,         40, HRESULT, (IDirectDrawSurface7* self, REFGUID guidTag, const void* lpData, DWORD cbSize, DWORD dwFlags))
D3D7_SURFACE_METHOD(GETPRIVATEDATA,         GetPrivateData,         41, HRESULT, (IDirectDrawSurface7* self, REFGUID guidTag, void* lpBuffer, DWORD* lpcbBufferSize))
D3D7_SURFACE_METHOD(FREEPRIVATEDATA,        FreePrivateData,        42, HRESULT, (IDirectDrawSurface7* self, REFGUID guidTag))
D3D7_SURFACE_METHOD(GETUNIQUENESSVALUE,     GetUniquenessValue,     43, HRESULT, (IDirectDrawSurface7* self, DWORD* lpValue))
D3D7_SURFACE_METHOD(CHANGEUNIQUENESSVALUE,  ChangeUniquenessValue,  44, HRESULT, (IDirectDrawSurface7* self))
D3D7_SURFACE_METHOD(SETPRIORITY,            SetPriority,            45, HRESULT, (IDirectDrawSurface7* self, DWORD dwPriority))
D3D7_SURFACE_METHOD(GETPRIORITY,            GetPriority,            46, HRESULT, (IDirectDrawSurface7* self, DWORD* lpdwPriority))
D3D7_SURFACE_METHOD(SETLOD,                 SetLOD,                 47, HRESULT, (IDirectDrawSurface7* self, DWORD dwMaxLOD))
D3D7_SURFACE_METHOD(GETLOD,                 GetLOD,                 48, HRESULT, (IDirectDrawSurface7* self, DWORD* lpdwMaxLOD))

D3D7_INTERFACE(IDIRECT3D7, IDirect3D7)

D3D7_IUNKNOWN_METHODS(IDIRECT3D7, IDirect3D7)
D3D7_METHOD(IDIRECT3D7, IDirect3D7, ENUMDEVICES,           EnumDevices,          3, HRESULT, (IDirect3D7* self, void* lpEnumDevicesCallback, void* lpUserArg))
D3D7_METHOD(IDIRECT3D7, IDirect3D7, CREATEDEVICE,          CreateDevice,         4, HRESULT, (IDirect3D7* self, REFCLSID rclsid, IDirectDrawSurface7* lpDDS, IDirect3DDevice7** lplpD3DDevice))
D3D7_METHOD(IDIRECT3D7, IDirect3D7, CREATEVERTEXBUFFER,    CreateVertexBuffer,   5, HRESULT, (IDirect3D7* self, const D3DVERTEXBUFFERDESC* lpVBDesc, IDirect3DVertexBuffer7** lpD3DVertexBuffer, DWORD dwFlags))
D3D7_METHOD(IDIRECT3D7, IDirect3D7, ENUMZBUFFERFORMATS,    EnumZBufferFormats,   6, HRESULT, (IDirect3D7* self, REFCLSID riidDevice, void* lpEnumCallback, void* lpContext))
D3D7_METHOD(IDIRECT3D7, IDirect3D7, EVICTMANAGEDTEXTURES,  EvictManagedTextures, 7, HRESULT, (IDirect3D7* self))

#define D3D7_DEVICE_METHOD(METHOD_TAG, method_name, vtable_index, return_type, parameters) \
    D3D7_METHOD(IDIRECT3DDEVICE7, IDirect3DDevice7, METHOD_TAG, method_name, vtable_index, return_type, parameters)

D3D7_INTERFACE(IDIRECT3DDEVICE7, IDirect3DDevice7)

D3D7_IUNKNOWN_METHODS(IDIRECT3DDEVICE7, IDirect3DDevice7)
D3D7_DEVICE_METHOD(GETCAPS,                     GetCaps,                     3,  HRESULT, (IDirect3DDevice7* self, D3DDEVICEDESC7* lpD3DDevDesc))
D3D7_DEVICE_METHOD(ENUMTEXTUREFORMATS,          EnumTextureFormats,          4,  HRESULT, (IDirect3DDevice7* self, void* lpD3DEnumPixelProc, void* lpArg))
D3D7_DEVICE_METHOD(BEGINSCENE,                  BeginScene,                  5,  HRESULT, (IDirect3DDevice7* self))
D3D7_DEVICE_METHOD(ENDSCENE,                    EndScene,                    6,  HRESULT, (IDirect3DDevice7* self))
D3D7_DEVICE_METHOD(GETDIRECT3D,                 GetDirect3D,                 7,  HRESULT, (IDirect3DDevice7* self, IDirect3D7** lplpD3D))
D3D7_DEVICE_METHOD(SETRENDERTARGET,             SetRenderTarget,             8,  HRESULT, (IDirect3DDevice7* self, IDirectDrawSurface7* lpNewRenderTarget, DWORD dwFlags))
D3D7_DEVICE_METHOD(GETRENDERTARGET,             GetRenderTarget,             9,  HRESULT, (IDirect3DDevice7* self, IDirectDrawSurface7** lplpRenderTarget))
D3D7_DEVICE_METHOD(CLEAR,                       Clear,                       10, HRESULT, (IDirect3DDevice7* self, DWORD dwCount, const D3DRECT* lpRects, DWORD dwFlags, DWORD dwColor, float dvZ, DWORD dwStencil))
D3D7_DEVICE_METHOD(SETTRANSFORM,                SetTransform,                11, HRESULT, (IDirect3DDevice7* self, D3DTRANSFORMSTATETYPE dtstTransformStateType, const D3DMATRIX* lpD3DMatrix))
D3D7_DEVICE_METHOD(GETTRANSFORM,                GetTransform,                12, HRESULT, (IDirect3DDevice7* self, D3DTRANSFORMSTATETYPE dtstTransformStateType, D3DMATRIX* lpD3DMatrix))
D3D7_DEVICE_METHOD(SETVIEWPORT,                 SetViewport,                 13, HRESULT, (IDirect3DDevice7* self, const D3DVIEWPORT7* lpViewport))
D3D7_DEVICE_METHOD(MULTIPLYTRANSFORM,           MultiplyTransform,           14, HRESULT, (IDirect3DDevice7* self, D3DTRANSFORMSTATETYPE dtstTransformStateType, const D3DMATRIX* lpD3DMatrix))
D3D7_DEVICE_METHOD(GETVIEWPORT,                 GetViewport,                 15, HRESULT, (IDirect3DDevice7* self, D3DVIEWPORT7* lpViewport))
D3D7_DEVICE_METHOD(SETMATERIAL,                 SetMaterial,                 16, HRESULT, (IDirect3DDevice7* self, const D3DMATERIAL7* lpMaterial))
D3D7_DEVICE_METHOD(GETMATERIAL,                 GetMaterial,                 17, HRESULT, (IDirect3DDevice7* self, D3DMATERIAL7* lpMaterial))
D3D7_DEVICE_METHOD(SETLIGHT,                    SetLight,                    18, HRESULT, (IDirect3DDevice7* self, DWORD dwLightIndex, const D3DLIGHT7* lpLight))
D3D7_DEVICE_METHOD(GETLIGHT,                    GetLight,                    19, HRESULT, (IDirect3DDevice7* self, DWORD dwLightIndex, D3DLIGHT7* lpLight))
D3D7_DEVICE_METHOD(SETRENDERSTATE,              SetRenderState,              20, HRESULT, (IDirect3DDevice7* self, D3DRENDERSTATETYPE dwRenderStateType, DWORD dwRenderState))
D3D7_DEVICE_METHOD(GETRENDERSTATE,              GetRenderState,              21, HRESULT, (IDirect3DDevice7* self, D3DRENDERSTATETYPE dwRenderStateType, DWORD* lpdwRenderState))
D3D7_DEVICE_METHOD(BEGINSTATEBLOCK,             BeginStateBlock,             22, HRESULT, (IDirect3DDevice7* self))
D3D7_DEVICE_METHOD(ENDSTATEBLOCK,               EndStateBlock,               23, HRESULT, (IDirect3DDevice7* self, DWORD* lpdwBlockHandle))
D3D7_DEVICE_METHOD(PRELOAD,                     PreLoad,                     24, HRESULT, (IDirect3DDevice7* self, IDirectDrawSurface7* lpddsTexture))
D3D7_DEVICE_METHOD(DRAWPRIMITIVE,               DrawPrimitive,               25, HRESULT, (IDirect3DDevice7* self, D3DPRIMITIVETYPE d3dptPrimitiveType, DWORD dwVertexTypeDesc, void* lpvVertices, DWORD dwVertexCount, DWORD dwFlags))
D3D7_DEVICE_METHOD(DRAWINDEXEDPRIMITIVE,        DrawIndexedPrimitive,        26, HRESULT, (IDirect3DDevice7* self, D3DPRIMITIVETYPE d3dptPrimitiveType, DWORD dwVertexTypeDesc, void* lpvVertices, DWORD dwVertexCount, WORD* lpwIndices, DWORD dwIndexCount, DWORD dwFlags))
D3D7_DEVICE_METHOD(SETCLIPSTATUS,               SetClipStatus,               27, HRESULT, (IDirect3DDevice7* self, const D3DCLIPSTATUS* lpD3DClipStatus))
D3D7_DEVICE_METHOD(GETCLIPSTATUS,               GetClipStatus,               28, HRESULT, (IDirect3DDevice7* self, D3DCLIPSTATUS* lpD3DClipStatus))
D3D7_DEVICE_METHOD(DRAWPRIMITIVESTRIDED,        DrawPrimitiveStrided,        29, HRESULT, (IDirect3DDevice7* self, D3DPRIMITIVETYPE d3dptPrimitiveType, DWORD dwVertexTypeDesc, const D3DDRAWPRIMITIVESTRIDEDDATA* lpVertexArray, DWORD dwVertexCount, DWORD dwFlags))
D3D7_DEVICE_METHOD(DRAWINDEXEDPRIMITIVESTRIDED, DrawIndexedPrimitiveStrided, 30, HRESULT, (IDirect3DDevice7* self, D3DPRIMITIVETYPE d3dptPrimitiveType, DWORD dwVertexTypeDesc, const D3DDRAWPRIMITIVESTRIDEDDATA* lpVertexArray, DWORD dwVertexCount, WORD* lpwIndices, DWORD dwIndexCount, DWORD dwFlags))
D3D7_DEVICE_METHOD(DRAWPRIMITIVEVB,             DrawPrimitiveVB,             31, HRESULT, (IDirect3DDevice7* self, D3DPRIMITIVETYPE d3dptPrimitiveType, IDirect3DVertexBuffer7* lpd3dVertexBuffer, DWORD dwStartVertex, DWORD dwNumVertices, DWORD dwFlags))
D3D7_DEVICE_METHOD(DRAWINDEXEDPRIMITIVEVB,      DrawIndexedPrimitiveVB,      32, HRESULT, (IDirect3DDevice7* self, D3DPRIMITIVETYPE d3dptPrimitiveType, IDirect3DVertexBuffer7* lpd3dVertexBuffer, DWORD dwStartVertex, DWORD dwNumVertices, WORD* lpwIndices, DWORD dwIndexCount, DWORD dwFlags))
D3D7_DEVICE_METHOD(COMPUTESPHEREVISIBILITY,     ComputeSphereVisibility,     33, HRESULT, (IDirect3DDevice7* self, void* lpCenters, float* lpRadii, DWORD dwNumSpheres, DWORD dwFlags, DWORD* lpdwReturnValues))
D3D7_DEVICE_METHOD(GETTEXTURE,                  GetTexture,                  34, HRESULT, (IDirect3DDevice7* self, DWORD dwStage, IDirectDrawSurface7** lplpTexture))
D3D7_DEVICE_METHOD(SETTEXTURE,                  SetTexture,                  35, HRESULT, (IDirect3DDevice7* self, DWORD dwStage, IDirectDrawSurface7* lpTexture))
D3D7_DEVICE_METHOD(GETTEXTURESTAGESTATE,        GetTextureStageState,        36, HRESULT, (IDirect3DDevice7* self, DWORD dwStage, D3DTEXTURESTAGESTATETYPE dwState, DWORD* lpdwValue))
D3D7_DEVICE_METHOD(SETTEXTURESTAGESTATE,        SetTextureStageState,        37, HRESULT, (IDirect3DDevice7* self, DWORD dwStage, D3DTEXTURESTAGESTATETYPE dwState, DWORD dwValue))
D3D7_DEVICE_METHOD(VALIDATEDEVICE,              ValidateDevice,              38, HRESULT, (IDirect3DDevice7* self, DWORD* lpdwPasses))
D3D7_DEVICE_METHOD(APPLYSTATEBLOCK,             ApplyStateBlock,             39, HRESULT, (IDirect3DDevice7* self, DWORD dwBlockHandle))
D3D7_DEVICE_METHOD(CAPTURESTATEBLOCK,           CaptureStateBlock,           40, HRESULT, (IDirect3DDevice7* self, DWORD dwBlockHandle))
D3D7_DEVICE_METHOD(DELETESTATEBLOCK,            DeleteStateBlock,            41, HRESULT, (IDirect3DDevice7* self, DWORD dwBlockHandle))
D3D7_DEVICE_METHOD(CREATESTATEBLOCK,            CreateStateBlock,            42, HRESULT, (IDirect3DDevice7* self, D3DSTATEBLOCKTYPE d3dsbType, DWORD* lpdwBlockHandle))
D3D7_DEVICE_METHOD(LOAD,                        Load,                        43, HRESULT, (IDirect3DDevice7* self, IDirectDrawSurface7* lpDestTex, const POINT* lpDestPoint, IDirectDrawSurface7* lpSrcTex, const RECT* lprcSrcRect, DWORD dwFlags))
D3D7_DEVICE_METHOD(LIGHTENABLE,                 LightEnable,                 44, HRESULT, (IDirect3DDevice7* self, DWORD dwLightIndex, BOOL bEnable))
D3D7_DEVICE_METHOD(GETLIGHTENABLE,              GetLightEnable,              45, HRESULT, (IDirect3DDevice7* self, DWORD dwLightIndex, BOOL* pbEnable))
D3D7_DEVICE_METHOD(SETCLIPPLANE,                SetClipPlane,                46, HRESULT, (IDirect3DDevice7* self, DWORD dwIndex, const D3DCLIPPLANE* pPlaneEquation))
D3D7_DEVICE_METHOD(GETCLIPPLANE,                GetClipPlane,                47, HRESULT, (IDirect3DDevice7* self, DWORD dwIndex, D3DCLIPPLANE* pPlaneEquation))
D3D7_DEVICE_METHOD(GETINFO,                     GetInfo,                     48, HRESULT, (IDirect3DDevice7* self, DWORD dwDevInfoID, void* pDevInfoStruct, DWORD dwSize))

#define D3D7_VERTEX_BUFFER_METHOD(METHOD_TAG, method_name, vtable_index, return_type, parameters) \
    D3D7_METHOD(IDIRECT3DVERTEXBUFFER7, IDirect3DVertexBuffer7, METHOD_TAG, method_name, vtable_index, return_type, parameters)

D3D7_INTERFACE(IDIRECT3DVERTEXBUFFER7, IDirect3DVertexBuffer7)

D3D7_IUNKNOWN_METHODS(IDIRECT3DVERTEXBUFFER7, IDirect3DVertexBuffer7)
D3D7_VERTEX_BUFFER_METHOD(LOCK,                   Lock,                   3, HRESULT, (IDirect3DVertexBuffer7* self, DWORD dwFlags, void** lplpData, DWORD* lpdwSize))
D3D7_VERTEX_BUFFER_METHOD(UNLOCK,                 Unlock,                 4, HRESULT, (IDirect3DVertexBuffer7* self))
D3D7_VERTEX_BUFFER_METHOD(PROCESSVERTICES,        ProcessVertices,        5, HRESULT, (IDirect3DVertexBuffer7* self, DWORD dwVertexOp, DWORD dwDestIndex, DWORD dwCount, IDirect3DVertexBuffer7* lpSrcBuffer, DWORD dwSrcIndex, IDirect3DDevice7* lpD3DDevice, DWORD dwFlags))
D3D7_VERTEX_BUFFER_METHOD(GETVERTEXBUFFERDESC,    GetVertexBufferDesc,    6, HRESULT, (IDirect3DVertexBuffer7* self, D3DVERTEXBUFFERDESC* lpD3DVertexBufferDesc))
D3D7_VERTEX_BUFFER_METHOD(OPTIMIZE,               Optimize,               7, HRESULT, (IDirect3DVertexBuffer7* self, IDirect3DDevice7* lpD3DDevice, DWORD dwFlags))
D3D7_VERTEX_BUFFER_METHOD(PROCESSVERTICESSTRIDED, ProcessVerticesStrided, 8, HRESULT, (IDirect3DVertexBuffer7* self, DWORD dwVertexOp, DWORD dwDestIndex, DWORD dwCount, const D3DDRAWPRIMITIVESTRIDEDDATA* lpVertexArray, DWORD dwSrcIndex, IDirect3DDevice7* lpD3DDevice, DWORD dwFlags))

D3D7_INTERFACE(IDIRECTDRAWPALETTE, IDirectDrawPalette)

D3D7_IUNKNOWN_METHODS(IDIRECTDRAWPALETTE, IDirectDrawPalette)
D3D7_METHOD(IDIRECTDRAWPALETTE, IDirectDrawPalette, GETCAPS,    GetCaps,    3, HRESULT, (IDirectDrawPalette* self, DWORD* lpdwCaps))
D3D7_METHOD(IDIRECTDRAWPALETTE, IDirectDrawPalette, GETENTRIES, GetEntries, 4, HRESULT, (IDirectDrawPalette* self, DWORD dwFlags, DWORD dwBase, DWORD dwNumEntries, PALETTEENTRY* lpEntries))
D3D7_METHOD(IDIRECTDRAWPALETTE, IDirectDrawPalette, INITIALIZE, Initialize, 5, HRESULT, (IDirectDrawPalette* self, IDirectDraw* lpDD, DWORD dwFlags, const PALETTEENTRY* lpDDColorTable))
D3D7_METHOD(IDIRECTDRAWPALETTE, IDirectDrawPalette, SETENTRIES, SetEntries, 6, HRESULT, (IDirectDrawPalette* self, DWORD dwFlags, DWORD dwStartingEntry, DWORD dwCount, const PALETTEENTRY* lpEntries))

D3D7_INTERFACE(IDIRECTDRAWCLIPPER, IDirectDrawClipper)

D3D7_IUNKNOWN_METHODS(IDIRECTDRAWCLIPPER, IDirectDrawClipper)
D3D7_METHOD(IDIRECTDRAWCLIPPER, IDirectDrawClipper, GETCLIPLIST,       GetClipList,      3, HRESULT, (IDirectDrawClipper* self, const RECT* lpRect, RGNDATA* lpClipList, DWORD* lpdwSize))
D3D7_METHOD(IDIRECTDRAWCLIPPER, IDirectDrawClipper, GETHWND,           GetHWnd,          4, HRESULT, (IDirectDrawClipper* self, HWND* lphWnd))
D3D7_METHOD(IDIRECTDRAWCLIPPER, IDirectDrawClipper, INITIALIZE,        Initialize,       5, HRESULT, (IDirectDrawClipper* self, IDirectDraw* lpDD, DWORD dwFlags))
D3D7_METHOD(IDIRECTDRAWCLIPPER, IDirectDrawClipper, ISCLIPLISTCHANGED, IsClipListChanged, 6, HRESULT, (IDirectDrawClipper* self, BOOL* lpbChanged))
D3D7_METHOD(IDIRECTDRAWCLIPPER, IDirectDrawClipper, SETCLIPLIST,       SetClipList,      7, HRESULT, (IDirectDrawClipper* self, const RGNDATA* lpClipList, DWORD dwFlags))
D3D7_METHOD(IDIRECTDRAWCLIPPER, IDirectDrawClipper, SETHWND,           SetHWnd,          8, HRESULT, (IDirectDrawClipper* self, DWORD dwFlags, HWND hWnd))

D3D7_INTERFACE(IDIRECTDRAWCOLORCONTROL, IDirectDrawColorControl)

D3D7_IUNKNOWN_METHODS(IDIRECTDRAWCOLORCONTROL, IDirectDrawColorControl)
D3D7_METHOD(IDIRECTDRAWCOLORCONTROL, IDirectDrawColorControl, GETCOLORCONTROLS, GetColorControls, 3, HRESULT, (IDirectDrawColorControl* self, DDCOLORCONTROL* lpColorControl))
D3D7_METHOD(IDIRECTDRAWCOLORCONTROL, IDirectDrawColorControl, SETCOLORCONTROLS, SetColorControls, 4, HRESULT, (IDirectDrawColorControl* self, const DDCOLORCONTROL* lpColorControl))

D3D7_INTERFACE(IDIRECTDRAWGAMMACONTROL, IDirectDrawGammaControl)

D3D7_IUNKNOWN_METHODS(IDIRECTDRAWGAMMACONTROL, IDirectDrawGammaControl)
D3D7_METHOD(IDIRECTDRAWGAMMACONTROL, IDirectDrawGammaControl, GETGAMMARAMP, GetGammaRamp, 3, HRESULT, (IDirectDrawGammaControl* self, DWORD dwFlags, DDGAMMARAMP* lpRampData))
D3D7_METHOD(IDIRECTDRAWGAMMACONTROL, IDirectDrawGammaControl, SETGAMMARAMP, SetGammaRamp, 4, HRESULT, (IDirectDrawGammaControl* self, DWORD dwFlags, const DDGAMMARAMP* lpRampData))

D3D7_INTERFACE(IDIRECTDRAW, IDirectDraw)

D3D7_IUNKNOWN_METHODS(IDIRECTDRAW, IDirectDraw)

#undef D3D7_DEVICE_METHOD
#undef D3D7_DIRECTDRAW_METHOD
#undef D3D7_IUNKNOWN_METHODS
#undef D3D7_SURFACE_METHOD
#undef D3D7_VERTEX_BUFFER_METHOD

#if defined(D3D7_INTERFACE_DEFINED_BY_METHODS_INL)
    #undef D3D7_INTERFACE
    #undef D3D7_INTERFACE_DEFINED_BY_METHODS_INL
#endif
