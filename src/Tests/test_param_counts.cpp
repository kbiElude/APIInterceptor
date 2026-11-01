/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Checks of the number of values which API calls read through a pointer, when it depends on the parameter name.
 */
#include <gtest/gtest.h>
#include "Interception/Hooks/OpenGL/param_counts.h"
#include "gl/gl.h"

TEST(ParamCounts, CallListsElementsAreSizedByType)
{
    EXPECT_EQ(OpenGL::Utils::get_n_call_lists_type_bytes(GL_UNSIGNED_BYTE),  1u);
    EXPECT_EQ(OpenGL::Utils::get_n_call_lists_type_bytes(GL_SHORT),          2u);
    EXPECT_EQ(OpenGL::Utils::get_n_call_lists_type_bytes(GL_3_BYTES),        3u);
    EXPECT_EQ(OpenGL::Utils::get_n_call_lists_type_bytes(GL_FLOAT),          4u);
}

TEST(ParamCounts, ClearBufferValuesDependOnTheBuffer)
{
    EXPECT_EQ(OpenGL::Utils::get_n_clear_buffer_values(GL_COLOR),   4u);
    EXPECT_EQ(OpenGL::Utils::get_n_clear_buffer_values(GL_DEPTH),   1u);
    EXPECT_EQ(OpenGL::Utils::get_n_clear_buffer_values(GL_STENCIL), 1u);
}

TEST(ParamCounts, FixedFunctionVectors)
{
    EXPECT_EQ(OpenGL::Utils::get_n_fog_params(GL_FOG_COLOR),                      4u);
    EXPECT_EQ(OpenGL::Utils::get_n_fog_params(GL_FOG_DENSITY),                    1u);
    EXPECT_EQ(OpenGL::Utils::get_n_light_model_params(GL_LIGHT_MODEL_AMBIENT),    4u);
    EXPECT_EQ(OpenGL::Utils::get_n_light_model_params(GL_LIGHT_MODEL_TWO_SIDE),   1u);
    EXPECT_EQ(OpenGL::Utils::get_n_light_params(GL_POSITION),                     4u);
    EXPECT_EQ(OpenGL::Utils::get_n_light_params(GL_SPOT_DIRECTION),               3u);
    EXPECT_EQ(OpenGL::Utils::get_n_light_params(GL_SPOT_EXPONENT),                1u);
    EXPECT_EQ(OpenGL::Utils::get_n_material_params(GL_AMBIENT_AND_DIFFUSE),       4u);
    EXPECT_EQ(OpenGL::Utils::get_n_material_params(GL_COLOR_INDEXES),             3u);
    EXPECT_EQ(OpenGL::Utils::get_n_material_params(GL_SHININESS),                 1u);
    EXPECT_EQ(OpenGL::Utils::get_n_tex_env_params(GL_TEXTURE_ENV,
                                                  GL_TEXTURE_ENV_COLOR),          4u);
    EXPECT_EQ(OpenGL::Utils::get_n_tex_env_params(GL_TEXTURE_ENV,
                                                  GL_TEXTURE_ENV_MODE),           1u);
    EXPECT_EQ(OpenGL::Utils::get_n_tex_gen_params(GL_EYE_PLANE),                  4u);
    EXPECT_EQ(OpenGL::Utils::get_n_tex_gen_params(GL_TEXTURE_GEN_MODE),           1u);
}

TEST(ParamCounts, TextureAndPatchParameters)
{
    EXPECT_EQ(OpenGL::Utils::get_n_patch_parameter_values(GL_PATCH_DEFAULT_INNER_LEVEL), 2u);
    EXPECT_EQ(OpenGL::Utils::get_n_patch_parameter_values(GL_PATCH_DEFAULT_OUTER_LEVEL), 4u);
    EXPECT_EQ(OpenGL::Utils::get_n_texture_parameter_params(GL_TEXTURE_BORDER_COLOR),    4u);
    EXPECT_EQ(OpenGL::Utils::get_n_texture_parameter_params(GL_TEXTURE_MIN_FILTER),      1u);
}

TEST(ParamCounts, MapControlPointsAreSizedByTargetStrideAndOrder)
{
    EXPECT_EQ(OpenGL::Utils::get_n_map_components(GL_MAP1_VERTEX_4),   4u);
    EXPECT_EQ(OpenGL::Utils::get_n_map_components(GL_MAP2_NORMAL),     3u);
    EXPECT_EQ(OpenGL::Utils::get_n_map1_values(GL_MAP1_VERTEX_3,
                                               3,
                                               4),                    12u);
    EXPECT_EQ(OpenGL::Utils::get_n_map1_values(GL_MAP1_VERTEX_3,
                                               4,
                                               4),                    15u);
    EXPECT_EQ(OpenGL::Utils::get_n_map2_values(GL_MAP2_VERTEX_3,
                                               3,
                                               4,
                                               12,
                                               4),                    48u);
    EXPECT_EQ(OpenGL::Utils::get_n_map2_values(GL_MAP2_VERTEX_3,
                                               3,
                                               0,
                                               12,
                                               4),                     0u);
}
