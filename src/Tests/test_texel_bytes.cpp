/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Checks of the size of the single texel which the clear functions read.
 */
#include <gtest/gtest.h>
#include "Interception/Hooks/OpenGL/types.h"
#include "Interception/Hooks/OpenGL/utils.h"
#include "gl/gl.h"

TEST(TexelBytes, ComponentsTimesTypeSize)
{
    EXPECT_EQ(OpenGL::Utils::get_n_texel_bytes(GL_RGBA,
                                               GL_FLOAT),
              16u);
    EXPECT_EQ(OpenGL::Utils::get_n_texel_bytes(GL_RED,
                                               GL_UNSIGNED_BYTE),
              1u);
}

TEST(TexelBytes, PackedTypeIsOneElement)
{
    EXPECT_EQ(OpenGL::Utils::get_n_texel_bytes(GL_RGB,
                                               GL_UNSIGNED_SHORT_5_6_5),
              2u);
}
