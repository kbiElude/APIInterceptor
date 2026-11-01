/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Checks of the layout of the pixels of a surface region in memory.
 */
#include <gtest/gtest.h>
#include "Interception/Core/D3D8Utils/surface_layout.h"

TEST(SurfaceLayout, UncompressedRowsAreWidthTimesPixelSize)
{
    uint32_t n_row_bytes = 0;
    uint32_t n_rows      = 0;

    D3D8::Utils::get_surface_region_layout(D3D8::D3DFMT_A8R8G8B8,
                                           5,
                                           3,
                                          &n_rows,
                                          &n_row_bytes);

    EXPECT_EQ(n_rows,
              3u);
    EXPECT_EQ(n_row_bytes,
              20u);
}

TEST(SurfaceLayout, CompressedRowsAreMadeOfBlocks)
{
    uint32_t n_row_bytes = 0;
    uint32_t n_rows      = 0;

    D3D8::Utils::get_surface_region_layout(D3D8::D3DFMT_DXT1,
                                           9,
                                           8,
                                          &n_rows,
                                          &n_row_bytes);

    /* 9 pixels need 3 blocks of 8 bytes; 8 pixels need 2 block rows. */
    EXPECT_EQ(n_rows,
              2u);
    EXPECT_EQ(n_row_bytes,
              24u);
}
