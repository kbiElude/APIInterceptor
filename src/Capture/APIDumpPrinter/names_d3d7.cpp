/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/macros.h"
#include "d3d7_names.h"
#include "shared_names.h"

#define D3D7_FLAG(name, value)  {static_cast<uint32_t>(value), #name}
#define D3D7_TABLE(array)       array, static_cast<uint32_t>(sizeof(array) / sizeof(array[0]) )

bool Capture::APIDumpPrinter::D3D7Names::get_flag_name_table(const D3D7FlagTable& in_table,
                                                             const FlagNameEntry** out_table_ptr_ptr,
                                                             uint32_t*             out_n_entries_ptr)
{
    static const FlagNameEntry blt_flag_name_array[] =
    {
        D3D7_FLAG(DDBLT_ALPHADEST,                 0x00000001),
        D3D7_FLAG(DDBLT_ALPHADESTCONSTOVERRIDE,    0x00000002),
        D3D7_FLAG(DDBLT_ALPHADESTNEG,              0x00000004),
        D3D7_FLAG(DDBLT_ALPHADESTSURFACEOVERRIDE,  0x00000008),
        D3D7_FLAG(DDBLT_ALPHAEDGEBLEND,            0x00000010),
        D3D7_FLAG(DDBLT_ALPHASRC,                  0x00000020),
        D3D7_FLAG(DDBLT_ALPHASRCCONSTOVERRIDE,     0x00000040),
        D3D7_FLAG(DDBLT_ALPHASRCNEG,               0x00000080),
        D3D7_FLAG(DDBLT_ALPHASRCSURFACEOVERRIDE,   0x00000100),
        D3D7_FLAG(DDBLT_ASYNC,                     0x00000200),
        D3D7_FLAG(DDBLT_COLORFILL,                 0x00000400),
        D3D7_FLAG(DDBLT_DDFX,                      0x00000800),
        D3D7_FLAG(DDBLT_DDROPS,                    0x00001000),
        D3D7_FLAG(DDBLT_KEYDEST,                   0x00002000),
        D3D7_FLAG(DDBLT_KEYDESTOVERRIDE,           0x00004000),
        D3D7_FLAG(DDBLT_KEYSRC,                    0x00008000),
        D3D7_FLAG(DDBLT_KEYSRCOVERRIDE,            0x00010000),
        D3D7_FLAG(DDBLT_ROP,                       0x00020000),
        D3D7_FLAG(DDBLT_ROTATIONANGLE,             0x00040000),
        D3D7_FLAG(DDBLT_ZBUFFER,                   0x00080000),
        D3D7_FLAG(DDBLT_ZBUFFERDESTCONSTOVERRIDE,  0x00100000),
        D3D7_FLAG(DDBLT_ZBUFFERDESTOVERRIDE,       0x00200000),
        D3D7_FLAG(DDBLT_ZBUFFERSRCCONSTOVERRIDE,   0x00400000),
        D3D7_FLAG(DDBLT_ZBUFFERSRCOVERRIDE,        0x00800000),
        D3D7_FLAG(DDBLT_WAIT,                      0x01000000),
        D3D7_FLAG(DDBLT_DEPTHFILL,                 0x02000000),
        D3D7_FLAG(DDBLT_DONOTWAIT,                 0x08000000),
    };

    static const FlagNameEntry blt_fast_flag_name_array[] =
    {
        D3D7_FLAG(DDBLTFAST_SRCCOLORKEY,  0x00000001),
        D3D7_FLAG(DDBLTFAST_DESTCOLORKEY, 0x00000002),
        D3D7_FLAG(DDBLTFAST_WAIT,         0x00000010),
        D3D7_FLAG(DDBLTFAST_DONOTWAIT,    0x00000020),
    };

    static const FlagNameEntry clear_flag_name_array[] =
    {
        D3D7_FLAG(D3DCLEAR_TARGET,  0x00000001),
        D3D7_FLAG(D3DCLEAR_ZBUFFER, 0x00000002),
        D3D7_FLAG(D3DCLEAR_STENCIL, 0x00000004),
    };

    static const FlagNameEntry color_key_flag_name_array[] =
    {
        D3D7_FLAG(DDCKEY_COLORSPACE,  0x00000001),
        D3D7_FLAG(DDCKEY_DESTBLT,     0x00000002),
        D3D7_FLAG(DDCKEY_DESTOVERLAY, 0x00000004),
        D3D7_FLAG(DDCKEY_SRCBLT,      0x00000008),
        D3D7_FLAG(DDCKEY_SRCOVERLAY,  0x00000010),
    };

    static const FlagNameEntry cooperative_level_flag_name_array[] =
    {
        D3D7_FLAG(DDSCL_FULLSCREEN,         0x00000001),
        D3D7_FLAG(DDSCL_ALLOWREBOOT,        0x00000002),
        D3D7_FLAG(DDSCL_NOWINDOWCHANGES,    0x00000004),
        D3D7_FLAG(DDSCL_NORMAL,             0x00000008),
        D3D7_FLAG(DDSCL_EXCLUSIVE,          0x00000010),
        D3D7_FLAG(DDSCL_ALLOWMODEX,         0x00000040),
        D3D7_FLAG(DDSCL_SETFOCUSWINDOW,     0x00000080),
        D3D7_FLAG(DDSCL_SETDEVICEWINDOW,    0x00000100),
        D3D7_FLAG(DDSCL_CREATEDEVICEWINDOW, 0x00000200),
        D3D7_FLAG(DDSCL_MULTITHREADED,      0x00000400),
        D3D7_FLAG(DDSCL_FPUSETUP,           0x00000800),
        D3D7_FLAG(DDSCL_FPUPRESERVE,        0x00001000),
    };

    static const FlagNameEntry device_caps_flag_name_array[] =
    {
        D3D7_FLAG(D3DDEVCAPS_FLOATTLVERTEX,            0x00000001),
        D3D7_FLAG(D3DDEVCAPS_SORTINCREASINGZ,          0x00000002),
        D3D7_FLAG(D3DDEVCAPS_SORTDECREASINGZ,          0x00000004),
        D3D7_FLAG(D3DDEVCAPS_SORTEXACT,                0x00000008),
        D3D7_FLAG(D3DDEVCAPS_EXECUTESYSTEMMEMORY,      0x00000010),
        D3D7_FLAG(D3DDEVCAPS_EXECUTEVIDEOMEMORY,       0x00000020),
        D3D7_FLAG(D3DDEVCAPS_TLVERTEXSYSTEMMEMORY,     0x00000040),
        D3D7_FLAG(D3DDEVCAPS_TLVERTEXVIDEOMEMORY,      0x00000080),
        D3D7_FLAG(D3DDEVCAPS_TEXTURESYSTEMMEMORY,      0x00000100),
        D3D7_FLAG(D3DDEVCAPS_TEXTUREVIDEOMEMORY,       0x00000200),
        D3D7_FLAG(D3DDEVCAPS_DRAWPRIMTLVERTEX,         0x00000400),
        D3D7_FLAG(D3DDEVCAPS_CANRENDERAFTERFLIP,       0x00000800),
        D3D7_FLAG(D3DDEVCAPS_TEXTURENONLOCALVIDMEM,    0x00001000),
        D3D7_FLAG(D3DDEVCAPS_DRAWPRIMITIVES2,          0x00002000),
        D3D7_FLAG(D3DDEVCAPS_SEPARATETEXTUREMEMORIES,  0x00004000),
        D3D7_FLAG(D3DDEVCAPS_DRAWPRIMITIVES2EX,        0x00008000),
        D3D7_FLAG(D3DDEVCAPS_HWTRANSFORMANDLIGHT,      0x00010000),
        D3D7_FLAG(D3DDEVCAPS_CANBLTSYSTONONLOCAL,      0x00020000),
        D3D7_FLAG(D3DDEVCAPS_HWRASTERIZATION,          0x00080000),
    };

    static const FlagNameEntry direct_draw_caps_flag_name_array[] =
    {
        D3D7_FLAG(DDCAPS_ALIGNBOUNDARYDEST,  0x00000001),
        D3D7_FLAG(DDCAPS_ALIGNSIZEDEST,      0x00000002),
        D3D7_FLAG(DDCAPS_ALIGNBOUNDARYSRC,   0x00000004),
        D3D7_FLAG(DDCAPS_ALIGNSIZESRC,       0x00000008),
        D3D7_FLAG(DDCAPS_ALIGNSTRIDE,        0x00000010),
        D3D7_FLAG(DDCAPS_BLT,                0x00000020),
        D3D7_FLAG(DDCAPS_BLTQUEUE,           0x00000040),
        D3D7_FLAG(DDCAPS_BLTFOURCC,          0x00000080),
        D3D7_FLAG(DDCAPS_BLTSTRETCH,         0x00000100),
        D3D7_FLAG(DDCAPS_GDI,                0x00000400),
        D3D7_FLAG(DDCAPS_OVERLAY,            0x00000800),
        D3D7_FLAG(DDCAPS_OVERLAYCANTCLIP,    0x00001000),
        D3D7_FLAG(DDCAPS_OVERLAYFOURCC,      0x00002000),
        D3D7_FLAG(DDCAPS_OVERLAYSTRETCH,     0x00004000),
        D3D7_FLAG(DDCAPS_PALETTE,            0x00008000),
        D3D7_FLAG(DDCAPS_PALETTEVSYNC,       0x00010000),
        D3D7_FLAG(DDCAPS_READSCANLINE,       0x00020000),
        D3D7_FLAG(DDCAPS_VBI,                0x00080000),
        D3D7_FLAG(DDCAPS_ZBLTS,              0x00100000),
        D3D7_FLAG(DDCAPS_ZOVERLAYS,          0x00200000),
        D3D7_FLAG(DDCAPS_COLORKEY,           0x00400000),
        D3D7_FLAG(DDCAPS_ALPHA,              0x00800000),
        D3D7_FLAG(DDCAPS_COLORKEYHWASSIST,   0x01000000),
        D3D7_FLAG(DDCAPS_NOHARDWARE,         0x02000000),
        D3D7_FLAG(DDCAPS_BLTCOLORFILL,       0x04000000),
        D3D7_FLAG(DDCAPS_BANKSWITCHED,       0x08000000),
        D3D7_FLAG(DDCAPS_BLTDEPTHFILL,       0x10000000),
        D3D7_FLAG(DDCAPS_CANCLIP,            0x20000000),
        D3D7_FLAG(DDCAPS_CANCLIPSTRETCHED,   0x40000000),
        D3D7_FLAG(DDCAPS_CANBLTSYSMEM,       0x80000000),
    };

    static const FlagNameEntry direct_draw_caps2_flag_name_array[] =
    {
        D3D7_FLAG(DDCAPS2_CERTIFIED,                0x00000001),
        D3D7_FLAG(DDCAPS2_NO2DDURING3DSCENE,        0x00000002),
        D3D7_FLAG(DDCAPS2_VIDEOPORT,                0x00000004),
        D3D7_FLAG(DDCAPS2_AUTOFLIPOVERLAY,          0x00000008),
        D3D7_FLAG(DDCAPS2_CANBOBINTERLEAVED,        0x00000010),
        D3D7_FLAG(DDCAPS2_CANBOBNONINTERLEAVED,     0x00000020),
        D3D7_FLAG(DDCAPS2_COLORCONTROLOVERLAY,      0x00000040),
        D3D7_FLAG(DDCAPS2_COLORCONTROLPRIMARY,      0x00000080),
        D3D7_FLAG(DDCAPS2_CANDROPZ16BIT,            0x00000100),
        D3D7_FLAG(DDCAPS2_NONLOCALVIDMEM,           0x00000200),
        D3D7_FLAG(DDCAPS2_NONLOCALVIDMEMCAPS,       0x00000400),
        D3D7_FLAG(DDCAPS2_NOPAGELOCKREQUIRED,       0x00000800),
        D3D7_FLAG(DDCAPS2_WIDESURFACES,             0x00001000),
        D3D7_FLAG(DDCAPS2_CANFLIPODDEVEN,           0x00002000),
        D3D7_FLAG(DDCAPS2_CANBOBHARDWARE,           0x00004000),
        D3D7_FLAG(DDCAPS2_COPYFOURCC,               0x00008000),
        D3D7_FLAG(DDCAPS2_PRIMARYGAMMA,             0x00020000),
        D3D7_FLAG(DDCAPS2_CANRENDERWINDOWED,        0x00080000),
        D3D7_FLAG(DDCAPS2_CANCALIBRATEGAMMA,        0x00100000),
        D3D7_FLAG(DDCAPS2_FLIPINTERVAL,             0x00200000),
        D3D7_FLAG(DDCAPS2_FLIPNOVSYNC,              0x00400000),
        D3D7_FLAG(DDCAPS2_CANMANAGETEXTURE,         0x00800000),
        D3D7_FLAG(DDCAPS2_TEXMANINNONLOCALVIDMEM,   0x01000000),
        D3D7_FLAG(DDCAPS2_STEREO,                   0x02000000),
    };

    static const FlagNameEntry draw_flag_name_array[] =
    {
        D3D7_FLAG(D3DDP_WAIT,               0x00000001),
        D3D7_FLAG(D3DDP_OUTOFORDER,         0x00000002),
        D3D7_FLAG(D3DDP_DONOTCLIP,          0x00000004),
        D3D7_FLAG(D3DDP_DONOTUPDATEEXTENTS, 0x00000008),
        D3D7_FLAG(D3DDP_DONOTLIGHT,         0x00000010),
    };

    static const FlagNameEntry enum_display_modes_flag_name_array[] =
    {
        D3D7_FLAG(DDEDM_REFRESHRATES,     0x00000001),
        D3D7_FLAG(DDEDM_STANDARDVGAMODES, 0x00000002),
    };

    static const FlagNameEntry enum_surfaces_flag_name_array[] =
    {
        D3D7_FLAG(DDENUMSURFACES_ALL,         0x00000001),
        D3D7_FLAG(DDENUMSURFACES_MATCH,       0x00000002),
        D3D7_FLAG(DDENUMSURFACES_NOMATCH,     0x00000004),
        D3D7_FLAG(DDENUMSURFACES_CANBECREATED, 0x00000008),
        D3D7_FLAG(DDENUMSURFACES_DOESEXIST,   0x00000010),
    };

    static const FlagNameEntry flip_flag_name_array[] =
    {
        D3D7_FLAG(DDFLIP_WAIT,       0x00000001),
        D3D7_FLAG(DDFLIP_EVEN,       0x00000002),
        D3D7_FLAG(DDFLIP_ODD,        0x00000004),
        D3D7_FLAG(DDFLIP_NOVSYNC,    0x00000008),
        D3D7_FLAG(DDFLIP_STEREO,     0x00000010),
        D3D7_FLAG(DDFLIP_DONOTWAIT,  0x00000020),
    };

    static const FlagNameEntry lock_flag_name_array[] =
    {
        D3D7_FLAG(DDLOCK_WAIT,            0x00000001),
        D3D7_FLAG(DDLOCK_EVENT,           0x00000002),
        D3D7_FLAG(DDLOCK_READONLY,        0x00000010),
        D3D7_FLAG(DDLOCK_WRITEONLY,       0x00000020),
        D3D7_FLAG(DDLOCK_NOSYSLOCK,       0x00000800),
        D3D7_FLAG(DDLOCK_NOOVERWRITE,     0x00001000),
        D3D7_FLAG(DDLOCK_DISCARDCONTENTS, 0x00002000),
    };

    static const FlagNameEntry overlay_flag_name_array[] =
    {
        D3D7_FLAG(DDOVER_ALPHADEST,                0x00000001),
        D3D7_FLAG(DDOVER_ALPHADESTCONSTOVERRIDE,   0x00000002),
        D3D7_FLAG(DDOVER_ALPHADESTNEG,             0x00000004),
        D3D7_FLAG(DDOVER_ALPHADESTSURFACEOVERRIDE, 0x00000008),
        D3D7_FLAG(DDOVER_ALPHAEDGEBLEND,           0x00000010),
        D3D7_FLAG(DDOVER_ALPHASRC,                 0x00000020),
        D3D7_FLAG(DDOVER_ALPHASRCCONSTOVERRIDE,    0x00000040),
        D3D7_FLAG(DDOVER_ALPHASRCNEG,              0x00000080),
        D3D7_FLAG(DDOVER_ALPHASRCSURFACEOVERRIDE,  0x00000100),
        D3D7_FLAG(DDOVER_HIDE,                     0x00000200),
        D3D7_FLAG(DDOVER_KEYDEST,                  0x00000400),
        D3D7_FLAG(DDOVER_KEYDESTOVERRIDE,          0x00000800),
        D3D7_FLAG(DDOVER_KEYSRC,                   0x00001000),
        D3D7_FLAG(DDOVER_KEYSRCOVERRIDE,           0x00002000),
        D3D7_FLAG(DDOVER_SHOW,                     0x00004000),
        D3D7_FLAG(DDOVER_ADDDIRTYRECT,             0x00008000),
        D3D7_FLAG(DDOVER_REFRESHDIRTYRECTS,        0x00010000),
        D3D7_FLAG(DDOVER_REFRESHALL,               0x00020000),
        D3D7_FLAG(DDOVER_DDFX,                     0x00080000),
        D3D7_FLAG(DDOVER_AUTOFLIP,                 0x00100000),
        D3D7_FLAG(DDOVER_BOB,                      0x00200000),
        D3D7_FLAG(DDOVER_OVERRIDEBOBWEAVE,         0x00400000),
        D3D7_FLAG(DDOVER_INTERLEAVED,              0x00800000),
        D3D7_FLAG(DDOVER_BOBHARDWARE,              0x01000000),
        D3D7_FLAG(DDOVER_ARGBSCALEFACTORS,         0x02000000),
        D3D7_FLAG(DDOVER_DEGRADEARGBSCALING,       0x04000000),
    };

    static const FlagNameEntry palette_flag_name_array[] =
    {
        D3D7_FLAG(DDPCAPS_4BIT,              0x00000001),
        D3D7_FLAG(DDPCAPS_8BITENTRIES,       0x00000002),
        D3D7_FLAG(DDPCAPS_8BIT,              0x00000004),
        D3D7_FLAG(DDPCAPS_PRIMARYSURFACE,    0x00000010),
        D3D7_FLAG(DDPCAPS_PRIMARYSURFACELEFT, 0x00000020),
        D3D7_FLAG(DDPCAPS_ALLOW256,          0x00000040),
        D3D7_FLAG(DDPCAPS_VSYNC,             0x00000080),
        D3D7_FLAG(DDPCAPS_1BIT,              0x00000100),
        D3D7_FLAG(DDPCAPS_2BIT,              0x00000200),
        D3D7_FLAG(DDPCAPS_ALPHA,             0x00000400),
    };

    static const FlagNameEntry pixel_format_flag_name_array[] =
    {
        D3D7_FLAG(DDPF_ALPHAPIXELS,       0x00000001),
        D3D7_FLAG(DDPF_ALPHA,             0x00000002),
        D3D7_FLAG(DDPF_FOURCC,            0x00000004),
        D3D7_FLAG(DDPF_PALETTEINDEXED4,   0x00000008),
        D3D7_FLAG(DDPF_PALETTEINDEXEDTO8, 0x00000010),
        D3D7_FLAG(DDPF_PALETTEINDEXED8,   0x00000020),
        D3D7_FLAG(DDPF_RGB,               0x00000040),
        D3D7_FLAG(DDPF_COMPRESSED,        0x00000080),
        D3D7_FLAG(DDPF_RGBTOYUV,          0x00000100),
        D3D7_FLAG(DDPF_YUV,               0x00000200),
        D3D7_FLAG(DDPF_ZBUFFER,           0x00000400),
        D3D7_FLAG(DDPF_PALETTEINDEXED1,   0x00000800),
        D3D7_FLAG(DDPF_PALETTEINDEXED2,   0x00001000),
        D3D7_FLAG(DDPF_ZPIXELS,           0x00002000),
        D3D7_FLAG(DDPF_STENCILBUFFER,     0x00004000),
        D3D7_FLAG(DDPF_ALPHAPREMULT,      0x00008000),
        D3D7_FLAG(DDPF_LUMINANCE,         0x00020000),
        D3D7_FLAG(DDPF_BUMPLUMINANCE,     0x00040000),
        D3D7_FLAG(DDPF_BUMPDUDV,          0x00080000),
    };

    static const FlagNameEntry set_display_mode_flag_name_array[] =
    {
        D3D7_FLAG(DDSDM_STANDARDVGAMODE, 0x00000001),
    };

    static const FlagNameEntry surface_caps_flag_name_array[] =
    {
        D3D7_FLAG(DDSCAPS_RESERVED1,       0x00000001),
        D3D7_FLAG(DDSCAPS_ALPHA,           0x00000002),
        D3D7_FLAG(DDSCAPS_BACKBUFFER,      0x00000004),
        D3D7_FLAG(DDSCAPS_COMPLEX,         0x00000008),
        D3D7_FLAG(DDSCAPS_FLIP,            0x00000010),
        D3D7_FLAG(DDSCAPS_FRONTBUFFER,     0x00000020),
        D3D7_FLAG(DDSCAPS_OFFSCREENPLAIN,  0x00000040),
        D3D7_FLAG(DDSCAPS_OVERLAY,         0x00000080),
        D3D7_FLAG(DDSCAPS_PALETTE,         0x00000100),
        D3D7_FLAG(DDSCAPS_PRIMARYSURFACE,  0x00000200),
        D3D7_FLAG(DDSCAPS_PRIMARYSURFACELEFT, 0x00000400),
        D3D7_FLAG(DDSCAPS_SYSTEMMEMORY,    0x00000800),
        D3D7_FLAG(DDSCAPS_TEXTURE,         0x00001000),
        D3D7_FLAG(DDSCAPS_3DDEVICE,        0x00002000),
        D3D7_FLAG(DDSCAPS_VIDEOMEMORY,     0x00004000),
        D3D7_FLAG(DDSCAPS_VISIBLE,         0x00008000),
        D3D7_FLAG(DDSCAPS_WRITEONLY,       0x00010000),
        D3D7_FLAG(DDSCAPS_ZBUFFER,         0x00020000),
        D3D7_FLAG(DDSCAPS_OWNDC,           0x00040000),
        D3D7_FLAG(DDSCAPS_LIVEVIDEO,       0x00080000),
        D3D7_FLAG(DDSCAPS_HWCODEC,         0x00100000),
        D3D7_FLAG(DDSCAPS_MODEX,           0x00200000),
        D3D7_FLAG(DDSCAPS_MIPMAP,          0x00400000),
        D3D7_FLAG(DDSCAPS_RESERVED2,       0x00800000),
        D3D7_FLAG(DDSCAPS_ALLOCONLOAD,     0x04000000),
        D3D7_FLAG(DDSCAPS_VIDEOPORT,       0x08000000),
        D3D7_FLAG(DDSCAPS_LOCALVIDMEM,     0x10000000),
        D3D7_FLAG(DDSCAPS_NONLOCALVIDMEM,  0x20000000),
        D3D7_FLAG(DDSCAPS_STANDARDVGAMODE, 0x40000000),
        D3D7_FLAG(DDSCAPS_OPTIMIZED,       0x80000000),
    };

    static const FlagNameEntry surface_caps2_flag_name_array[] =
    {
        D3D7_FLAG(DDSCAPS2_HINTDYNAMIC,         0x00000004),
        D3D7_FLAG(DDSCAPS2_HINTSTATIC,          0x00000008),
        D3D7_FLAG(DDSCAPS2_TEXTUREMANAGE,       0x00000010),
        D3D7_FLAG(DDSCAPS2_OPAQUE,              0x00000080),
        D3D7_FLAG(DDSCAPS2_HINTANTIALIASING,    0x00000100),
        D3D7_FLAG(DDSCAPS2_CUBEMAP,             0x00000200),
        D3D7_FLAG(DDSCAPS2_CUBEMAP_POSITIVEX,   0x00000400),
        D3D7_FLAG(DDSCAPS2_CUBEMAP_NEGATIVEX,   0x00000800),
        D3D7_FLAG(DDSCAPS2_CUBEMAP_POSITIVEY,   0x00001000),
        D3D7_FLAG(DDSCAPS2_CUBEMAP_NEGATIVEY,   0x00002000),
        D3D7_FLAG(DDSCAPS2_CUBEMAP_POSITIVEZ,   0x00004000),
        D3D7_FLAG(DDSCAPS2_CUBEMAP_NEGATIVEZ,   0x00008000),
        D3D7_FLAG(DDSCAPS2_MIPMAPSUBLEVEL,      0x00010000),
        D3D7_FLAG(DDSCAPS2_D3DTEXTUREMANAGE,    0x00020000),
        D3D7_FLAG(DDSCAPS2_DONOTPERSIST,        0x00040000),
        D3D7_FLAG(DDSCAPS2_STEREOSURFACELEFT,   0x00080000),
    };

    static const FlagNameEntry surface_desc_flag_name_array[] =
    {
        D3D7_FLAG(DDSD_CAPS,            0x00000001),
        D3D7_FLAG(DDSD_HEIGHT,          0x00000002),
        D3D7_FLAG(DDSD_WIDTH,           0x00000004),
        D3D7_FLAG(DDSD_PITCH,           0x00000008),
        D3D7_FLAG(DDSD_BACKBUFFERCOUNT, 0x00000020),
        D3D7_FLAG(DDSD_ZBUFFERBITDEPTH, 0x00000040),
        D3D7_FLAG(DDSD_ALPHABITDEPTH,   0x00000080),
        D3D7_FLAG(DDSD_LPSURFACE,       0x00000800),
        D3D7_FLAG(DDSD_PIXELFORMAT,     0x00001000),
        D3D7_FLAG(DDSD_CKDESTOVERLAY,   0x00002000),
        D3D7_FLAG(DDSD_CKDESTBLT,       0x00004000),
        D3D7_FLAG(DDSD_CKSRCOVERLAY,    0x00008000),
        D3D7_FLAG(DDSD_CKSRCBLT,        0x00010000),
        D3D7_FLAG(DDSD_MIPMAPCOUNT,     0x00020000),
        D3D7_FLAG(DDSD_REFRESHRATE,     0x00040000),
        D3D7_FLAG(DDSD_LINEARSIZE,      0x00080000),
        D3D7_FLAG(DDSD_TEXTURESTAGE,    0x00100000),
        D3D7_FLAG(DDSD_FVF,             0x00200000),
        D3D7_FLAG(DDSD_SRCVBHANDLE,     0x00400000),
        D3D7_FLAG(DDSD_DEPTH,           0x00800000),
    };

    static const FlagNameEntry vertex_operation_flag_name_array[] =
    {
        D3D7_FLAG(D3DVOP_TRANSFORM, 0x00000001),
        D3D7_FLAG(D3DVOP_CLIP,      0x00000004),
        D3D7_FLAG(D3DVOP_EXTENTS,   0x00000008),
        D3D7_FLAG(D3DVOP_LIGHT,     0x00000400),
    };

    static const FlagNameEntry wait_for_vertical_blank_flag_name_array[] =
    {
        D3D7_FLAG(DDWAITVB_BLOCKBEGIN,      0x00000001),
        D3D7_FLAG(DDWAITVB_BLOCKBEGINEVENT, 0x00000002),
        D3D7_FLAG(DDWAITVB_BLOCKEND,        0x00000004),
    };

    /* In the order of the enum. */
    const FlagNameEntry* const table_ptr_array[] =
    {
        blt_flag_name_array,
        blt_fast_flag_name_array,
        clear_flag_name_array,
        color_key_flag_name_array,
        cooperative_level_flag_name_array,
        device_caps_flag_name_array,
        direct_draw_caps_flag_name_array,
        direct_draw_caps2_flag_name_array,
        draw_flag_name_array,
        enum_display_modes_flag_name_array,
        enum_surfaces_flag_name_array,
        flip_flag_name_array,
        lock_flag_name_array,
        overlay_flag_name_array,
        palette_flag_name_array,
        pixel_format_flag_name_array,
        set_display_mode_flag_name_array,
        surface_caps_flag_name_array,
        surface_caps2_flag_name_array,
        surface_desc_flag_name_array,
        vertex_operation_flag_name_array,
        wait_for_vertical_blank_flag_name_array
    };

    const uint32_t n_entries_array[] =
    {
        static_cast<uint32_t>(sizeof(blt_flag_name_array) / sizeof(blt_flag_name_array[0]) ),
        static_cast<uint32_t>(sizeof(blt_fast_flag_name_array) / sizeof(blt_fast_flag_name_array[0]) ),
        static_cast<uint32_t>(sizeof(clear_flag_name_array) / sizeof(clear_flag_name_array[0]) ),
        static_cast<uint32_t>(sizeof(color_key_flag_name_array) / sizeof(color_key_flag_name_array[0]) ),
        static_cast<uint32_t>(sizeof(cooperative_level_flag_name_array) / sizeof(cooperative_level_flag_name_array[0]) ),
        static_cast<uint32_t>(sizeof(device_caps_flag_name_array) / sizeof(device_caps_flag_name_array[0]) ),
        static_cast<uint32_t>(sizeof(direct_draw_caps_flag_name_array) / sizeof(direct_draw_caps_flag_name_array[0]) ),
        static_cast<uint32_t>(sizeof(direct_draw_caps2_flag_name_array) / sizeof(direct_draw_caps2_flag_name_array[0]) ),
        static_cast<uint32_t>(sizeof(draw_flag_name_array) / sizeof(draw_flag_name_array[0]) ),
        static_cast<uint32_t>(sizeof(enum_display_modes_flag_name_array) / sizeof(enum_display_modes_flag_name_array[0]) ),
        static_cast<uint32_t>(sizeof(enum_surfaces_flag_name_array) / sizeof(enum_surfaces_flag_name_array[0]) ),
        static_cast<uint32_t>(sizeof(flip_flag_name_array) / sizeof(flip_flag_name_array[0]) ),
        static_cast<uint32_t>(sizeof(lock_flag_name_array) / sizeof(lock_flag_name_array[0]) ),
        static_cast<uint32_t>(sizeof(overlay_flag_name_array) / sizeof(overlay_flag_name_array[0]) ),
        static_cast<uint32_t>(sizeof(palette_flag_name_array) / sizeof(palette_flag_name_array[0]) ),
        static_cast<uint32_t>(sizeof(pixel_format_flag_name_array) / sizeof(pixel_format_flag_name_array[0]) ),
        static_cast<uint32_t>(sizeof(set_display_mode_flag_name_array) / sizeof(set_display_mode_flag_name_array[0]) ),
        static_cast<uint32_t>(sizeof(surface_caps_flag_name_array) / sizeof(surface_caps_flag_name_array[0]) ),
        static_cast<uint32_t>(sizeof(surface_caps2_flag_name_array) / sizeof(surface_caps2_flag_name_array[0]) ),
        static_cast<uint32_t>(sizeof(surface_desc_flag_name_array) / sizeof(surface_desc_flag_name_array[0]) ),
        static_cast<uint32_t>(sizeof(vertex_operation_flag_name_array) / sizeof(vertex_operation_flag_name_array[0]) ),
        static_cast<uint32_t>(sizeof(wait_for_vertical_blank_flag_name_array) / sizeof(wait_for_vertical_blank_flag_name_array[0]) )
    };

    const size_t n_table = static_cast<size_t>(in_table);
    bool         result  = false;

    if (n_table < sizeof(table_ptr_array) / sizeof(table_ptr_array[0]) )
    {
        *out_table_ptr_ptr = table_ptr_array[n_table];
        *out_n_entries_ptr = n_entries_array[n_table];
        result             = true;
    }
    else
    {
        AI_FAIL_UNSUPPORTED(in_table);
    }

    return result;
}

