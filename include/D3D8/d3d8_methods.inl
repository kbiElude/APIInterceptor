/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * D3D8 method table (X-macro). Before including, define:
 *   D3D8_METHOD(INTERFACE_TAG, interface_name, METHOD_TAG, method_name, vtable_index, return_type, parameters)
 *   D3D8_INTERFACE(INTERFACE_TAG, interface_name) (optional)
 *
 * Tags are upper-case; parameters start with 'self'. Methods are listed per interface, in vtable order. New interfaces
 * are appended, so that the function IDs in existing dumps stay valid. Types resolve in namespace D3D8.
 */
#if !defined(D3D8_METHOD)
    #error D3D8_METHOD must be defined before including d3d8_methods.inl
#endif

#if !defined(D3D8_INTERFACE)
    #define D3D8_INTERFACE(INTERFACE_TAG, interface_name)
    #define D3D8_INTERFACE_DEFINED_BY_METHODS_INL
#endif

/* Groups of methods shared by multiple interfaces. */
#define D3D8_IUNKNOWN_METHODS(INTERFACE_TAG, interface_name) \
    D3D8_METHOD(INTERFACE_TAG, interface_name, QUERYINTERFACE, QueryInterface, 0, HRESULT, (interface_name* self, REFIID riid, void** ppvObj)) \
    D3D8_METHOD(INTERFACE_TAG, interface_name, ADDREF,         AddRef,         1, ULONG,   (interface_name* self))                             \
    D3D8_METHOD(INTERFACE_TAG, interface_name, RELEASE,        Release,        2, ULONG,   (interface_name* self))

#define D3D8_PRIVATE_DATA_METHODS(INTERFACE_TAG, interface_name) \
    D3D8_METHOD(INTERFACE_TAG, interface_name, GETDEVICE,       GetDevice,       3, HRESULT, (interface_name* self, IDirect3DDevice8** ppDevice))                                       \
    D3D8_METHOD(INTERFACE_TAG, interface_name, SETPRIVATEDATA,  SetPrivateData,  4, HRESULT, (interface_name* self, REFGUID refguid, const void* pData, DWORD SizeOfData, DWORD Flags)) \
    D3D8_METHOD(INTERFACE_TAG, interface_name, GETPRIVATEDATA,  GetPrivateData,  5, HRESULT, (interface_name* self, REFGUID refguid, void* pData, DWORD* pSizeOfData))                  \
    D3D8_METHOD(INTERFACE_TAG, interface_name, FREEPRIVATEDATA, FreePrivateData, 6, HRESULT, (interface_name* self, REFGUID refguid))

#define D3D8_RESOURCE_METHODS(INTERFACE_TAG, interface_name) \
    D3D8_METHOD(INTERFACE_TAG, interface_name, SETPRIORITY, SetPriority, 7,  DWORD,           (interface_name* self, DWORD PriorityNew)) \
    D3D8_METHOD(INTERFACE_TAG, interface_name, GETPRIORITY, GetPriority, 8,  DWORD,           (interface_name* self))                    \
    D3D8_METHOD(INTERFACE_TAG, interface_name, PRELOAD,     PreLoad,     9,  void,            (interface_name* self))                    \
    D3D8_METHOD(INTERFACE_TAG, interface_name, GETTYPE,     GetType,     10, D3DRESOURCETYPE, (interface_name* self))

#define D3D8_BASE_TEXTURE_METHODS(INTERFACE_TAG, interface_name) \
    D3D8_METHOD(INTERFACE_TAG, interface_name, SETLOD,        SetLOD,        11, DWORD, (interface_name* self, DWORD LODNew)) \
    D3D8_METHOD(INTERFACE_TAG, interface_name, GETLOD,        GetLOD,        12, DWORD, (interface_name* self))               \
    D3D8_METHOD(INTERFACE_TAG, interface_name, GETLEVELCOUNT, GetLevelCount, 13, DWORD, (interface_name* self))

D3D8_INTERFACE(IDIRECT3D8, IDirect3D8)

