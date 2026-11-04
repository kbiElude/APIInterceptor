/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * A Direct3D 7 program which makes every kind of draw (user memory, strided, vertex buffer, and the indexed ones of each), windowed, for 120 frames,
 * so that there is a capture of them to replay and to analyze: data/d3d7_draw_kinds.workload is one. Strided draws take no pre-transformed vertices.
 */
#include "Common/vtable.h"
#include "Interception/Hooks/D3D7/types.h"
#include <Windows.h>
#include <stdio.h>

namespace D3D7 = Interception::Hooks::D3D7;

static const GUID IID_DD7        = {0x15e65ec0, 0x3b9c, 0x11d2, {0xb9, 0x2f, 0x00, 0x60, 0x97, 0x97, 0xea, 0x5b}};
static const GUID IID_D3D7       = {0xf5049e77, 0x4861, 0x11d2, {0xa4, 0x07, 0x00, 0xa0, 0xc9, 0x06, 0x29, 0xa8}};
static const GUID IID_HAL        = {0x84e63de0, 0x46aa, 0x11cf, {0x81, 0x6f, 0x00, 0x00, 0xc0, 0x20, 0x15, 0x6e}};
static const GUID IID_RGB        = {0xa4665c60, 0x2673, 0x11cf, {0xa3, 0x1a, 0x00, 0xaa, 0x00, 0xb9, 0x33, 0x56}};

static const DWORD FVF_XYZRHW_DIFFUSE = 0x044;
static const DWORD FVF_XYZ_DIFFUSE    = 0x042; /* strided draws take no pre-transformed vertices */

struct Vertex
{
    float x;
    float y;
    float z;
    float rhw;
    DWORD color;
};

template<typename PFN>
static PFN method(void* object, const unsigned index)
{
    return APIInterceptor::get_method_ptr<PFN>(APIInterceptor::get_vtable_ptr(object), index);
}


static Vertex make_vertex(float x, float y, DWORD color)
{
    Vertex v = {x, y, 0.5f, 1.0f, color};

    return v;
}

static void pump()
{
    MSG msg;

    while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE) )
    {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
}