bool Capture::APIDumpPrinter::D3D7Names::get_hresult_name_table(const ValueNameEntry** out_table_ptr_ptr,
                                                                uint32_t*              out_n_entries_ptr)
{
    /* The codes of DirectDraw and of Direct3D 7 are 0x88760000 and the number the headers give them. */
    static const ValueNameEntry hresult_name_array[] =
    {
        {"S_OK",                                    0x00000000},
        {"S_FALSE",                                 0x00000001},
        {"E_NOTIMPL (DDERR_UNSUPPORTED)",           0x80004001},
        {"E_NOINTERFACE",                           0x80004002},
        {"E_FAIL (DDERR_GENERIC)",                  0x80004005},
        {"E_OUTOFMEMORY (DDERR_OUTOFMEMORY)",       0x8007000E},
        {"E_INVALIDARG (DDERR_INVALIDPARAMS)",      0x80070057},
        {"DDERR_ALREADYINITIALIZED",                0x88760005},
        {"DDERR_CANNOTATTACHSURFACE",               0x8876000A},
        {"DDERR_CANNOTDETACHSURFACE",               0x88760014},
        {"DDERR_CURRENTLYNOTAVAIL",                 0x88760028},
        {"DDERR_EXCEPTION",                         0x88760037},
        {"DDERR_HEIGHTALIGN",                       0x8876005A},
        {"DDERR_INCOMPATIBLEPRIMARY",               0x8876005F},
        {"DDERR_INVALIDCAPS",                       0x88760064},
        {"DDERR_INVALIDCLIPLIST",                   0x8876006E},
        {"DDERR_INVALIDMODE",                       0x88760078},
        {"DDERR_INVALIDOBJECT",                     0x88760082},
        {"DDERR_INVALIDPIXELFORMAT",                0x88760091},
        {"DDERR_INVALIDRECT",                       0x88760096},
        {"DDERR_LOCKEDSURFACES",                    0x887600A0},
        {"DDERR_NO3D",                              0x887600AA},
        {"DDERR_NOALPHAHW",                         0x887600B4},
        {"DDERR_NOSTEREOHARDWARE",                  0x887600B5},
        {"DDERR_NOSURFACELEFT",                     0x887600B6},
        {"DDERR_NOCLIPLIST",                        0x887600CD},
        {"DDERR_NOCOLORCONVHW",                     0x887600D2},
        {"DDERR_NOCOOPERATIVELEVELSET",             0x887600D4},
        {"DDERR_NOCOLORKEY",                        0x887600D7},
        {"DDERR_NOCOLORKEYHW",                      0x887600DC},
        {"DDERR_NODIRECTDRAWSUPPORT",               0x887600DE},
        {"DDERR_NOEXCLUSIVEMODE",                   0x887600E1},
        {"DDERR_NOFLIPHW",                          0x887600E6},
        {"DDERR_NOGDI",                             0x887600F0},
        {"DDERR_NOMIRRORHW",                        0x887600FA},
        {"DDERR_NOTFOUND",                          0x887600FF},
        {"DDERR_NOOVERLAYHW",                       0x88760104},
        {"DDERR_OVERLAPPINGRECTS",                  0x8876010E},
        {"DDERR_NORASTEROPHW",                      0x88760118},
        {"DDERR_NOROTATIONHW",                      0x88760122},
        {"DDERR_NOSTRETCHHW",                       0x88760136},
        {"DDERR_NOT4BITCOLOR",                      0x8876013C},
        {"DDERR_NOT4BITCOLORINDEX",                 0x8876013D},
        {"DDERR_NOT8BITCOLOR",                      0x88760140},
        {"DDERR_NOTEXTUREHW",                       0x8876014A},
        {"DDERR_NOVSYNCHW",                         0x8876014F},
        {"DDERR_NOZBUFFERHW",                       0x88760154},
        {"DDERR_NOZOVERLAYHW",                      0x8876015E},
        {"DDERR_OUTOFCAPS",                         0x88760168},
        {"DDERR_OUTOFVIDEOMEMORY",                  0x8876017C},
        {"DDERR_OVERLAYCANTCLIP",                   0x8876017E},
        {"DDERR_OVERLAYCOLORKEYONLYONEACTIVE",      0x88760180},
        {"DDERR_PALETTEBUSY",                       0x88760183},
        {"DDERR_COLORKEYNOTSET",                    0x88760190},
        {"DDERR_SURFACEALREADYATTACHED",            0x8876019A},
        {"DDERR_SURFACEALREADYDEPENDENT",           0x887601A4},
        {"DDERR_SURFACEBUSY",                       0x887601AE},
        {"DDERR_CANTLOCKSURFACE",                   0x887601B3},
        {"DDERR_SURFACEISOBSCURED",                 0x887601B8},
        {"DDERR_SURFACELOST",                       0x887601C2},
        {"DDERR_SURFACENOTATTACHED",                0x887601CC},
        {"DDERR_TOOBIGHEIGHT",                      0x887601D6},
        {"DDERR_TOOBIGSIZE",                        0x887601E0},
        {"DDERR_TOOBIGWIDTH",                       0x887601EA},
        {"DDERR_UNSUPPORTEDFORMAT",                 0x887601FE},
        {"DDERR_UNSUPPORTEDMASK",                   0x88760208},
        {"DDERR_VERTICALBLANKINPROGRESS",           0x88760219},
        {"DDERR_WASSTILLDRAWING",                   0x8876021C},
        {"DDERR_XALIGN",                            0x88760230},
        {"DDERR_INVALIDDIRECTDRAWGUID",             0x88760231},
        {"DDERR_DIRECTDRAWALREADYCREATED",          0x88760232},
        {"DDERR_NODIRECTDRAWHW",                    0x88760233},
        {"DDERR_PRIMARYSURFACEALREADYEXISTS",       0x88760234},
        {"DDERR_NOEMULATION",                       0x88760235},
        {"DDERR_REGIONTOOSMALL",                    0x88760236},
        {"DDERR_CLIPPERISUSINGHWND",                0x88760237},
        {"DDERR_NOCLIPPERATTACHED",                 0x88760238},
        {"DDERR_NOHWND",                            0x88760239},
        {"DDERR_HWNDSUBCLASSED",                    0x8876023A},
        {"DDERR_HWNDALREADYSET",                    0x8876023B},
        {"DDERR_NOPALETTEATTACHED",                 0x8876023C},
        {"DDERR_NOPALETTEHW",                       0x8876023D},
        {"DDERR_BLTFASTCANTCLIP",                   0x8876023E},
        {"DDERR_NOBLTHW",                           0x8876023F},
        {"DDERR_NODDROPSHW",                        0x88760240},
        {"DDERR_OVERLAYNOTVISIBLE",                 0x88760241},
        {"DDERR_NOOVERLAYDEST",                     0x88760242},
        {"DDERR_INVALIDPOSITION",                   0x88760243},
        {"DDERR_NOTAOVERLAYSURFACE",                0x88760244},
        {"DDERR_EXCLUSIVEMODEALREADYSET",           0x88760245},
        {"DDERR_NOTFLIPPABLE",                      0x88760246},
        {"DDERR_CANTDUPLICATE",                     0x88760247},
        {"DDERR_NOTLOCKED",                         0x88760248},
        {"DDERR_CANTCREATEDC",                      0x88760249},
        {"DDERR_NODC",                              0x8876024A},
        {"DDERR_WRONGMODE",                         0x8876024B},
        {"DDERR_IMPLICITLYCREATED",                 0x8876024C},
        {"DDERR_NOTPALETTIZED",                     0x8876024D},
        {"DDERR_UNSUPPORTEDMODE",                   0x8876024E},
        {"DDERR_NOMIPMAPHW",                        0x8876024F},
        {"DDERR_INVALIDSURFACETYPE",                0x88760250},
        {"DDERR_NOOPTIMIZEHW",                      0x88760258},
        {"DDERR_NOTLOADED",                         0x88760259},
        {"DDERR_NOFOCUSWINDOW",                     0x8876025A},
        {"DDERR_NOTONMIPMAPSUBLEVEL",               0x8876025B},
        {"DDERR_DCALREADYCREATED",                  0x8876026C},
        {"DDERR_NONONLOCALVIDMEM",                  0x88760276},
        {"DDERR_CANTPAGELOCK",                      0x88760280},
        {"DDERR_CANTPAGEUNLOCK",                    0x88760294},
        {"DDERR_NOTPAGELOCKED",                     0x887602A8},
        {"DDERR_MOREDATA",                          0x887602B2},
        {"DDERR_EXPIRED",                           0x887602B3},
        {"DDERR_TESTFINISHED",                      0x887602B4},
        {"DDERR_NEWMODE",                           0x887602B5},
        {"DDERR_D3DNOTINITIALIZED",                 0x887602B6},
        {"DDERR_VIDEONOTACTIVE",                    0x887602B7},
        {"DDERR_NOMONITORINFORMATION",              0x887602B8},
        {"DDERR_NODRIVERSUPPORT",                   0x887602B9},
        {"DDERR_DEVICEDOESNTOWNSURFACE",            0x887602BB},
        {"D3DERR_BADMAJORVERSION",                  0x887602BC},
        {"D3DERR_BADMINORVERSION",                  0x887602BD},
        {"D3DERR_INVALID_DEVICE",                   0x887602C1},
        {"D3DERR_INITFAILED",                       0x887602C2},
        {"D3DERR_DEVICEAGGREGATED",                 0x887602C3},
        {"D3DERR_EXECUTE_CREATE_FAILED",            0x887602C6},
        {"D3DERR_EXECUTE_DESTROY_FAILED",           0x887602C7},
        {"D3DERR_EXECUTE_LOCK_FAILED",              0x887602C8},
        {"D3DERR_EXECUTE_UNLOCK_FAILED",            0x887602C9},
        {"D3DERR_EXECUTE_LOCKED",                   0x887602CA},
        {"D3DERR_EXECUTE_NOT_LOCKED",               0x887602CB},
        {"D3DERR_EXECUTE_FAILED",                   0x887602CC},
        {"D3DERR_EXECUTE_CLIPPED_FAILED",           0x887602CD},
        {"D3DERR_TEXTURE_NO_SUPPORT",               0x887602D0},
        {"D3DERR_TEXTURE_CREATE_FAILED",            0x887602D1},
        {"D3DERR_TEXTURE_DESTROY_FAILED",           0x887602D2},
        {"D3DERR_TEXTURE_LOCK_FAILED",              0x887602D3},
        {"D3DERR_TEXTURE_UNLOCK_FAILED",            0x887602D4},
        {"D3DERR_TEXTURE_LOAD_FAILED",              0x887602D5},
        {"D3DERR_TEXTURE_SWAP_FAILED",              0x887602D6},
        {"D3DERR_TEXTURE_LOCKED",                   0x887602D7},
        {"D3DERR_TEXTURE_NOT_LOCKED",               0x887602D8},
        {"D3DERR_TEXTURE_GETSURF_FAILED",           0x887602D9},
        {"D3DERR_SETVIEWPORTDATA_FAILED",           0x887602F8},
        {"D3DERR_INVALIDCURRENTVIEWPORT",           0x887602F9},
        {"D3DERR_INVALIDPRIMITIVETYPE",             0x887602FA},
        {"D3DERR_INVALIDVERTEXTYPE",                0x887602FB},
        {"D3DERR_TEXTURE_BADSIZE",                  0x887602FC},
        {"D3DERR_INVALIDRAMPTEXTURE",               0x887602FD},
        {"D3DERR_LIGHT_SET_FAILED",                 0x8876030C},
        {"D3DERR_LIGHTHASVIEWPORT",                 0x8876030E},
        {"D3DERR_LIGHTNOTINTHISVIEWPORT",           0x8876030F},
        {"D3DERR_SCENE_IN_SCENE",                   0x88760316},
        {"D3DERR_SCENE_NOT_IN_SCENE",               0x88760317},
        {"D3DERR_SCENE_BEGIN_FAILED",               0x88760318},
        {"D3DERR_SCENE_END_FAILED",                 0x88760319},
        {"D3DERR_INBEGIN",                          0x8876031C},
        {"D3DERR_NOTINBEGIN",                       0x8876031D},
        {"D3DERR_NOVIEWPORTS",                      0x8876031E},
        {"D3DERR_VIEWPORTDATANOTSET",               0x8876031F},
        {"D3DERR_VIEWPORTHASNODEVICE",              0x88760320},
        {"D3DERR_NOCURRENTVIEWPORT",                0x88760321},
        {"D3DERR_INVALIDVERTEXFORMAT",              0x88760800},
        {"D3DERR_COLORKEYATTACHED",                 0x88760802},
        {"D3DERR_VERTEXBUFFEROPTIMIZED",            0x8876080C},
        {"D3DERR_VBUF_CREATE_FAILED",               0x8876080D},
        {"D3DERR_VERTEXBUFFERLOCKED",               0x8876080E},
        {"D3DERR_VERTEXBUFFERUNLOCKFAILED",         0x8876080F},
        {"D3DERR_ZBUFFER_NOTPRESENT",               0x88760816},
        {"D3DERR_STENCILBUFFER_NOTPRESENT",         0x88760817},
        {"D3DERR_WRONGTEXTUREFORMAT",               0x88760818},
        {"D3DERR_UNSUPPORTEDCOLOROPERATION",        0x88760819},
        {"D3DERR_UNSUPPORTEDCOLORARG",              0x8876081A},
        {"D3DERR_UNSUPPORTEDALPHAOPERATION",        0x8876081B},
        {"D3DERR_UNSUPPORTEDALPHAARG",              0x8876081C},
        {"D3DERR_TOOMANYOPERATIONS",                0x8876081D},
        {"D3DERR_CONFLICTINGTEXTUREFILTER",         0x8876081E},
        {"D3DERR_UNSUPPORTEDFACTORVALUE",           0x8876081F},
        {"D3DERR_CONFLICTINGRENDERSTATE",           0x88760821},
        {"D3DERR_UNSUPPORTEDTEXTUREFILTER",         0x88760822},
        {"D3DERR_TOOMANYPRIMITIVES",                0x88760823},
        {"D3DERR_INVALIDMATRIX",                    0x88760824},
        {"D3DERR_TOOMANYVERTICES",                  0x88760825},
        {"D3DERR_CONFLICTINGTEXTUREPALETTE",        0x88760826},
        {"D3DERR_INVALIDSTATEBLOCK",                0x88760834},
        {"D3DERR_INBEGINSTATEBLOCK",                0x88760835},
        {"D3DERR_NOTINBEGINSTATEBLOCK",             0x88760836},
    };

    *out_table_ptr_ptr = hresult_name_array;
    *out_n_entries_ptr = static_cast<uint32_t>(sizeof(hresult_name_array) / sizeof(hresult_name_array[0]) );

    return true;
}