D3D8_IUNKNOWN_METHODS(IDIRECT3D8, IDirect3D8)
D3D8_METHOD(IDIRECT3D8, IDirect3D8, REGISTERSOFTWAREDEVICE,     RegisterSoftwareDevice,     3,  HRESULT,  (IDirect3D8* self, void* pInitializeFunction))
D3D8_METHOD(IDIRECT3D8, IDirect3D8, GETADAPTERCOUNT,            GetAdapterCount,            4,  UINT,     (IDirect3D8* self))
D3D8_METHOD(IDIRECT3D8, IDirect3D8, GETADAPTERIDENTIFIER,       GetAdapterIdentifier,       5,  HRESULT,  (IDirect3D8* self, UINT Adapter, DWORD Flags, D3DADAPTER_IDENTIFIER8* pIdentifier))
D3D8_METHOD(IDIRECT3D8, IDirect3D8, GETADAPTERMODECOUNT,        GetAdapterModeCount,        6,  UINT,     (IDirect3D8* self, UINT Adapter))
D3D8_METHOD(IDIRECT3D8, IDirect3D8, ENUMADAPTERMODES,           EnumAdapterModes,           7,  HRESULT,  (IDirect3D8* self, UINT Adapter, UINT Mode, D3DDISPLAYMODE* pMode))
D3D8_METHOD(IDIRECT3D8, IDirect3D8, GETADAPTERDISPLAYMODE,      GetAdapterDisplayMode,      8,  HRESULT,  (IDirect3D8* self, UINT Adapter, D3DDISPLAYMODE* pMode))
D3D8_METHOD(IDIRECT3D8, IDirect3D8, CHECKDEVICETYPE,            CheckDeviceType,            9,  HRESULT,  (IDirect3D8* self, UINT Adapter, D3DDEVTYPE CheckType, D3DFORMAT DisplayFormat, D3DFORMAT BackBufferFormat, BOOL Windowed))
D3D8_METHOD(IDIRECT3D8, IDirect3D8, CHECKDEVICEFORMAT,          CheckDeviceFormat,          10, HRESULT,  (IDirect3D8* self, UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, DWORD Usage, D3DRESOURCETYPE RType, D3DFORMAT CheckFormat))
D3D8_METHOD(IDIRECT3D8, IDirect3D8, CHECKDEVICEMULTISAMPLETYPE, CheckDeviceMultiSampleType, 11, HRESULT,  (IDirect3D8* self, UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT SurfaceFormat, BOOL Windowed, D3DMULTISAMPLE_TYPE MultiSampleType))
D3D8_METHOD(IDIRECT3D8, IDirect3D8, CHECKDEPTHSTENCILMATCH,     CheckDepthStencilMatch,     12, HRESULT,  (IDirect3D8* self, UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, D3DFORMAT RenderTargetFormat, D3DFORMAT DepthStencilFormat))
D3D8_METHOD(IDIRECT3D8, IDirect3D8, GETDEVICECAPS,              GetDeviceCaps,              13, HRESULT,  (IDirect3D8* self, UINT Adapter, D3DDEVTYPE DeviceType, D3DCAPS8* pCaps))
D3D8_METHOD(IDIRECT3D8, IDirect3D8, GETADAPTERMONITOR,          GetAdapterMonitor,          14, HMONITOR, (IDirect3D8* self, UINT Adapter))
D3D8_METHOD(IDIRECT3D8, IDirect3D8, CREATEDEVICE,               CreateDevice,               15, HRESULT,  (IDirect3D8* self, UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS* pPresentationParameters, IDirect3DDevice8** ppReturnedDeviceInterface))

#define D3D8_DEVICE_METHOD(METHOD_TAG, method_name, vtable_index, return_type, parameters) \
    D3D8_METHOD(IDIRECT3DDEVICE8, IDirect3DDevice8, METHOD_TAG, method_name, vtable_index, return_type, parameters)

D3D8_INTERFACE(IDIRECT3DDEVICE8, IDirect3DDevice8)

