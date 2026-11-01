/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Checks of the tracking of the texture bindings and of the levels of textures.
 */
#include <gtest/gtest.h>
#include "Interception/Hooks/OpenGL/texture_manager.h"

TEST(TextureManager, NothingIsBoundInitially)
{
    OpenGL::TextureManager manager;

    EXPECT_EQ(manager.get_bound_texture(OpenGL::TextureBindingTarget::TEXTURE_2D),
              0u);
    EXPECT_EQ(manager.get_level_props(5,
                                      0).width,
              0u);
}

TEST(TextureManager, BindingsAreTrackedPerTarget)
{
    OpenGL::TextureManager manager;

    manager.on_texture_bound(OpenGL::TextureBindingTarget::TEXTURE_2D,
                             4);
    manager.on_texture_bound(OpenGL::TextureBindingTarget::TEXTURE_3D,
                             9);

    EXPECT_EQ(manager.get_bound_texture(OpenGL::TextureBindingTarget::TEXTURE_2D),
              4u);
    EXPECT_EQ(manager.get_bound_texture(OpenGL::TextureBindingTarget::TEXTURE_3D),
              9u);
}

TEST(TextureManager, LevelPropsKeepEachDimensionInItsOwnField)
{
    OpenGL::TextureManager manager;

    manager.set_level_props(3,
                            2,
                            64,  /* in_width  */
                            32,  /* in_height */
                            8);  /* in_depth  */

    const auto props = manager.get_level_props(3,
                                               2);

    EXPECT_EQ(props.width,
              64u);
    EXPECT_EQ(props.height,
              32u);
    EXPECT_EQ(props.depth,
              8u);
    EXPECT_EQ(props.compressed_size_bytes,
              0u);

    /* Another level of the same texture is not affected. */
    EXPECT_EQ(manager.get_level_props(3,
                                      1).width,
              0u);
}

TEST(TextureManager, CompressedLevelsRememberTheirSize)
{
    OpenGL::TextureManager manager;

    manager.set_compressed_level_props(3,
                                       0,
                                       4096,
                                       64,
                                       64,
                                       1);

    EXPECT_EQ(manager.get_level_props(3,
                                      0).compressed_size_bytes,
              4096u);

    /* Specifying the level again replaces what was known. */
    manager.set_level_props(3,
                            0,
                            16,
                            16,
                            1);

    EXPECT_EQ(manager.get_level_props(3,
                                      0).compressed_size_bytes,
              0u);
}

TEST(TextureManager, DeletingATextureForgetsItsLevelsOnly)
{
    OpenGL::TextureManager manager;

    manager.set_level_props(2, 0, 4, 4, 1);
    manager.set_level_props(2, 1, 2, 2, 1);
    manager.set_level_props(3, 0, 8, 8, 1);
    manager.on_texture_bound(OpenGL::TextureBindingTarget::TEXTURE_2D,
                             2);

    manager.on_texture_deleted(2);

    EXPECT_EQ(manager.get_level_props(2,
                                      0).width,
              0u);
    EXPECT_EQ(manager.get_level_props(2,
                                      1).width,
              0u);
    EXPECT_EQ(manager.get_level_props(3,
                                      0).width,
              8u);

    /* Deleting a bound texture unbinds it. */
    EXPECT_EQ(manager.get_bound_texture(OpenGL::TextureBindingTarget::TEXTURE_2D),
              0u);
}