bool Capture::APIDumpPrinter::D3D7Names::get_render_state_value_info(const uint32_t& in_render_state,
                                                                     StateValueInfo* out_info_ptr)
{
    /* Render states, by their value in the headers of DirectX 7. */
    static const StateValueEntry state_value_entry_array[] =
    {
        {1,   StateValueFormat::HEX,     StateValueTable::NONE},                      /* D3DRENDERSTATE_TEXTUREHANDLE */
        {4,   StateValueFormat::BOOLEAN, StateValueTable::NONE},                      /* TEXTUREPERSPECTIVE */
        {5,   StateValueFormat::BOOLEAN, StateValueTable::NONE},                      /* WRAPU */
        {6,   StateValueFormat::BOOLEAN, StateValueTable::NONE},                      /* WRAPV */
        {7,   StateValueFormat::NAME,    StateValueTable::Z_BUFFER_TYPE},             /* ZENABLE */
        {8,   StateValueFormat::NAME,    StateValueTable::FILL_MODE},                 /* FILLMODE */
        {9,   StateValueFormat::NAME,    StateValueTable::SHADE_MODE},                /* SHADEMODE */
        {10,  StateValueFormat::HEX,     StateValueTable::NONE},                      /* LINEPATTERN */
        {11,  StateValueFormat::BOOLEAN, StateValueTable::NONE},                      /* MONOENABLE */
        {14,  StateValueFormat::BOOLEAN, StateValueTable::NONE},                      /* ZWRITEENABLE */
        {15,  StateValueFormat::BOOLEAN, StateValueTable::NONE},                      /* ALPHATESTENABLE */
        {16,  StateValueFormat::BOOLEAN, StateValueTable::NONE},                      /* LASTPIXEL */
        {17,  StateValueFormat::NAME,    StateValueTable::TEXTURE_FILTER_MAG_LEGACY}, /* TEXTUREMAG */
        {18,  StateValueFormat::NAME,    StateValueTable::TEXTURE_FILTER_MAG_LEGACY}, /* TEXTUREMIN */
        {19,  StateValueFormat::NAME,    StateValueTable::BLEND},                     /* SRCBLEND */
        {20,  StateValueFormat::NAME,    StateValueTable::BLEND},                     /* DESTBLEND */
        {21,  StateValueFormat::NAME,    StateValueTable::TEXTURE_BLEND},             /* TEXTUREMAPBLEND */
        {22,  StateValueFormat::NAME,    StateValueTable::CULL},                      /* CULLMODE */
        {23,  StateValueFormat::NAME,    StateValueTable::CMP_FUNC},                  /* ZFUNC */
        {25,  StateValueFormat::NAME,    StateValueTable::CMP_FUNC},                  /* ALPHAFUNC */
        {26,  StateValueFormat::BOOLEAN, StateValueTable::NONE},                      /* DITHERENABLE */
        {27,  StateValueFormat::BOOLEAN, StateValueTable::NONE},                      /* ALPHABLENDENABLE */
        {28,  StateValueFormat::BOOLEAN, StateValueTable::NONE},                      /* FOGENABLE */
        {29,  StateValueFormat::BOOLEAN, StateValueTable::NONE},                      /* SPECULARENABLE */
        {30,  StateValueFormat::BOOLEAN, StateValueTable::NONE},                      /* ZVISIBLE */
        {31,  StateValueFormat::BOOLEAN, StateValueTable::NONE},                      /* SUBPIXEL */
        {32,  StateValueFormat::BOOLEAN, StateValueTable::NONE},                      /* SUBPIXELX */
        {33,  StateValueFormat::BOOLEAN, StateValueTable::NONE},                      /* STIPPLEDALPHA */
        {34,  StateValueFormat::COLOR,   StateValueTable::NONE},                      /* FOGCOLOR */
        {35,  StateValueFormat::NAME,    StateValueTable::FOG_MODE},                  /* FOGTABLEMODE */
        {36,  StateValueFormat::FLOAT,   StateValueTable::NONE},                      /* FOGSTART */
        {37,  StateValueFormat::FLOAT,   StateValueTable::NONE},                      /* FOGEND */
        {38,  StateValueFormat::FLOAT,   StateValueTable::NONE},                      /* FOGDENSITY */
        {39,  StateValueFormat::BOOLEAN, StateValueTable::NONE},                      /* STIPPLEENABLE */
        {40,  StateValueFormat::BOOLEAN, StateValueTable::NONE},                      /* EDGEANTIALIAS */
        {41,  StateValueFormat::BOOLEAN, StateValueTable::NONE},                      /* COLORKEYENABLE */
        {43,  StateValueFormat::COLOR,   StateValueTable::NONE},                      /* BORDERCOLOR */
        {44,  StateValueFormat::NAME,    StateValueTable::TEXTURE_ADDRESS},           /* TEXTUREADDRESSU */
        {45,  StateValueFormat::NAME,    StateValueTable::TEXTURE_ADDRESS},           /* TEXTUREADDRESSV */
        {3,   StateValueFormat::NAME,    StateValueTable::TEXTURE_ADDRESS},           /* TEXTUREADDRESS */
        {46,  StateValueFormat::FLOAT,   StateValueTable::NONE},                      /* MIPMAPLODBIAS */
        {48,  StateValueFormat::BOOLEAN, StateValueTable::NONE},                      /* RANGEFOGENABLE */
        {50,  StateValueFormat::BOOLEAN, StateValueTable::NONE},                      /* FLUSHBATCH */
        {51,  StateValueFormat::BOOLEAN, StateValueTable::NONE},                      /* TRANSLUCENTSORTINDEPENDENT */
        {52,  StateValueFormat::BOOLEAN, StateValueTable::NONE},                      /* STENCILENABLE */
        {53,  StateValueFormat::NAME,    StateValueTable::STENCIL_OP},                /* STENCILFAIL */
        {54,  StateValueFormat::NAME,    StateValueTable::STENCIL_OP},                /* STENCILZFAIL */
        {55,  StateValueFormat::NAME,    StateValueTable::STENCIL_OP},                /* STENCILPASS */
        {56,  StateValueFormat::NAME,    StateValueTable::CMP_FUNC},                  /* STENCILFUNC */
        {58,  StateValueFormat::HEX,     StateValueTable::NONE},                      /* STENCILMASK */
        {59,  StateValueFormat::HEX,     StateValueTable::NONE},                      /* STENCILWRITEMASK */
        {60,  StateValueFormat::COLOR,   StateValueTable::NONE},                      /* TEXTUREFACTOR */
        {128, StateValueFormat::HEX,     StateValueTable::NONE},                      /* WRAP0 */
        {129, StateValueFormat::HEX,     StateValueTable::NONE},                      /* WRAP1 */
        {130, StateValueFormat::HEX,     StateValueTable::NONE},                      /* WRAP2 */
        {131, StateValueFormat::HEX,     StateValueTable::NONE},                      /* WRAP3 */
        {132, StateValueFormat::HEX,     StateValueTable::NONE},                      /* WRAP4 */
        {133, StateValueFormat::HEX,     StateValueTable::NONE},                      /* WRAP5 */
        {134, StateValueFormat::HEX,     StateValueTable::NONE},                      /* WRAP6 */
        {135, StateValueFormat::HEX,     StateValueTable::NONE},                      /* WRAP7 */
        {136, StateValueFormat::BOOLEAN, StateValueTable::NONE},                      /* CLIPPING */
        {137, StateValueFormat::BOOLEAN, StateValueTable::NONE},                      /* LIGHTING */
        {138, StateValueFormat::BOOLEAN, StateValueTable::NONE},                      /* EXTENTS */
        {139, StateValueFormat::COLOR,   StateValueTable::NONE},                      /* AMBIENT */
        {140, StateValueFormat::NAME,    StateValueTable::FOG_MODE},                  /* FOGVERTEXMODE */
        {141, StateValueFormat::BOOLEAN, StateValueTable::NONE},                      /* COLORVERTEX */
        {142, StateValueFormat::BOOLEAN, StateValueTable::NONE},                      /* LOCALVIEWER */
        {143, StateValueFormat::BOOLEAN, StateValueTable::NONE},                      /* NORMALIZENORMALS */
        {144, StateValueFormat::BOOLEAN, StateValueTable::NONE},                      /* COLORKEYBLENDENABLE */
        {145, StateValueFormat::NAME,    StateValueTable::MATERIAL_COLOR_SOURCE},     /* DIFFUSEMATERIALSOURCE */
        {146, StateValueFormat::NAME,    StateValueTable::MATERIAL_COLOR_SOURCE},     /* SPECULARMATERIALSOURCE */
        {147, StateValueFormat::NAME,    StateValueTable::MATERIAL_COLOR_SOURCE},     /* AMBIENTMATERIALSOURCE */
        {148, StateValueFormat::NAME,    StateValueTable::MATERIAL_COLOR_SOURCE},     /* EMISSIVEMATERIALSOURCE */
        {152, StateValueFormat::HEX,     StateValueTable::NONE},                      /* CLIPPLANEENABLE */
    };

    return get_state_value_info(D3D7_TABLE(state_value_entry_array),
                                in_render_state,
                                out_info_ptr);
}