D3D8_IUNKNOWN_METHODS(IDIRECT3DDEVICE8, IDirect3DDevice8)
D3D8_DEVICE_METHOD(TESTCOOPERATIVELEVEL,        TestCooperativeLevel,        3,  HRESULT, (IDirect3DDevice8* self))
D3D8_DEVICE_METHOD(GETAVAILABLETEXTUREMEM,      GetAvailableTextureMem,      4,  UINT,    (IDirect3DDevice8* self))
D3D8_DEVICE_METHOD(RESOURCEMANAGERDISCARDBYTES, ResourceManagerDiscardBytes, 5,  HRESULT, (IDirect3DDevice8* self, DWORD Bytes))
D3D8_DEVICE_METHOD(GETDIRECT3D,                 GetDirect3D,                 6,  HRESULT, (IDirect3DDevice8* self, IDirect3D8** ppD3D8))
D3D8_DEVICE_METHOD(GETDEVICECAPS,               GetDeviceCaps,               7,  HRESULT, (IDirect3DDevice8* self, D3DCAPS8* pCaps))
D3D8_DEVICE_METHOD(GETDISPLAYMODE,              GetDisplayMode,              8,  HRESULT, (IDirect3DDevice8* self, D3DDISPLAYMODE* pMode))
D3D8_DEVICE_METHOD(GETCREATIONPARAMETERS,       GetCreationParameters,       9,  HRESULT, (IDirect3DDevice8* self, D3DDEVICE_CREATION_PARAMETERS* pParameters))
D3D8_DEVICE_METHOD(SETCURSORPROPERTIES,         SetCursorProperties,         10, HRESULT, (IDirect3DDevice8* self, UINT XHotSpot, UINT YHotSpot, IDirect3DSurface8* pCursorBitmap))
D3D8_DEVICE_METHOD(SETCURSORPOSITION,           SetCursorPosition,           11, void,    (IDirect3DDevice8* self, UINT XScreenSpace, UINT YScreenSpace, DWORD Flags))
D3D8_DEVICE_METHOD(SHOWCURSOR,                  ShowCursor,                  12, BOOL,    (IDirect3DDevice8* self, BOOL bShow))
D3D8_DEVICE_METHOD(CREATEADDITIONALSWAPCHAIN,   CreateAdditionalSwapChain,   13, HRESULT, (IDirect3DDevice8* self, D3DPRESENT_PARAMETERS* pPresentationParameters, IDirect3DSwapChain8** pSwapChain))
D3D8_DEVICE_METHOD(RESET,                       Reset,                       14, HRESULT, (IDirect3DDevice8* self, D3DPRESENT_PARAMETERS* pPresentationParameters))
D3D8_DEVICE_METHOD(PRESENT,                     Present,                     15, HRESULT, (IDirect3DDevice8* self, const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const RGNDATA* pDirtyRegion))
D3D8_DEVICE_METHOD(GETBACKBUFFER,               GetBackBuffer,               16, HRESULT, (IDirect3DDevice8* self, UINT BackBuffer, D3DBACKBUFFER_TYPE Type, IDirect3DSurface8** ppBackBuffer))
D3D8_DEVICE_METHOD(GETRASTERSTATUS,             GetRasterStatus,             17, HRESULT, (IDirect3DDevice8* self, D3DRASTER_STATUS* pRasterStatus))
D3D8_DEVICE_METHOD(SETGAMMARAMP,                SetGammaRamp,                18, void,    (IDirect3DDevice8* self, DWORD Flags, const D3DGAMMARAMP* pRamp))
D3D8_DEVICE_METHOD(GETGAMMARAMP,                GetGammaRamp,                19, void,    (IDirect3DDevice8* self, D3DGAMMARAMP* pRamp))
D3D8_DEVICE_METHOD(CREATETEXTURE,               CreateTexture,               20, HRESULT, (IDirect3DDevice8* self, UINT Width, UINT Height, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DTexture8** ppTexture))
D3D8_DEVICE_METHOD(CREATEVOLUMETEXTURE,         CreateVolumeTexture,         21, HRESULT, (IDirect3DDevice8* self, UINT Width, UINT Height, UINT Depth, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DVolumeTexture8** ppVolumeTexture))
D3D8_DEVICE_METHOD(CREATECUBETEXTURE,           CreateCubeTexture,           22, HRESULT, (IDirect3DDevice8* self, UINT EdgeLength, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DCubeTexture8** ppCubeTexture))
D3D8_DEVICE_METHOD(CREATEVERTEXBUFFER,          CreateVertexBuffer,          23, HRESULT, (IDirect3DDevice8* self, UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool, IDirect3DVertexBuffer8** ppVertexBuffer))
D3D8_DEVICE_METHOD(CREATEINDEXBUFFER,           CreateIndexBuffer,           24, HRESULT, (IDirect3DDevice8* self, UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DIndexBuffer8** ppIndexBuffer))
D3D8_DEVICE_METHOD(CREATERENDERTARGET,          CreateRenderTarget,          25, HRESULT, (IDirect3DDevice8* self, UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, BOOL Lockable, IDirect3DSurface8** ppSurface))
D3D8_DEVICE_METHOD(CREATEDEPTHSTENCILSURFACE,   CreateDepthStencilSurface,   26, HRESULT, (IDirect3DDevice8* self, UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, IDirect3DSurface8** ppSurface))
D3D8_DEVICE_METHOD(CREATEIMAGESURFACE,          CreateImageSurface,          27, HRESULT, (IDirect3DDevice8* self, UINT Width, UINT Height, D3DFORMAT Format, IDirect3DSurface8** ppSurface))
D3D8_DEVICE_METHOD(COPYRECTS,                   CopyRects,                   28, HRESULT, (IDirect3DDevice8* self, IDirect3DSurface8* pSourceSurface, const RECT* pSourceRectsArray, UINT cRects, IDirect3DSurface8* pDestinationSurface, const POINT* pDestPointsArray))
D3D8_DEVICE_METHOD(UPDATETEXTURE,               UpdateTexture,               29, HRESULT, (IDirect3DDevice8* self, IDirect3DBaseTexture8* pSourceTexture, IDirect3DBaseTexture8* pDestinationTexture))
D3D8_DEVICE_METHOD(GETFRONTBUFFER,              GetFrontBuffer,              30, HRESULT, (IDirect3DDevice8* self, IDirect3DSurface8* pDestSurface))
D3D8_DEVICE_METHOD(SETRENDERTARGET,             SetRenderTarget,             31, HRESULT, (IDirect3DDevice8* self, IDirect3DSurface8* pRenderTarget, IDirect3DSurface8* pNewZStencil))
D3D8_DEVICE_METHOD(GETRENDERTARGET,             GetRenderTarget,             32, HRESULT, (IDirect3DDevice8* self, IDirect3DSurface8** ppRenderTarget))
D3D8_DEVICE_METHOD(GETDEPTHSTENCILSURFACE,      GetDepthStencilSurface,      33, HRESULT, (IDirect3DDevice8* self, IDirect3DSurface8** ppZStencilSurface))
D3D8_DEVICE_METHOD(BEGINSCENE,                  BeginScene,                  34, HRESULT, (IDirect3DDevice8* self))
D3D8_DEVICE_METHOD(ENDSCENE,                    EndScene,                    35, HRESULT, (IDirect3DDevice8* self))
D3D8_DEVICE_METHOD(CLEAR,                       Clear,                       36, HRESULT, (IDirect3DDevice8* self, DWORD Count, const D3DRECT* pRects, DWORD Flags, D3DCOLOR Color, float Z, DWORD Stencil))
D3D8_DEVICE_METHOD(SETTRANSFORM,                SetTransform,                37, HRESULT, (IDirect3DDevice8* self, D3DTRANSFORMSTATETYPE State, const D3DMATRIX* pMatrix))
D3D8_DEVICE_METHOD(GETTRANSFORM,                GetTransform,                38, HRESULT, (IDirect3DDevice8* self, D3DTRANSFORMSTATETYPE State, D3DMATRIX* pMatrix))
D3D8_DEVICE_METHOD(MULTIPLYTRANSFORM,           MultiplyTransform,           39, HRESULT, (IDirect3DDevice8* self, D3DTRANSFORMSTATETYPE State, const D3DMATRIX* pMatrix))
D3D8_DEVICE_METHOD(SETVIEWPORT,                 SetViewport,                 40, HRESULT, (IDirect3DDevice8* self, const D3DVIEWPORT8* pViewport))
D3D8_DEVICE_METHOD(GETVIEWPORT,                 GetViewport,                 41, HRESULT, (IDirect3DDevice8* self, D3DVIEWPORT8* pViewport))
D3D8_DEVICE_METHOD(SETMATERIAL,                 SetMaterial,                 42, HRESULT, (IDirect3DDevice8* self, const D3DMATERIAL8* pMaterial))
D3D8_DEVICE_METHOD(GETMATERIAL,                 GetMaterial,                 43, HRESULT, (IDirect3DDevice8* self, D3DMATERIAL8* pMaterial))
D3D8_DEVICE_METHOD(SETLIGHT,                    SetLight,                    44, HRESULT, (IDirect3DDevice8* self, DWORD Index, const D3DLIGHT8* pLight))
D3D8_DEVICE_METHOD(GETLIGHT,                    GetLight,                    45, HRESULT, (IDirect3DDevice8* self, DWORD Index, D3DLIGHT8* pLight))
D3D8_DEVICE_METHOD(LIGHTENABLE,                 LightEnable,                 46, HRESULT, (IDirect3DDevice8* self, DWORD Index, BOOL Enable))
D3D8_DEVICE_METHOD(GETLIGHTENABLE,              GetLightEnable,              47, HRESULT, (IDirect3DDevice8* self, DWORD Index, BOOL* pEnable))
D3D8_DEVICE_METHOD(SETCLIPPLANE,                SetClipPlane,                48, HRESULT, (IDirect3DDevice8* self, DWORD Index, const float* pPlane))
D3D8_DEVICE_METHOD(GETCLIPPLANE,                GetClipPlane,                49, HRESULT, (IDirect3DDevice8* self, DWORD Index, float* pPlane))
D3D8_DEVICE_METHOD(SETRENDERSTATE,              SetRenderState,              50, HRESULT, (IDirect3DDevice8* self, D3DRENDERSTATETYPE State, DWORD Value))
D3D8_DEVICE_METHOD(GETRENDERSTATE,              GetRenderState,              51, HRESULT, (IDirect3DDevice8* self, D3DRENDERSTATETYPE State, DWORD* pValue))
D3D8_DEVICE_METHOD(BEGINSTATEBLOCK,             BeginStateBlock,             52, HRESULT, (IDirect3DDevice8* self))
D3D8_DEVICE_METHOD(ENDSTATEBLOCK,               EndStateBlock,               53, HRESULT, (IDirect3DDevice8* self, DWORD* pToken))
D3D8_DEVICE_METHOD(APPLYSTATEBLOCK,             ApplyStateBlock,             54, HRESULT, (IDirect3DDevice8* self, DWORD Token))
D3D8_DEVICE_METHOD(CAPTURESTATEBLOCK,           CaptureStateBlock,           55, HRESULT, (IDirect3DDevice8* self, DWORD Token))
D3D8_DEVICE_METHOD(DELETESTATEBLOCK,            DeleteStateBlock,            56, HRESULT, (IDirect3DDevice8* self, DWORD Token))
D3D8_DEVICE_METHOD(CREATESTATEBLOCK,            CreateStateBlock,            57, HRESULT, (IDirect3DDevice8* self, D3DSTATEBLOCKTYPE Type, DWORD* pToken))
D3D8_DEVICE_METHOD(SETCLIPSTATUS,               SetClipStatus,               58, HRESULT, (IDirect3DDevice8* self, const D3DCLIPSTATUS8* pClipStatus))
D3D8_DEVICE_METHOD(GETCLIPSTATUS,               GetClipStatus,               59, HRESULT, (IDirect3DDevice8* self, D3DCLIPSTATUS8* pClipStatus))
D3D8_DEVICE_METHOD(GETTEXTURE,                  GetTexture,                  60, HRESULT, (IDirect3DDevice8* self, DWORD Stage, IDirect3DBaseTexture8** ppTexture))
D3D8_DEVICE_METHOD(SETTEXTURE,                  SetTexture,                  61, HRESULT, (IDirect3DDevice8* self, DWORD Stage, IDirect3DBaseTexture8* pTexture))
D3D8_DEVICE_METHOD(GETTEXTURESTAGESTATE,        GetTextureStageState,        62, HRESULT, (IDirect3DDevice8* self, DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD* pValue))
D3D8_DEVICE_METHOD(SETTEXTURESTAGESTATE,        SetTextureStageState,        63, HRESULT, (IDirect3DDevice8* self, DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD Value))
D3D8_DEVICE_METHOD(VALIDATEDEVICE,              ValidateDevice,              64, HRESULT, (IDirect3DDevice8* self, DWORD* pNumPasses))
D3D8_DEVICE_METHOD(GETINFO,                     GetInfo,                     65, HRESULT, (IDirect3DDevice8* self, DWORD DevInfoID, void* pDevInfoStruct, DWORD DevInfoStructSize))
D3D8_DEVICE_METHOD(SETPALETTEENTRIES,           SetPaletteEntries,           66, HRESULT, (IDirect3DDevice8* self, UINT PaletteNumber, const PALETTEENTRY* pEntries))
D3D8_DEVICE_METHOD(GETPALETTEENTRIES,           GetPaletteEntries,           67, HRESULT, (IDirect3DDevice8* self, UINT PaletteNumber, PALETTEENTRY* pEntries))
D3D8_DEVICE_METHOD(SETCURRENTTEXTUREPALETTE,    SetCurrentTexturePalette,    68, HRESULT, (IDirect3DDevice8* self, UINT PaletteNumber))
D3D8_DEVICE_METHOD(GETCURRENTTEXTUREPALETTE,    GetCurrentTexturePalette,    69, HRESULT, (IDirect3DDevice8* self, UINT* PaletteNumber))
D3D8_DEVICE_METHOD(DRAWPRIMITIVE,               DrawPrimitive,               70, HRESULT, (IDirect3DDevice8* self, D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount))
D3D8_DEVICE_METHOD(DRAWINDEXEDPRIMITIVE,        DrawIndexedPrimitive,        71, HRESULT, (IDirect3DDevice8* self, D3DPRIMITIVETYPE PrimitiveType, UINT MinIndex, UINT NumVertices, UINT StartIndex, UINT PrimitiveCount))
D3D8_DEVICE_METHOD(DRAWPRIMITIVEUP,             DrawPrimitiveUP,             72, HRESULT, (IDirect3DDevice8* self, D3DPRIMITIVETYPE PrimitiveType, UINT PrimitiveCount, const void* pVertexStreamZeroData, UINT VertexStreamZeroStride))
D3D8_DEVICE_METHOD(DRAWINDEXEDPRIMITIVEUP,      DrawIndexedPrimitiveUP,      73, HRESULT, (IDirect3DDevice8* self, D3DPRIMITIVETYPE PrimitiveType, UINT MinVertexIndex, UINT NumVertexIndices, UINT PrimitiveCount, const void* pIndexData, D3DFORMAT IndexDataFormat, const void* pVertexStreamZeroData, UINT VertexStreamZeroStride))
D3D8_DEVICE_METHOD(PROCESSVERTICES,             ProcessVertices,             74, HRESULT, (IDirect3DDevice8* self, UINT SrcStartIndex, UINT DestIndex, UINT VertexCount, IDirect3DVertexBuffer8* pDestBuffer, DWORD Flags))
D3D8_DEVICE_METHOD(CREATEVERTEXSHADER,          CreateVertexShader,          75, HRESULT, (IDirect3DDevice8* self, const DWORD* pDeclaration, const DWORD* pFunction, DWORD* pHandle, DWORD Usage))
D3D8_DEVICE_METHOD(SETVERTEXSHADER,             SetVertexShader,             76, HRESULT, (IDirect3DDevice8* self, DWORD Handle))
D3D8_DEVICE_METHOD(GETVERTEXSHADER,             GetVertexShader,             77, HRESULT, (IDirect3DDevice8* self, DWORD* pHandle))
D3D8_DEVICE_METHOD(DELETEVERTEXSHADER,          DeleteVertexShader,          78, HRESULT, (IDirect3DDevice8* self, DWORD Handle))
D3D8_DEVICE_METHOD(SETVERTEXSHADERCONSTANT,     SetVertexShaderConstant,     79, HRESULT, (IDirect3DDevice8* self, DWORD Register, const void* pConstantData, DWORD ConstantCount))
D3D8_DEVICE_METHOD(GETVERTEXSHADERCONSTANT,     GetVertexShaderConstant,     80, HRESULT, (IDirect3DDevice8* self, DWORD Register, void* pConstantData, DWORD ConstantCount))
D3D8_DEVICE_METHOD(GETVERTEXSHADERDECLARATION,  GetVertexShaderDeclaration,  81, HRESULT, (IDirect3DDevice8* self, DWORD Handle, void* pData, DWORD* pSizeOfData))
D3D8_DEVICE_METHOD(GETVERTEXSHADERFUNCTION,     GetVertexShaderFunction,     82, HRESULT, (IDirect3DDevice8* self, DWORD Handle, void* pData, DWORD* pSizeOfData))
D3D8_DEVICE_METHOD(SETSTREAMSOURCE,             SetStreamSource,             83, HRESULT, (IDirect3DDevice8* self, UINT StreamNumber, IDirect3DVertexBuffer8* pStreamData, UINT Stride))
D3D8_DEVICE_METHOD(GETSTREAMSOURCE,             GetStreamSource,             84, HRESULT, (IDirect3DDevice8* self, UINT StreamNumber, IDirect3DVertexBuffer8** ppStreamData, UINT* pStride))
D3D8_DEVICE_METHOD(SETINDICES,                  SetIndices,                  85, HRESULT, (IDirect3DDevice8* self, IDirect3DIndexBuffer8* pIndexData, UINT BaseVertexIndex))
D3D8_DEVICE_METHOD(GETINDICES,                  GetIndices,                  86, HRESULT, (IDirect3DDevice8* self, IDirect3DIndexBuffer8** ppIndexData, UINT* pBaseVertexIndex))
D3D8_DEVICE_METHOD(CREATEPIXELSHADER,           CreatePixelShader,           87, HRESULT, (IDirect3DDevice8* self, const DWORD* pFunction, DWORD* pHandle))
D3D8_DEVICE_METHOD(SETPIXELSHADER,              SetPixelShader,              88, HRESULT, (IDirect3DDevice8* self, DWORD Handle))
D3D8_DEVICE_METHOD(GETPIXELSHADER,              GetPixelShader,              89, HRESULT, (IDirect3DDevice8* self, DWORD* pHandle))
D3D8_DEVICE_METHOD(DELETEPIXELSHADER,           DeletePixelShader,           90, HRESULT, (IDirect3DDevice8* self, DWORD Handle))
D3D8_DEVICE_METHOD(SETPIXELSHADERCONSTANT,      SetPixelShaderConstant,      91, HRESULT, (IDirect3DDevice8* self, DWORD Register, const void* pConstantData, DWORD ConstantCount))
D3D8_DEVICE_METHOD(GETPIXELSHADERCONSTANT,      GetPixelShaderConstant,      92, HRESULT, (IDirect3DDevice8* self, DWORD Register, void* pConstantData, DWORD ConstantCount))
D3D8_DEVICE_METHOD(GETPIXELSHADERFUNCTION,      GetPixelShaderFunction,      93, HRESULT, (IDirect3DDevice8* self, DWORD Handle, void* pData, DWORD* pSizeOfData))
D3D8_DEVICE_METHOD(DRAWRECTPATCH,               DrawRectPatch,               94, HRESULT, (IDirect3DDevice8* self, UINT Handle, const float* pNumSegs, const D3DRECTPATCH_INFO* pRectPatchInfo))
D3D8_DEVICE_METHOD(DRAWTRIPATCH,                DrawTriPatch,                95, HRESULT, (IDirect3DDevice8* self, UINT Handle, const float* pNumSegs, const D3DTRIPATCH_INFO* pTriPatchInfo))
D3D8_DEVICE_METHOD(DELETEPATCH,                 DeletePatch,                 96, HRESULT, (IDirect3DDevice8* self, UINT Handle))

