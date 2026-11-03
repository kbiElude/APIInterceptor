/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * The values of DirectDraw 7 and Direct3D 7 which the code that follows the calls needs. The names and numbers are those of the
 * headers of DirectX 7; the printer has its own lists, of everything.
 */
#ifndef D3D7UTILS_CONSTANTS_H
#define D3D7UTILS_CONSTANTS_H

#include <stdint.h>

namespace Interception
{
    namespace Core
    {
        namespace D3D7Utils
        {
            enum BltFlags : uint32_t
            {
                DDBLT_COLORFILL = 0x00000400,
                DDBLT_DEPTHFILL = 0x02000000
            };

            enum ClearFlags : uint32_t
            {
                D3DCLEAR_STENCIL = 0x00000004,
                D3DCLEAR_TARGET  = 0x00000001,
                D3DCLEAR_ZBUFFER = 0x00000002
            };

            enum PixelFormatFlags : uint32_t
            {
                DDPF_ALPHAPIXELS     = 0x00000001,
                DDPF_FOURCC          = 0x00000004,
                DDPF_PALETTEINDEXED8 = 0x00000020,
                DDPF_RGB             = 0x00000040,
                DDPF_STENCILBUFFER   = 0x00004000,
                DDPF_ZBUFFER         = 0x00000400
            };

            enum RenderState : uint32_t
            {
                D3DRENDERSTATE_ALPHABLENDENABLE   = 27,
                D3DRENDERSTATE_ALPHAREF           = 24,
                D3DRENDERSTATE_AMBIENT            = 139,
                D3DRENDERSTATE_ANISOTROPY         = 49,
                D3DRENDERSTATE_BORDERCOLOR        = 43,
                D3DRENDERSTATE_FOGCOLOR           = 34,
                D3DRENDERSTATE_FOGDENSITY         = 38,
                D3DRENDERSTATE_FOGEND             = 37,
                D3DRENDERSTATE_FOGSTART           = 36,
                D3DRENDERSTATE_LINEPATTERN        = 10,
                D3DRENDERSTATE_MIPMAPLODBIAS      = 46,
                D3DRENDERSTATE_STENCILENABLE      = 52,
                D3DRENDERSTATE_STENCILMASK        = 58,
                D3DRENDERSTATE_STENCILREF         = 57,
                D3DRENDERSTATE_STENCILWRITEMASK   = 59,
                D3DRENDERSTATE_TEXTUREFACTOR      = 60,
                D3DRENDERSTATE_ZBIAS              = 47,
                D3DRENDERSTATE_ZENABLE            = 7
            };

            enum SurfaceCaps : uint32_t
            {
                DDSCAPS_3DDEVICE       = 0x00002000,
                DDSCAPS_BACKBUFFER     = 0x00000004,
                DDSCAPS_COMPLEX        = 0x00000008,
                DDSCAPS_FLIP           = 0x00000010,
                DDSCAPS_FRONTBUFFER    = 0x00000020,
                DDSCAPS_MIPMAP         = 0x00400000,
                DDSCAPS_OFFSCREENPLAIN = 0x00000040,
                DDSCAPS_PRIMARYSURFACE = 0x00000200,
                DDSCAPS_SYSTEMMEMORY   = 0x00000800,
                DDSCAPS_TEXTURE        = 0x00001000,
                DDSCAPS_VIDEOMEMORY    = 0x00004000,
                DDSCAPS_ZBUFFER        = 0x00020000
            };

            enum SurfaceDescFlags : uint32_t
            {
                DDSD_BACKBUFFERCOUNT = 0x00000020,
                DDSD_CAPS            = 0x00000001,
                DDSD_HEIGHT          = 0x00000002,
                DDSD_MIPMAPCOUNT     = 0x00020000,
                DDSD_PIXELFORMAT     = 0x00001000,
                DDSD_WIDTH           = 0x00000004
            };

            enum TextureStageState : uint32_t
            {
                D3DTSS_BORDERCOLOR           = 15,
                D3DTSS_BUMPENVLOFFSET        = 23,
                D3DTSS_BUMPENVLSCALE         = 22,
                D3DTSS_BUMPENVMAT00          = 7,
                D3DTSS_BUMPENVMAT01          = 8,
                D3DTSS_BUMPENVMAT10          = 9,
                D3DTSS_BUMPENVMAT11          = 10,
                D3DTSS_MAXANISOTROPY         = 21,
                D3DTSS_MAXMIPLEVEL           = 20,
                D3DTSS_MIPMAPLODBIAS         = 19
            };

            enum TransformState : uint32_t
            {
                D3DTRANSFORMSTATE_PROJECTION = 3,
                D3DTRANSFORMSTATE_TEXTURE0   = 16,
                D3DTRANSFORMSTATE_TEXTURE1   = 17,
                D3DTRANSFORMSTATE_TEXTURE2   = 18,
                D3DTRANSFORMSTATE_TEXTURE3   = 19,
                D3DTRANSFORMSTATE_TEXTURE4   = 20,
                D3DTRANSFORMSTATE_TEXTURE5   = 21,
                D3DTRANSFORMSTATE_TEXTURE6   = 22,
                D3DTRANSFORMSTATE_TEXTURE7   = 23,
                D3DTRANSFORMSTATE_VIEW       = 2,
                D3DTRANSFORMSTATE_WORLD      = 1,
                D3DTRANSFORMSTATE_WORLD1     = 4,
                D3DTRANSFORMSTATE_WORLD2     = 5,
                D3DTRANSFORMSTATE_WORLD3     = 6
            };

            /* The flexible vertex formats of the vertices: what is in the vertex. */
            enum VertexFormatFlags : uint32_t
            {
                D3DFVF_POSITION_MASK = 0x00E,
                D3DFVF_XYZRHW        = 0x004
            };
        }
    }
}

#endif /* D3D7UTILS_CONSTANTS_H */