bool Capture::APIDumpPrinter::D3D7Names::get_state_value_info(const StateValueEntry* in_entry_array_ptr,
                                                              const uint32_t&        in_n_entries,
                                                              const uint32_t&        in_state,
                                                              StateValueInfo*        out_info_ptr)
{
    static const ValueNameEntry texture_blend_name_array[] =
    {
        {"D3DTBLEND_DECAL",         1},
        {"D3DTBLEND_MODULATE",      2},
        {"D3DTBLEND_DECALALPHA",    3},
        {"D3DTBLEND_MODULATEALPHA", 4},
        {"D3DTBLEND_DECALMASK",     5},
        {"D3DTBLEND_MODULATEMASK",  6},
        {"D3DTBLEND_COPY",          7},
        {"D3DTBLEND_ADD",           8},
    };

    static const ValueNameEntry texture_filter_mag_name_array[] =
    {
        {"D3DTFG_POINT",       1},
        {"D3DTFG_LINEAR",      2},
        {"D3DTFG_FLATCUBIC",   3},
        {"D3DTFG_GAUSSIANCUBIC", 4},
        {"D3DTFG_ANISOTROPIC", 5},
    };

    static const ValueNameEntry texture_filter_mag_legacy_name_array[] =
    {
        {"D3DFILTER_NEAREST",          1},
        {"D3DFILTER_LINEAR",           2},
        {"D3DFILTER_MIPNEAREST",       3},
        {"D3DFILTER_MIPLINEAR",        4},
        {"D3DFILTER_LINEARMIPNEAREST", 5},
        {"D3DFILTER_LINEARMIPLINEAR",  6},
    };

    static const ValueNameEntry texture_filter_min_name_array[] =
    {
        {"D3DTFN_POINT",       1},
        {"D3DTFN_LINEAR",      2},
        {"D3DTFN_ANISOTROPIC", 3},
    };

    static const ValueNameEntry texture_filter_mip_name_array[] =
    {
        {"D3DTFP_NONE",   1},
        {"D3DTFP_POINT",  2},
        {"D3DTFP_LINEAR", 3},
    };

    const StateValueEntry* entry_ptr = nullptr;
    bool                   result    = false;

    for (uint32_t n_entry = 0;
                  n_entry < in_n_entries;
                ++n_entry)
    {
        if (in_entry_array_ptr[n_entry].state == in_state)
        {
            entry_ptr = &in_entry_array_ptr[n_entry];

            break;
        }
    }

    out_info_ptr->format    = StateValueFormat::RAW;
    out_info_ptr->n_entries = 0;
    out_info_ptr->table_ptr = nullptr;

    if (entry_ptr != nullptr)
    {
        NameTable name_table = {nullptr, 0};

        switch (entry_ptr->table)
        {
            case StateValueTable::NONE:
            {
                break;
            }

            case StateValueTable::BLEND:                 name_table = get_shared_name_table(SharedNameTable::BLEND);                 break;
            case StateValueTable::CMP_FUNC:              name_table = get_shared_name_table(SharedNameTable::CMP_FUNC);              break;
            case StateValueTable::CULL:                  name_table = get_shared_name_table(SharedNameTable::CULL);                  break;
            case StateValueTable::FILL_MODE:             name_table = get_shared_name_table(SharedNameTable::FILL_MODE);             break;
            case StateValueTable::FOG_MODE:              name_table = get_shared_name_table(SharedNameTable::FOG_MODE);              break;
            case StateValueTable::MATERIAL_COLOR_SOURCE: name_table = get_shared_name_table(SharedNameTable::MATERIAL_COLOR_SOURCE); break;
            case StateValueTable::SHADE_MODE:            name_table = get_shared_name_table(SharedNameTable::SHADE_MODE);            break;
            case StateValueTable::STENCIL_OP:            name_table = get_shared_name_table(SharedNameTable::STENCIL_OP);            break;
            case StateValueTable::TEXTURE_ADDRESS:       name_table = get_shared_name_table(SharedNameTable::TEXTURE_ADDRESS);       break;
            case StateValueTable::TEXTURE_ARGUMENT:      name_table = get_shared_name_table(SharedNameTable::TEXTURE_ARGUMENT);      break;
            case StateValueTable::TEXTURE_OP:            name_table = get_shared_name_table(SharedNameTable::TEXTURE_OP);            break;
            case StateValueTable::Z_BUFFER_TYPE:         name_table = get_shared_name_table(SharedNameTable::Z_BUFFER_TYPE);         break;

            case StateValueTable::TEXTURE_BLEND:
            {
                name_table = {D3D7_TABLE(texture_blend_name_array)};

                break;
            }

            case StateValueTable::TEXTURE_FILTER_MAG:
            {
                name_table = {D3D7_TABLE(texture_filter_mag_name_array)};

                break;
            }

            case StateValueTable::TEXTURE_FILTER_MAG_LEGACY:
            {
                name_table = {D3D7_TABLE(texture_filter_mag_legacy_name_array)};

                break;
            }

            case StateValueTable::TEXTURE_FILTER_MIN:
            {
                name_table = {D3D7_TABLE(texture_filter_min_name_array)};

                break;
            }

            case StateValueTable::TEXTURE_FILTER_MIP:
            {
                name_table = {D3D7_TABLE(texture_filter_mip_name_array)};

                break;
            }

            default:
            {
                AI_FAIL_UNSUPPORTED(entry_ptr->table);

                break;
            }
        }

        out_info_ptr->format    = entry_ptr->format;
        out_info_ptr->n_entries = name_table.n_entries;
        out_info_ptr->table_ptr = name_table.table_ptr;
        result                  = true;
    }

    return result;
}