#undef D3D8_DEVICE_METHOD

D3D8_INTERFACE(IDIRECT3DINDEXBUFFER8, IDirect3DIndexBuffer8)

D3D8_IUNKNOWN_METHODS    (IDIRECT3DINDEXBUFFER8, IDirect3DIndexBuffer8)
D3D8_PRIVATE_DATA_METHODS(IDIRECT3DINDEXBUFFER8, IDirect3DIndexBuffer8)
D3D8_RESOURCE_METHODS    (IDIRECT3DINDEXBUFFER8, IDirect3DIndexBuffer8)
D3D8_METHOD(IDIRECT3DINDEXBUFFER8, IDirect3DIndexBuffer8, LOCK,    Lock,    11, HRESULT, (IDirect3DIndexBuffer8* self, UINT OffsetToLock, UINT SizeToLock, BYTE** ppbData, DWORD Flags))
D3D8_METHOD(IDIRECT3DINDEXBUFFER8, IDirect3DIndexBuffer8, UNLOCK,  Unlock,  12, HRESULT, (IDirect3DIndexBuffer8* self))
D3D8_METHOD(IDIRECT3DINDEXBUFFER8, IDirect3DIndexBuffer8, GETDESC, GetDesc, 13, HRESULT, (IDirect3DIndexBuffer8* self, D3DINDEXBUFFER_DESC* pDesc))