int main()
{
    typedef HRESULT (WINAPI* CreateExFunc)(GUID*, void**, REFIID, void*);

    const HMODULE ddraw = LoadLibraryW(L"ddraw.dll");
    const auto    create_ex = reinterpret_cast<CreateExFunc>(GetProcAddress(ddraw, "DirectDrawCreateEx") );
    void*         dd        = nullptr;

    if (create_ex == nullptr || FAILED(create_ex(nullptr, &dd, IID_DD7, nullptr) ) )
    {
        printf("no DirectDraw 7\n");
        return 2;
    }

    WNDCLASSW wc = {};

    wc.lpfnWndProc   = DefWindowProcW;
    wc.hInstance     = GetModuleHandleW(nullptr);
    wc.lpszClassName = L"d3d7_draw_kinds";
    RegisterClassW(&wc);

    const HWND window = CreateWindowW(L"d3d7_draw_kinds", L"d3d7_draw_kinds", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 280, 300, nullptr, nullptr, wc.hInstance, nullptr);

    typedef HRESULT (__stdcall* SetCoopFunc)(void*, HWND, DWORD);
    typedef HRESULT (__stdcall* CreateSurfaceFunc)(void*, D3D7::DDSURFACEDESC2*, void**, void*);
    typedef HRESULT (__stdcall* QueryInterfaceFunc)(void*, const GUID&, void**);
    typedef HRESULT (__stdcall* CreateClipperFunc)(void*, DWORD, void**, void*);
    typedef HRESULT (__stdcall* ClipperSetHWndFunc)(void*, DWORD, HWND);
    typedef HRESULT (__stdcall* SurfaceSetClipperFunc)(void*, void*);
    typedef HRESULT (__stdcall* CreateDeviceFunc)(void*, const GUID&, void*, void**);
    typedef HRESULT (__stdcall* SetViewportFunc)(void*, const D3D7::D3DVIEWPORT7*);
    typedef HRESULT (__stdcall* CreateVBFunc)(void*, const D3D7::D3DVERTEXBUFFERDESC*, void**, DWORD);
    typedef HRESULT (__stdcall* VBLockFunc)(void*, DWORD, void**, DWORD*);
    typedef HRESULT (__stdcall* VBUnlockFunc)(void*);
    typedef HRESULT (__stdcall* SetRenderStateFunc)(void*, DWORD, DWORD);
    typedef HRESULT (__stdcall* ClearFunc)(void*, DWORD, void*, DWORD, DWORD, float, DWORD);
    typedef HRESULT (__stdcall* SceneFunc)(void*);
    typedef HRESULT (__stdcall* DrawFunc)(void*, D3D7::D3DPRIMITIVETYPE, DWORD, void*, DWORD, DWORD);
    typedef HRESULT (__stdcall* DrawIndexedFunc)(void*, D3D7::D3DPRIMITIVETYPE, DWORD, void*, DWORD, WORD*, DWORD, DWORD);
    typedef HRESULT (__stdcall* DrawStridedFunc)(void*, D3D7::D3DPRIMITIVETYPE, DWORD, D3D7::D3DDRAWPRIMITIVESTRIDEDDATA*, DWORD, DWORD);
    typedef HRESULT (__stdcall* DrawIndexedStridedFunc)(void*, D3D7::D3DPRIMITIVETYPE, DWORD, D3D7::D3DDRAWPRIMITIVESTRIDEDDATA*, DWORD, WORD*, DWORD, DWORD);
    typedef HRESULT (__stdcall* DrawVBFunc)(void*, D3D7::D3DPRIMITIVETYPE, void*, DWORD, DWORD, DWORD);
    typedef HRESULT (__stdcall* DrawIndexedVBFunc)(void*, D3D7::D3DPRIMITIVETYPE, void*, DWORD, DWORD, WORD*, DWORD, DWORD);
    typedef HRESULT (__stdcall* BltFunc)(void*, RECT*, void*, RECT*, DWORD, void*);

    method<SetCoopFunc>(dd, D3D7::VTABLE_INDEX_IDIRECTDRAW7_SETCOOPERATIVELEVEL)(dd, window, 0x8 /* DDSCL_NORMAL */);

    D3D7::DDSURFACEDESC2 desc = {};

    desc.dwSize         = sizeof(desc);
    desc.dwFlags        = 0x1; /* DDSD_CAPS */
    desc.ddsCaps.dwCaps = 0x200; /* DDSCAPS_PRIMARYSURFACE */

    void* primary = nullptr;

    if (FAILED(method<CreateSurfaceFunc>(dd, D3D7::VTABLE_INDEX_IDIRECTDRAW7_CREATESURFACE)(dd, &desc, &primary, nullptr) ) )
    {
        printf("no primary\n");
        return 3;
    }

    void* clipper = nullptr;

    method<CreateClipperFunc>(dd, D3D7::VTABLE_INDEX_IDIRECTDRAW7_CREATECLIPPER)(dd, 0, &clipper, nullptr);
    method<ClipperSetHWndFunc>(clipper, D3D7::VTABLE_INDEX_IDIRECTDRAWCLIPPER_SETHWND)(clipper, 0, window);
    method<SurfaceSetClipperFunc>(primary, D3D7::VTABLE_INDEX_IDIRECTDRAWSURFACE7_SETCLIPPER)(primary, clipper);

    D3D7::DDSURFACEDESC2 back_desc = {};

    back_desc.dwSize         = sizeof(back_desc);
    back_desc.dwFlags        = 0x1 | 0x2 | 0x4; /* DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH */
    back_desc.dwHeight       = 256;
    back_desc.dwWidth        = 256;
    back_desc.ddsCaps.dwCaps = 0x40 | 0x2000; /* DDSCAPS_OFFSCREENPLAIN | DDSCAPS_3DDEVICE */

    void* back = nullptr;

    if (FAILED(method<CreateSurfaceFunc>(dd, D3D7::VTABLE_INDEX_IDIRECTDRAW7_CREATESURFACE)(dd, &back_desc, &back, nullptr) ) )
    {
        printf("no back buffer\n");
        return 4;
    }

    void* d3d = nullptr;

    method<QueryInterfaceFunc>(dd, D3D7::VTABLE_INDEX_IDIRECTDRAW7_QUERYINTERFACE)(dd, IID_D3D7, &d3d);

    void* device = nullptr;

    if (FAILED(method<CreateDeviceFunc>(d3d, D3D7::VTABLE_INDEX_IDIRECT3D7_CREATEDEVICE)(d3d, IID_HAL, back, &device) ) &&
        FAILED(method<CreateDeviceFunc>(d3d, D3D7::VTABLE_INDEX_IDIRECT3D7_CREATEDEVICE)(d3d, IID_RGB, back, &device) ) )
    {
        printf("no device\n");
        return 5;
    }

    D3D7::D3DVIEWPORT7 viewport = {0, 0, 256, 256, 0.0f, 1.0f};

    method<SetViewportFunc>(device, D3D7::VTABLE_INDEX_IDIRECT3DDEVICE7_SETVIEWPORT)(device, &viewport);
    method<SetRenderStateFunc>(device, D3D7::VTABLE_INDEX_IDIRECT3DDEVICE7_SETRENDERSTATE)(device, 7 /* ZENABLE */, 0);
    method<SetRenderStateFunc>(device, D3D7::VTABLE_INDEX_IDIRECT3DDEVICE7_SETRENDERSTATE)(device, 22 /* CULLMODE */, 1 /* NONE */);
    method<SetRenderStateFunc>(device, D3D7::VTABLE_INDEX_IDIRECT3DDEVICE7_SETRENDERSTATE)(device, 137 /* LIGHTING */, 0);

    /* The vertex buffer: two triangles (six vertices), and indices to draw them as a list too. */
    D3D7::D3DVERTEXBUFFERDESC vb_desc = {sizeof(D3D7::D3DVERTEXBUFFERDESC), 0x800 /* SYSTEMMEMORY */, FVF_XYZRHW_DIFFUSE, 6};
    void*                     vb      = nullptr;

    if (FAILED(method<CreateVBFunc>(d3d, D3D7::VTABLE_INDEX_IDIRECT3D7_CREATEVERTEXBUFFER)(d3d, &vb_desc, &vb, 0) ) )
    {
        printf("no vertex buffer\n");
        return 6;
    }

    for (int n_frame = 0; n_frame < 120; ++n_frame)
    {
        const DWORD c0 = 0xff000000 | ((n_frame * 2) & 0xff) << 16;
        const DWORD c1 = 0xff00ff00 | ((n_frame * 3) & 0xff);
        const DWORD c2 = 0xff0000ff | ((n_frame * 5) & 0xff) << 8;

        /* The contents of the vertex buffer change every frame: one lock and one unlock. */
        void*  data = nullptr;
        DWORD  size = 0;

        method<VBLockFunc>(vb, D3D7::VTABLE_INDEX_IDIRECT3DVERTEXBUFFER7_LOCK)(vb, 0x1 /* WAIT */ | 0x20 /* WRITEONLY */, &data, &size);

        Vertex* vertices = static_cast<Vertex*>(data);

        vertices[0] = make_vertex(150.0f, 170.0f, c0);
        vertices[1] = make_vertex(230.0f, 170.0f, c1);
        vertices[2] = make_vertex(190.0f, 240.0f, c2);
        vertices[3] = make_vertex(20.0f,  170.0f, c2);
        vertices[4] = make_vertex(100.0f, 170.0f, c0);
        vertices[5] = make_vertex(60.0f,  240.0f, c1);

        method<VBUnlockFunc>(vb, D3D7::VTABLE_INDEX_IDIRECT3DVERTEXBUFFER7_UNLOCK)(vb);

        method<ClearFunc>(device, D3D7::VTABLE_INDEX_IDIRECT3DDEVICE7_CLEAR)(device, 0, nullptr, 1 /* TARGET */, 0xff101030, 1.0f, 0);
        method<SceneFunc>(device, D3D7::VTABLE_INDEX_IDIRECT3DDEVICE7_BEGINSCENE)(device);

        /* 1: user memory */
        Vertex user[3] = {make_vertex(20.0f, 10.0f, c0), make_vertex(100.0f, 10.0f, c1), make_vertex(60.0f, 70.0f, c2)};

        method<DrawFunc>(device, D3D7::VTABLE_INDEX_IDIRECT3DDEVICE7_DRAWPRIMITIVE)(device, D3D7::D3DPT_TRIANGLELIST, FVF_XYZRHW_DIFFUSE, user, 3, 0);

        /* 2: strided, positions and colors in two arrays */
        float position[3][3] = {{0.1f, 0.9f, 0.5f}, {0.9f, 0.9f, 0.5f}, {0.5f, 0.45f, 0.5f}};
        DWORD color[3]       = {c1, c2, c0};
        D3D7::D3DDRAWPRIMITIVESTRIDEDDATA strided = {};

        strided.position.lpvData = position;
        strided.position.dwStride = sizeof(position[0]);
        strided.diffuse.lpvData   = color;
        strided.diffuse.dwStride  = sizeof(color[0]);

        method<DrawStridedFunc>(device, D3D7::VTABLE_INDEX_IDIRECT3DDEVICE7_DRAWPRIMITIVESTRIDED)(device, D3D7::D3DPT_TRIANGLELIST, FVF_XYZ_DIFFUSE, &strided, 3, 0);

        /* 3: indexed and strided: a quad of two triangles by four vertices */
        float quad_position[4][3] = {{-0.9f, 0.3f, 0.5f}, {-0.1f, 0.3f, 0.5f}, {-0.1f, -0.3f, 0.5f}, {-0.9f, -0.3f, 0.5f}};
        DWORD quad_color[4]       = {c0, c1, c2, c0};
        WORD  quad_index[6]       = {0, 1, 2, 0, 2, 3};
        D3D7::D3DDRAWPRIMITIVESTRIDEDDATA quad = {};

        quad.position.lpvData = quad_position;
        quad.position.dwStride = sizeof(quad_position[0]);
        quad.diffuse.lpvData   = quad_color;
        quad.diffuse.dwStride  = sizeof(quad_color[0]);

        method<DrawIndexedStridedFunc>(device, D3D7::VTABLE_INDEX_IDIRECT3DDEVICE7_DRAWINDEXEDPRIMITIVESTRIDED)(device, D3D7::D3DPT_TRIANGLELIST, FVF_XYZ_DIFFUSE, &quad, 4, quad_index, 6, 0);

        /* 4: from the vertex buffer */
        method<DrawVBFunc>(device, D3D7::VTABLE_INDEX_IDIRECT3DDEVICE7_DRAWPRIMITIVEVB)(device, D3D7::D3DPT_TRIANGLELIST, vb, 0, 3, 0);

        /* 5: from the vertex buffer, indexed (the second triangle through indices) */
        WORD vb_index[3] = {3, 4, 5};

        method<DrawIndexedVBFunc>(device, D3D7::VTABLE_INDEX_IDIRECT3DDEVICE7_DRAWINDEXEDPRIMITIVEVB)(device, D3D7::D3DPT_TRIANGLELIST, vb, 0, 6, vb_index, 3, 0);

        method<SceneFunc>(device, D3D7::VTABLE_INDEX_IDIRECT3DDEVICE7_ENDSCENE)(device);

        RECT client = {};
        POINT origin = {0, 0};

        GetClientRect(window, &client);
        ClientToScreen(window, &origin);

        RECT destination = {origin.x, origin.y, origin.x + 256, origin.y + 256};
        RECT source      = {0, 0, 256, 256};

        method<BltFunc>(primary, D3D7::VTABLE_INDEX_IDIRECTDRAWSURFACE7_BLT)(primary, &destination, back, &source, 0x1000000 /* WAIT */, nullptr);

        pump();
        Sleep(16);
    }

    printf("done\n");

    return 0;
}