bool Capture::APIDumpPrinter::D3D7Names::get_texture_stage_state_value_info(const uint32_t& in_texture_stage_state,
                                                                             StateValueInfo* out_info_ptr)
{
    /* Texture stage states, by their value in the headers of DirectX 7. */
    static const StateValueEntry state_value_entry_array[] =
    {
        {1,  StateValueFormat::NAME,                    StateValueTable::TEXTURE_OP},         /* COLOROP */
        {2,  StateValueFormat::TEXTURE_ARGUMENT,        StateValueTable::TEXTURE_ARGUMENT},   /* COLORARG1 */
        {3,  StateValueFormat::TEXTURE_ARGUMENT,        StateValueTable::TEXTURE_ARGUMENT},   /* COLORARG2 */
        {4,  StateValueFormat::NAME,                    StateValueTable::TEXTURE_OP},         /* ALPHAOP */
        {5,  StateValueFormat::TEXTURE_ARGUMENT,        StateValueTable::TEXTURE_ARGUMENT},   /* ALPHAARG1 */
        {6,  StateValueFormat::TEXTURE_ARGUMENT,        StateValueTable::TEXTURE_ARGUMENT},   /* ALPHAARG2 */
        {7,  StateValueFormat::FLOAT,                   StateValueTable::NONE},               /* BUMPENVMAT00 */
        {8,  StateValueFormat::FLOAT,                   StateValueTable::NONE},               /* BUMPENVMAT01 */
        {9,  StateValueFormat::FLOAT,                   StateValueTable::NONE},               /* BUMPENVMAT10 */
        {10, StateValueFormat::FLOAT,                   StateValueTable::NONE},               /* BUMPENVMAT11 */
        {11, StateValueFormat::TEX_COORD_INDEX,         StateValueTable::NONE},               /* TEXCOORDINDEX */
        {12, StateValueFormat::NAME,                    StateValueTable::TEXTURE_ADDRESS},    /* ADDRESS */
        {13, StateValueFormat::NAME,                    StateValueTable::TEXTURE_ADDRESS},    /* ADDRESSU */
        {14, StateValueFormat::NAME,                    StateValueTable::TEXTURE_ADDRESS},    /* ADDRESSV */
        {15, StateValueFormat::COLOR,                   StateValueTable::NONE},               /* BORDERCOLOR */
        {16, StateValueFormat::NAME,                    StateValueTable::TEXTURE_FILTER_MAG}, /* MAGFILTER */
        {17, StateValueFormat::NAME,                    StateValueTable::TEXTURE_FILTER_MIN}, /* MINFILTER */
        {18, StateValueFormat::NAME,                    StateValueTable::TEXTURE_FILTER_MIP}, /* MIPFILTER */
        {19, StateValueFormat::FLOAT,                   StateValueTable::NONE},               /* MIPMAPLODBIAS */
        {22, StateValueFormat::FLOAT,                   StateValueTable::NONE},               /* BUMPENVLSCALE */
        {23, StateValueFormat::FLOAT,                   StateValueTable::NONE},               /* BUMPENVLOFFSET */
        {24, StateValueFormat::TEXTURE_TRANSFORM_FLAGS, StateValueTable::NONE},               /* TEXTURETRANSFORMFLAGS */
    };

    return get_state_value_info(D3D7_TABLE(state_value_entry_array),
                                in_texture_stage_state,
                                out_info_ptr);
}

