/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * What D3D7Utils tells about vertices, the pixels of locked surfaces, and palettes.
 */
#include <gtest/gtest.h>
#include "Interception/Core/D3D7Utils/palette_layout.h"
#include "Interception/Core/D3D7Utils/surface_layout.h"
#include "Interception/Core/D3D7Utils/vertex_format.h"

TEST(D3D7VertexFormat, PositionSizeFollowsTheFormat)
{
    /* Bits of a flexible vertex format, as the DirectX 7 header names them. */
    constexpr uint32_t FVF_XYZ    = 0x002;
    constexpr uint32_t FVF_XYZB2  = 0x008;
    constexpr uint32_t FVF_XYZRHW = 0x004;

    using Interception::Core::D3D7Utils::VertexFormat;

    EXPECT_EQ(VertexFormat::get_n_position_bytes(0),          0u);
    EXPECT_EQ(VertexFormat::get_n_position_bytes(FVF_XYZ),    12u);
    EXPECT_EQ(VertexFormat::get_n_position_bytes(FVF_XYZRHW), 16u);
    EXPECT_EQ(VertexFormat::get_n_position_bytes(FVF_XYZB2),  20u);
}

TEST(D3D7VertexFormat, VertexSizeAddsWhatTheFormatHas)
{
    constexpr uint32_t FVF_DIFFUSE  = 0x040;
    constexpr uint32_t FVF_NORMAL   = 0x010;
    constexpr uint32_t FVF_SPECULAR = 0x080;
    constexpr uint32_t FVF_TEX1     = 0x100;
    constexpr uint32_t FVF_TEX2     = 0x200;
    constexpr uint32_t FVF_XYZ      = 0x002;
    constexpr uint32_t FVF_XYZRHW   = 0x004;

    using Interception::Core::D3D7Utils::VertexFormat;

    /* The transformed and lit vertex of the sample code: position, w, diffuse, specular, one pair of coordinates. */
    EXPECT_EQ(VertexFormat::get_n_vertex_bytes(FVF_XYZRHW | FVF_DIFFUSE | FVF_SPECULAR | FVF_TEX1),
              16u + 4u + 4u + 8u);

    EXPECT_EQ(VertexFormat::get_n_vertex_bytes(FVF_XYZ | FVF_NORMAL | FVF_TEX2),
              12u + 12u + 8u + 8u);

    EXPECT_EQ(VertexFormat::get_n_vertex_bytes(0),
              0u);
}

TEST(D3D7VertexFormat, TextureCoordinatesHaveTheSizeOfTheirStage)
{
    constexpr uint32_t FVF_TEX2            = 0x200;
    constexpr uint32_t FVF_TEXCOORDSIZE1_1 = 0x000c0000; /* stage 1 has 1 coordinate  */
    constexpr uint32_t FVF_TEXCOORDSIZE3_0 = 0x00010000; /* stage 0 has 3 coordinates */
    constexpr uint32_t FVF_XYZ             = 0x002;

    using Interception::Core::D3D7Utils::VertexFormat;

    const uint32_t format = FVF_XYZ | FVF_TEX2 | FVF_TEXCOORDSIZE3_0 | FVF_TEXCOORDSIZE1_1;

    EXPECT_EQ(VertexFormat::get_n_texture_stages(format),                    2u);
    EXPECT_EQ(VertexFormat::get_n_texture_coordinate_bytes(format, 0),       12u);
    EXPECT_EQ(VertexFormat::get_n_texture_coordinate_bytes(format, 1),       4u);
    EXPECT_EQ(VertexFormat::get_n_texture_coordinate_bytes(format, 2),       0u); /* not used */
    EXPECT_EQ(VertexFormat::get_n_vertex_bytes(format),
              12u + 12u + 4u);
}

TEST(D3D7SurfaceLayout, LastRowIsNotPaddedUpToThePitch)
{
    Interception::Hooks::D3D7::DDSURFACEDESC2 description = {};

    description.dwFlags                     = 0x8 /* DDSD_PITCH */;
    description.dwHeight                    = 4;
    description.dwWidth                     = 10;
    description.lPitch                      = 64;
    description.ddpfPixelFormat.dwRGBBitCount = 16;

    EXPECT_EQ(Interception::Core::D3D7Utils::SurfaceLayout::get_region_n_bytes(description, nullptr),
              3u * 64u + 10u * 2u);

    const RECT rect = {2, 1, 6, 3}; /* 4 x 2 pixels */

    EXPECT_EQ(Interception::Core::D3D7Utils::SurfaceLayout::get_region_n_bytes(description, &rect),
              1u * 64u + 4u * 2u);
}

TEST(D3D7SurfaceLayout, CompressedSurfacesTellTheirSize)
{
    Interception::Hooks::D3D7::DDSURFACEDESC2 description = {};

    description.dwFlags = 0x80000 /* DDSD_LINEARSIZE */;
    description.lPitch  = 8192;

    EXPECT_EQ(Interception::Core::D3D7Utils::SurfaceLayout::get_region_n_bytes(description, nullptr),
              8192u);

    description = {};

    EXPECT_EQ(Interception::Core::D3D7Utils::SurfaceLayout::get_region_n_bytes(description, nullptr),
              0u);
}

TEST(D3D7PaletteLayout, EntriesFollowTheFlags)
{
    using Interception::Core::D3D7Utils::PaletteLayout;

    EXPECT_EQ(PaletteLayout::get_n_entries(0x100), 2u);   /* DDPCAPS_1BIT */
    EXPECT_EQ(PaletteLayout::get_n_entries(0x200), 4u);   /* DDPCAPS_2BIT */
    EXPECT_EQ(PaletteLayout::get_n_entries(0x008), 16u);  /* DDPCAPS_4BIT */
    EXPECT_EQ(PaletteLayout::get_n_entries(0x004 | 0x040 /* DDPCAPS_ALLOW256 */), 256u);
    EXPECT_EQ(PaletteLayout::get_n_entries(0),     0u);
}
