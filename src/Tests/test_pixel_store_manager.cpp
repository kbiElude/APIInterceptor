/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Checks of the sizes of the images which pixel transfers read and write, given the pixel storage modes.
 */
#include <gtest/gtest.h>
#include "Interception/Hooks/OpenGL/pixel_store_manager.h"
#include "Interception/Hooks/OpenGL/types.h"
#include "gl/gl.h"

TEST(PixelStoreManager, RowsArePaddedToTheDefaultAlignment)
{
    Interception::Hooks::OpenGL::PixelStoreManager manager;

    /* 3 RGB pixels are 9 bytes, padded to 12 for the first row; the last row is not padded. */
    EXPECT_EQ(manager.get_n_unpack_bytes(3, 2, 1, GL_RGB, GL_UNSIGNED_BYTE),
              12u + 9u);
}

TEST(PixelStoreManager, TightlyPackedRowsWithAlignmentOfOne)
{
    Interception::Hooks::OpenGL::PixelStoreManager manager;

    manager.on_pixel_store(GL_UNPACK_ALIGNMENT,
                           1);

    EXPECT_EQ(manager.get_n_unpack_bytes(3, 2, 1, GL_RGB, GL_UNSIGNED_BYTE),
              18u);
}

TEST(PixelStoreManager, RowLengthSetsTheDistanceBetweenRows)
{
    Interception::Hooks::OpenGL::PixelStoreManager manager;

    manager.on_pixel_store(GL_UNPACK_ROW_LENGTH,
                           8);

    /* Rows are 8 pixels apart, but the last one has only 2 pixels. */
    EXPECT_EQ(manager.get_n_unpack_bytes(2, 2, 1, GL_RGBA, GL_UNSIGNED_BYTE),
              32u + 8u);
}

TEST(PixelStoreManager, SkippedPixelsAndRowsCountToo)
{
    Interception::Hooks::OpenGL::PixelStoreManager manager;

    manager.on_pixel_store(GL_UNPACK_SKIP_PIXELS,
                           1);
    manager.on_pixel_store(GL_UNPACK_SKIP_ROWS,
                           1);

    /* A row is 8 bytes. One pixel and one row are skipped, then the 2 pixels. */
    EXPECT_EQ(manager.get_n_unpack_bytes(2, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE),
              4u + 8u + 8u);
}

TEST(PixelStoreManager, ImagesOfAVolumeUseImageHeightAndSkipImages)
{
    Interception::Hooks::OpenGL::PixelStoreManager manager;

    manager.on_pixel_store(GL_UNPACK_IMAGE_HEIGHT,
                           4);
    manager.on_pixel_store(GL_UNPACK_SKIP_IMAGES,
                           1);

    /* A row is 8 bytes, an image 4 rows. One image is skipped; of the 2 images, the second has 2 rows. */
    EXPECT_EQ(manager.get_n_unpack_bytes(2, 2, 2, GL_RGBA, GL_UNSIGNED_BYTE),
              32u + 32u + 8u + 8u);
}

TEST(PixelStoreManager, PackedTypesAreOneElement)
{
    Interception::Hooks::OpenGL::PixelStoreManager manager;

    /* 3 pixels of 2 bytes are 6 bytes, padded to 8. */
    EXPECT_EQ(manager.get_n_unpack_bytes(3, 2, 1, GL_RGB, GL_UNSIGNED_SHORT_5_6_5),
              8u + 6u);
}

TEST(PixelStoreManager, PackAndUnpackModesAreIndependent)
{
    Interception::Hooks::OpenGL::PixelStoreManager manager;

    manager.on_pixel_store(GL_PACK_ALIGNMENT,
                           1);

    EXPECT_EQ(manager.get_n_pack_bytes(3, 2, 1, GL_RGB, GL_UNSIGNED_BYTE),
              18u);
    EXPECT_EQ(manager.get_n_unpack_bytes(3, 2, 1, GL_RGB, GL_UNSIGNED_BYTE),
              12u + 9u);
}

TEST(PixelStoreManager, EmptyImagesHaveNoBytes)
{
    Interception::Hooks::OpenGL::PixelStoreManager manager;

    EXPECT_EQ(manager.get_n_unpack_bytes(0, 4, 1, GL_RGBA, GL_UNSIGNED_BYTE),
              0u);
    EXPECT_EQ(manager.get_n_unpack_bytes(4, 0, 1, GL_RGBA, GL_UNSIGNED_BYTE),
              0u);
    EXPECT_EQ(manager.get_n_unpack_bitmap_bytes(0, 4),
              0u);
}

TEST(PixelStoreManager, NegativeValuesAreIgnored)
{
    Interception::Hooks::OpenGL::PixelStoreManager manager;

    manager.on_pixel_store(GL_UNPACK_ALIGNMENT,
                           -1);

    EXPECT_EQ(manager.get_n_unpack_bytes(3, 2, 1, GL_RGB, GL_UNSIGNED_BYTE),
              12u + 9u);
}

TEST(PixelStoreManager, BitmapsHaveOneBitPerPixel)
{
    Interception::Hooks::OpenGL::PixelStoreManager manager;

    /* 10 pixels are 2 bytes, padded to 4 for the first row. */
    EXPECT_EQ(manager.get_n_unpack_bitmap_bytes(10, 2),
              4u + 2u);

    manager.on_pixel_store(GL_UNPACK_ALIGNMENT,
                           1);

    EXPECT_EQ(manager.get_n_unpack_bitmap_bytes(10, 2),
              2u + 2u);
}