D3D8_INTERFACE(IDIRECT3DSURFACE8, IDirect3DSurface8)

D3D8_IUNKNOWN_METHODS    (IDIRECT3DSURFACE8, IDirect3DSurface8)
D3D8_PRIVATE_DATA_METHODS(IDIRECT3DSURFACE8, IDirect3DSurface8)
D3D8_METHOD(IDIRECT3DSURFACE8, IDirect3DSurface8, GETCONTAINER, GetContainer, 7,  HRESULT, (IDirect3DSurface8* self, REFIID riid, void** ppContainer))
D3D8_METHOD(IDIRECT3DSURFACE8, IDirect3DSurface8, GETDESC,      GetDesc,      8,  HRESULT, (IDirect3DSurface8* self, D3DSURFACE_DESC* pDesc))
D3D8_METHOD(IDIRECT3DSURFACE8, IDirect3DSurface8, LOCKRECT,     LockRect,     9,  HRESULT, (IDirect3DSurface8* self, D3DLOCKED_RECT* pLockedRect, const RECT* pRect, DWORD Flags))
D3D8_METHOD(IDIRECT3DSURFACE8, IDirect3DSurface8, UNLOCKRECT,   UnlockRect,   10, HRESULT, (IDirect3DSurface8* self))

D3D8_INTERFACE(IDIRECT3DSWAPCHAIN8, IDirect3DSwapChain8)

