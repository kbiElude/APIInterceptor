/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Checks of what is done to the pixels that GL reads from a window to make an image of them: the rows are put from the top, and every pixel is opaque.
 */
#include <gtest/gtest.h>
#include "gl_frame_reader.h"

namespace
{
    /* A pixel of four bytes that says which it is: its row and its place in the row. */
    std::vector<uint8_t> make_pixels(const uint32_t& in_width,
                                     const uint32_t& in_height)
    {
        std::vector<uint8_t> result_u8vec;

        for (uint32_t n_row = 0;
                      n_row < in_height;
                    ++n_row)
        {
            for (uint32_t n_column = 0;
                          n_column < in_width;
                        ++n_column)
            {
                result_u8vec.push_back(static_cast<uint8_t>(n_row) );
                result_u8vec.push_back(static_cast<uint8_t>(n_column) );
                result_u8vec.push_back(7);
                result_u8vec.push_back(0); /* the alpha that a window without alpha bits gives */
            }
        }

        return result_u8vec;
    }
}

TEST(GlFrameReader, TheRowsAreFromTheTop)
{
    auto pixel_u8vec = make_pixels(2,
                                   4);

    Replay::ReplayEngineDLL::GlFrameReader::make_top_down_and_opaque(2,
                                                                     4,
                                                                     &pixel_u8vec);

    /* The first row is what was the last. */
    EXPECT_EQ(pixel_u8vec.at(0),
              3u);
    EXPECT_EQ(pixel_u8vec.at(1),
              0u);
    EXPECT_EQ(pixel_u8vec.at(4),
              3u);
    EXPECT_EQ(pixel_u8vec.at(5),
              1u);

    /* The last is what was the first. */
    EXPECT_EQ(pixel_u8vec.at(3 * 2 * 4),
              0u);
}

TEST(GlFrameReader, TheMiddleRowOfAnOddNumberOfThemStaysWhereItIs)
{
    auto pixel_u8vec = make_pixels(3,
                                   3);

    Replay::ReplayEngineDLL::GlFrameReader::make_top_down_and_opaque(3,
                                                                     3,
                                                                     &pixel_u8vec);

    EXPECT_EQ(pixel_u8vec.at(1 * 3 * 4),
              1u);
    EXPECT_EQ(pixel_u8vec.at(0),
              2u);
    EXPECT_EQ(pixel_u8vec.at(2 * 3 * 4),
              0u);
}

TEST(GlFrameReader, EveryPixelIsOpaqueAndTheOtherBytesAreAsTheyWere)
{
    auto pixel_u8vec = make_pixels(2,
                                   2);

    Replay::ReplayEngineDLL::GlFrameReader::make_top_down_and_opaque(2,
                                                                     2,
                                                                     &pixel_u8vec);

    for (size_t n_pixel = 0;
                n_pixel < pixel_u8vec.size() / 4;
              ++n_pixel)
    {
        EXPECT_EQ(pixel_u8vec.at(n_pixel * 4 + 2),
                  7u);
        EXPECT_EQ(pixel_u8vec.at(n_pixel * 4 + 3),
                  255u);
    }
}

TEST(GlFrameReader, ThereIsNoImageWithoutAContext)
{
    Replay::ReplayEngineDLL::GlFrameReader reader([](const char*) -> void*
                                                  {
                                                      return nullptr;
                                                  });
    std::vector<uint8_t>                   pixel_u8vec;
    Replay::ReplayEngineDLL::FrameImage    image;

    EXPECT_FALSE(reader.read(&pixel_u8vec,
                             &image) );
}