bool Capture::APIDumpPrinter::D3D7Names::get_value_name_table(const Interception::Hooks::D3D7::ValueKind& in_kind,
                                                              const ValueNameEntry**                      out_table_ptr_ptr,
                                                              uint32_t*                                   out_n_entries_ptr)
{
    static const ValueNameEntry render_state_type_name_array[] =
    {
        {"D3DRENDERSTATE_TEXTUREHANDLE",              1},
        {"D3DRENDERSTATE_ANTIALIAS",                  2},
        {"D3DRENDERSTATE_TEXTUREADDRESS",             3},
        {"D3DRENDERSTATE_TEXTUREPERSPECTIVE",         4},
        {"D3DRENDERSTATE_WRAPU",                      5},
        {"D3DRENDERSTATE_WRAPV",                      6},
        {"D3DRENDERSTATE_ZENABLE",                    7},
        {"D3DRENDERSTATE_FILLMODE",                   8},
        {"D3DRENDERSTATE_SHADEMODE",                  9},
        {"D3DRENDERSTATE_LINEPATTERN",                10},
        {"D3DRENDERSTATE_MONOENABLE",                 11},
        {"D3DRENDERSTATE_ROP2",                       12},
        {"D3DRENDERSTATE_PLANEMASK",                  13},
        {"D3DRENDERSTATE_ZWRITEENABLE",               14},
        {"D3DRENDERSTATE_ALPHATESTENABLE",            15},
        {"D3DRENDERSTATE_LASTPIXEL",                  16},
        {"D3DRENDERSTATE_TEXTUREMAG",                 17},
        {"D3DRENDERSTATE_TEXTUREMIN",                 18},
        {"D3DRENDERSTATE_SRCBLEND",                   19},
        {"D3DRENDERSTATE_DESTBLEND",                  20},
        {"D3DRENDERSTATE_TEXTUREMAPBLEND",            21},
        {"D3DRENDERSTATE_CULLMODE",                   22},
        {"D3DRENDERSTATE_ZFUNC",                      23},
        {"D3DRENDERSTATE_ALPHAREF",                   24},
        {"D3DRENDERSTATE_ALPHAFUNC",                  25},
        {"D3DRENDERSTATE_DITHERENABLE",               26},
        {"D3DRENDERSTATE_ALPHABLENDENABLE",           27},
        {"D3DRENDERSTATE_FOGENABLE",                  28},
        {"D3DRENDERSTATE_SPECULARENABLE",             29},
        {"D3DRENDERSTATE_ZVISIBLE",                   30},
        {"D3DRENDERSTATE_SUBPIXEL",                   31},
        {"D3DRENDERSTATE_SUBPIXELX",                  32},
        {"D3DRENDERSTATE_STIPPLEDALPHA",              33},
        {"D3DRENDERSTATE_FOGCOLOR",                   34},
        {"D3DRENDERSTATE_FOGTABLEMODE",               35},
        {"D3DRENDERSTATE_FOGSTART",                   36},
        {"D3DRENDERSTATE_FOGEND",                     37},
        {"D3DRENDERSTATE_FOGDENSITY",                 38},
        {"D3DRENDERSTATE_STIPPLEENABLE",              39},
        {"D3DRENDERSTATE_EDGEANTIALIAS",              40},
        {"D3DRENDERSTATE_COLORKEYENABLE",             41},
        {"D3DRENDERSTATE_BORDERCOLOR",                43},
        {"D3DRENDERSTATE_TEXTUREADDRESSU",            44},
        {"D3DRENDERSTATE_TEXTUREADDRESSV",            45},
        {"D3DRENDERSTATE_MIPMAPLODBIAS",              46},
        {"D3DRENDERSTATE_ZBIAS",                      47},
        {"D3DRENDERSTATE_RANGEFOGENABLE",             48},
        {"D3DRENDERSTATE_ANISOTROPY",                 49},
        {"D3DRENDERSTATE_FLUSHBATCH",                 50},
        {"D3DRENDERSTATE_TRANSLUCENTSORTINDEPENDENT", 51},
        {"D3DRENDERSTATE_STENCILENABLE",              52},
        {"D3DRENDERSTATE_STENCILFAIL",                53},
        {"D3DRENDERSTATE_STENCILZFAIL",               54},
        {"D3DRENDERSTATE_STENCILPASS",                55},
        {"D3DRENDERSTATE_STENCILFUNC",                56},
        {"D3DRENDERSTATE_STENCILREF",                 57},
        {"D3DRENDERSTATE_STENCILMASK",                58},
        {"D3DRENDERSTATE_STENCILWRITEMASK",           59},
        {"D3DRENDERSTATE_TEXTUREFACTOR",              60},
        {"D3DRENDERSTATE_WRAP0",                      128},
        {"D3DRENDERSTATE_WRAP1",                      129},
        {"D3DRENDERSTATE_WRAP2",                      130},
        {"D3DRENDERSTATE_WRAP3",                      131},
        {"D3DRENDERSTATE_WRAP4",                      132},
        {"D3DRENDERSTATE_WRAP5",                      133},
        {"D3DRENDERSTATE_WRAP6",                      134},
        {"D3DRENDERSTATE_WRAP7",                      135},
        {"D3DRENDERSTATE_CLIPPING",                   136},
        {"D3DRENDERSTATE_LIGHTING",                   137},
        {"D3DRENDERSTATE_EXTENTS",                    138},
        {"D3DRENDERSTATE_AMBIENT",                    139},
        {"D3DRENDERSTATE_FOGVERTEXMODE",              140},
        {"D3DRENDERSTATE_COLORVERTEX",                141},
        {"D3DRENDERSTATE_LOCALVIEWER",                142},
        {"D3DRENDERSTATE_NORMALIZENORMALS",           143},
        {"D3DRENDERSTATE_COLORKEYBLENDENABLE",        144},
        {"D3DRENDERSTATE_DIFFUSEMATERIALSOURCE",      145},
        {"D3DRENDERSTATE_SPECULARMATERIALSOURCE",     146},
        {"D3DRENDERSTATE_AMBIENTMATERIALSOURCE",      147},
        {"D3DRENDERSTATE_EMISSIVEMATERIALSOURCE",     148},
        {"D3DRENDERSTATE_VERTEXBLEND",                151},
        {"D3DRENDERSTATE_CLIPPLANEENABLE",            152},
    };

    static const ValueNameEntry texture_stage_state_type_name_array[] =
    {
        {"D3DTSS_COLOROP",               1},
        {"D3DTSS_COLORARG1",             2},
        {"D3DTSS_COLORARG2",             3},
        {"D3DTSS_ALPHAOP",               4},
        {"D3DTSS_ALPHAARG1",             5},
        {"D3DTSS_ALPHAARG2",             6},
        {"D3DTSS_BUMPENVMAT00",          7},
        {"D3DTSS_BUMPENVMAT01",          8},
        {"D3DTSS_BUMPENVMAT10",          9},
        {"D3DTSS_BUMPENVMAT11",          10},
        {"D3DTSS_TEXCOORDINDEX",         11},
        {"D3DTSS_ADDRESS",               12},
        {"D3DTSS_ADDRESSU",              13},
        {"D3DTSS_ADDRESSV",              14},
        {"D3DTSS_BORDERCOLOR",           15},
        {"D3DTSS_MAGFILTER",             16},
        {"D3DTSS_MINFILTER",             17},
        {"D3DTSS_MIPFILTER",             18},
        {"D3DTSS_MIPMAPLODBIAS",         19},
        {"D3DTSS_MAXMIPLEVEL",           20},
        {"D3DTSS_MAXANISOTROPY",         21},
        {"D3DTSS_BUMPENVLSCALE",         22},
        {"D3DTSS_BUMPENVLOFFSET",        23},
        {"D3DTSS_TEXTURETRANSFORMFLAGS", 24},
    };

    static const ValueNameEntry transform_state_type_name_array[] =
    {
        {"D3DTRANSFORMSTATE_WORLD",       1},
        {"D3DTRANSFORMSTATE_VIEW",        2},
        {"D3DTRANSFORMSTATE_PROJECTION",  3},
        {"D3DTRANSFORMSTATE_WORLD1",      4},
        {"D3DTRANSFORMSTATE_WORLD2",      5},
        {"D3DTRANSFORMSTATE_WORLD3",      6},
        {"D3DTRANSFORMSTATE_TEXTURE0",    16},
        {"D3DTRANSFORMSTATE_TEXTURE1",    17},
        {"D3DTRANSFORMSTATE_TEXTURE2",    18},
        {"D3DTRANSFORMSTATE_TEXTURE3",    19},
        {"D3DTRANSFORMSTATE_TEXTURE4",    20},
        {"D3DTRANSFORMSTATE_TEXTURE5",    21},
        {"D3DTRANSFORMSTATE_TEXTURE6",    22},
        {"D3DTRANSFORMSTATE_TEXTURE7",    23},
    };

    NameTable name_table = {nullptr, 0};
    bool      result     = true;

    switch (in_kind)
    {
        case Interception::Hooks::D3D7::ValueKind::PRIMITIVE_TYPE:
        {
            name_table = get_shared_name_table(SharedNameTable::PRIMITIVE_TYPE);

            break;
        }

        case Interception::Hooks::D3D7::ValueKind::RENDER_STATE_TYPE:
        {
            name_table = {D3D7_TABLE(render_state_type_name_array)};

            break;
        }

        case Interception::Hooks::D3D7::ValueKind::STATE_BLOCK_TYPE:
        {
            name_table = get_shared_name_table(SharedNameTable::STATE_BLOCK_TYPE);

            break;
        }

        case Interception::Hooks::D3D7::ValueKind::TEXTURE_STAGE_STATE_TYPE:
        {
            name_table = {D3D7_TABLE(texture_stage_state_type_name_array)};

            break;
        }

        case Interception::Hooks::D3D7::ValueKind::TRANSFORM_STATE_TYPE:
        {
            name_table = {D3D7_TABLE(transform_state_type_name_array)};

            break;
        }

        default:
        {
            result = false;

            break;
        }
    }

    *out_table_ptr_ptr = name_table.table_ptr;
    *out_n_entries_ptr = name_table.n_entries;

    return result;
}