D3D8_IUNKNOWN_METHODS(IDIRECT3DSWAPCHAIN8, IDirect3DSwapChain8)
D3D8_METHOD(IDIRECT3DSWAPCHAIN8, IDirect3DSwapChain8, PRESENT,       Present,       3, HRESULT, (IDirect3DSwapChain8* self, const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const RGNDATA* pDirtyRegion))
D3D8_METHOD(IDIRECT3DSWAPCHAIN8, IDirect3DSwapChain8, GETBACKBUFFER, GetBackBuffer, 4, HRESULT, (IDirect3DSwapChain8* self, UINT BackBuffer, D3DBACKBUFFER_TYPE Type, IDirect3DSurface8** ppBackBuffer))

D3D8_INTERFACE(IDIRECT3DTEXTURE8, IDirect3DTexture8)

D3D8_IUNKNOWN_METHODS    (IDIRECT3DTEXTURE8, IDirect3DTexture8)
D3D8_PRIVATE_DATA_METHODS(IDIRECT3DTEXTURE8, IDirect3DTexture8)
D3D8_RESOURCE_METHODS    (IDIRECT3DTEXTURE8, IDirect3DTexture8)
D3D8_BASE_TEXTURE_METHODS(IDIRECT3DTEXTURE8, IDirect3DTexture8)
D3D8_METHOD(IDIRECT3DTEXTURE8, IDirect3DTexture8, GETLEVELDESC,    GetLevelDesc,    14, HRESULT, (IDirect3DTexture8* self, UINT Level, D3DSURFACE_DESC* pDesc))
D3D8_METHOD(IDIRECT3DTEXTURE8, IDirect3DTexture8, GETSURFACELEVEL, GetSurfaceLevel, 15, HRESULT, (IDirect3DTexture8* self, UINT Level, IDirect3DSurface8** ppSurfaceLevel))
D3D8_METHOD(IDIRECT3DTEXTURE8, IDirect3DTexture8, LOCKRECT,        LockRect,        16, HRESULT, (IDirect3DTexture8* self, UINT Level, D3DLOCKED_RECT* pLockedRect, const RECT* pRect, DWORD Flags))
D3D8_METHOD(IDIRECT3DTEXTURE8, IDirect3DTexture8, UNLOCKRECT,      UnlockRect,      17, HRESULT, (IDirect3DTexture8* self, UINT Level))
D3D8_METHOD(IDIRECT3DTEXTURE8, IDirect3DTexture8, ADDDIRTYRECT,    AddDirtyRect,    18, HRESULT, (IDirect3DTexture8* self, const RECT* pDirtyRect))

D3D8_INTERFACE(IDIRECT3DVERTEXBUFFER8, IDirect3DVertexBuffer8)

D3D8_IUNKNOWN_METHODS    (IDIRECT3DVERTEXBUFFER8, IDirect3DVertexBuffer8)
D3D8_PRIVATE_DATA_METHODS(IDIRECT3DVERTEXBUFFER8, IDirect3DVertexBuffer8)
D3D8_RESOURCE_METHODS    (IDIRECT3DVERTEXBUFFER8, IDirect3DVertexBuffer8)
D3D8_METHOD(IDIRECT3DVERTEXBUFFER8, IDirect3DVertexBuffer8, LOCK,    Lock,    11, HRESULT, (IDirect3DVertexBuffer8* self, UINT OffsetToLock, UINT SizeToLock, BYTE** ppbData, DWORD Flags))
D3D8_METHOD(IDIRECT3DVERTEXBUFFER8, IDirect3DVertexBuffer8, UNLOCK,  Unlock,  12, HRESULT, (IDirect3DVertexBuffer8* self))
D3D8_METHOD(IDIRECT3DVERTEXBUFFER8, IDirect3DVertexBuffer8, GETDESC, GetDesc, 13, HRESULT, (IDirect3DVertexBuffer8* self, D3DVERTEXBUFFER_DESC* pDesc))

D3D8_INTERFACE(IDIRECT3DCUBETEXTURE8, IDirect3DCubeTexture8)

D3D8_IUNKNOWN_METHODS    (IDIRECT3DCUBETEXTURE8, IDirect3DCubeTexture8)
D3D8_PRIVATE_DATA_METHODS(IDIRECT3DCUBETEXTURE8, IDirect3DCubeTexture8)
D3D8_RESOURCE_METHODS    (IDIRECT3DCUBETEXTURE8, IDirect3DCubeTexture8)
D3D8_BASE_TEXTURE_METHODS(IDIRECT3DCUBETEXTURE8, IDirect3DCubeTexture8)
D3D8_METHOD(IDIRECT3DCUBETEXTURE8, IDirect3DCubeTexture8, GETLEVELDESC,     GetLevelDesc,     14, HRESULT, (IDirect3DCubeTexture8* self, UINT Level, D3DSURFACE_DESC* pDesc))
D3D8_METHOD(IDIRECT3DCUBETEXTURE8, IDirect3DCubeTexture8, GETCUBEMAPSURFACE, GetCubeMapSurface, 15, HRESULT, (IDirect3DCubeTexture8* self, D3DCUBEMAP_FACES FaceType, UINT Level, IDirect3DSurface8** ppCubeMapSurface))
D3D8_METHOD(IDIRECT3DCUBETEXTURE8, IDirect3DCubeTexture8, LOCKRECT,         LockRect,         16, HRESULT, (IDirect3DCubeTexture8* self, D3DCUBEMAP_FACES FaceType, UINT Level, D3DLOCKED_RECT* pLockedRect, const RECT* pRect, DWORD Flags))
D3D8_METHOD(IDIRECT3DCUBETEXTURE8, IDirect3DCubeTexture8, UNLOCKRECT,       UnlockRect,       17, HRESULT, (IDirect3DCubeTexture8* self, D3DCUBEMAP_FACES FaceType, UINT Level))
D3D8_METHOD(IDIRECT3DCUBETEXTURE8, IDirect3DCubeTexture8, ADDDIRTYRECT,     AddDirtyRect,     18, HRESULT, (IDirect3DCubeTexture8* self, D3DCUBEMAP_FACES FaceType, const RECT* pDirtyRect))

D3D8_INTERFACE(IDIRECT3DVOLUME8, IDirect3DVolume8)

D3D8_IUNKNOWN_METHODS    (IDIRECT3DVOLUME8, IDirect3DVolume8)
D3D8_PRIVATE_DATA_METHODS(IDIRECT3DVOLUME8, IDirect3DVolume8)
D3D8_METHOD(IDIRECT3DVOLUME8, IDirect3DVolume8, GETCONTAINER, GetContainer, 7,  HRESULT, (IDirect3DVolume8* self, REFIID riid, void** ppContainer))
D3D8_METHOD(IDIRECT3DVOLUME8, IDirect3DVolume8, GETDESC,      GetDesc,      8,  HRESULT, (IDirect3DVolume8* self, D3DVOLUME_DESC* pDesc))
D3D8_METHOD(IDIRECT3DVOLUME8, IDirect3DVolume8, LOCKBOX,      LockBox,      9,  HRESULT, (IDirect3DVolume8* self, D3DLOCKED_BOX* pLockedVolume, const D3DBOX* pBox, DWORD Flags))
D3D8_METHOD(IDIRECT3DVOLUME8, IDirect3DVolume8, UNLOCKBOX,    UnlockBox,    10, HRESULT, (IDirect3DVolume8* self))

D3D8_INTERFACE(IDIRECT3DVOLUMETEXTURE8, IDirect3DVolumeTexture8)

D3D8_IUNKNOWN_METHODS    (IDIRECT3DVOLUMETEXTURE8, IDirect3DVolumeTexture8)
D3D8_PRIVATE_DATA_METHODS(IDIRECT3DVOLUMETEXTURE8, IDirect3DVolumeTexture8)
D3D8_RESOURCE_METHODS    (IDIRECT3DVOLUMETEXTURE8, IDirect3DVolumeTexture8)
D3D8_BASE_TEXTURE_METHODS(IDIRECT3DVOLUMETEXTURE8, IDirect3DVolumeTexture8)
D3D8_METHOD(IDIRECT3DVOLUMETEXTURE8, IDirect3DVolumeTexture8, GETLEVELDESC,  GetLevelDesc,  14, HRESULT, (IDirect3DVolumeTexture8* self, UINT Level, D3DVOLUME_DESC* pDesc))
D3D8_METHOD(IDIRECT3DVOLUMETEXTURE8, IDirect3DVolumeTexture8, GETVOLUMELEVEL, GetVolumeLevel, 15, HRESULT, (IDirect3DVolumeTexture8* self, UINT Level, IDirect3DVolume8** ppVolumeLevel))
D3D8_METHOD(IDIRECT3DVOLUMETEXTURE8, IDirect3DVolumeTexture8, LOCKBOX,       LockBox,       16, HRESULT, (IDirect3DVolumeTexture8* self, UINT Level, D3DLOCKED_BOX* pLockedVolume, const D3DBOX* pBox, DWORD Flags))
D3D8_METHOD(IDIRECT3DVOLUMETEXTURE8, IDirect3DVolumeTexture8, UNLOCKBOX,     UnlockBox,     17, HRESULT, (IDirect3DVolumeTexture8* self, UINT Level))
D3D8_METHOD(IDIRECT3DVOLUMETEXTURE8, IDirect3DVolumeTexture8, ADDDIRTYBOX,   AddDirtyBox,   18, HRESULT, (IDirect3DVolumeTexture8* self, const D3DBOX* pDirtyBox))

#undef D3D8_BASE_TEXTURE_METHODS
#undef D3D8_IUNKNOWN_METHODS
#undef D3D8_PRIVATE_DATA_METHODS
#undef D3D8_RESOURCE_METHODS

#if defined(D3D8_INTERFACE_DEFINED_BY_METHODS_INL)
    #undef D3D8_INTERFACE
    #undef D3D8_INTERFACE_DEFINED_BY_METHODS_INL
#endif
