/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Checks of the compile-time description of D3D8 method arguments.
 */
#include <gtest/gtest.h>
#include "Interception/Core/D3D8Utils/argument_info.h"
#include "argument_info_checker.h"
#include <string>

TEST(D3D8Arguments, ArgumentCountsMatchTheSignatures)
{
    EXPECT_EQ(Interception::Core::D3D8Utils::get_n_arguments(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_PRESENT),       5u);
    EXPECT_EQ(Interception::Core::D3D8Utils::get_n_arguments(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_BEGINSCENE),    1u);
    EXPECT_EQ(Interception::Core::D3D8Utils::get_n_arguments(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3D8_CREATEDEVICE),        7u);
    EXPECT_EQ(Interception::Core::D3D8Utils::get_n_arguments(APIInterceptor::APIFUNCTION_D3D8_DIRECT3DCREATE8),                0u);
    EXPECT_EQ(Interception::Core::D3D8Utils::get_n_arguments(APIInterceptor::APIFUNCTION_GL_GLACCUM),                          0u);
}

TEST(D3D8Arguments, FlagArgumentsAreOverridden)
{
    EXPECT_EQ(Tests::ArgumentInfoChecker::get_argument_info_or_fail(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3D8_CREATEDEVICE,
                                                                    4).kind,
              Interception::Hooks::D3D8::ValueKind::CREATE_FLAGS);
    EXPECT_EQ(Tests::ArgumentInfoChecker::get_argument_info_or_fail(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_CLEAR,
                                                                    3).kind,
              Interception::Hooks::D3D8::ValueKind::CLEAR_FLAGS);
    EXPECT_EQ(Tests::ArgumentInfoChecker::get_argument_info_or_fail(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_CREATETEXTURE,
                                                                    4).kind,
              Interception::Hooks::D3D8::ValueKind::USAGE_FLAGS);
    EXPECT_EQ(Tests::ArgumentInfoChecker::get_argument_info_or_fail(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_SETRENDERSTATE,
                                                                    2).kind,
              Interception::Hooks::D3D8::ValueKind::RENDER_STATE_VALUE);
}

TEST(D3D8Arguments, ObjectsAreNamedAfterTheirInterface)
{
    const auto self_info    = Tests::ArgumentInfoChecker::get_argument_info_or_fail(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_CREATETEXTURE,
                                                                                    0);
    const auto texture_info = Tests::ArgumentInfoChecker::get_argument_info_or_fail(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_CREATETEXTURE,
                                                                                    7);

    EXPECT_EQ(self_info.kind,
              Interception::Hooks::D3D8::ValueKind::OBJECT);
    EXPECT_EQ(std::string(self_info.object_type_name_ptr),
              std::string("Device") );
    EXPECT_EQ(texture_info.kind,
              Interception::Hooks::D3D8::ValueKind::OBJECT_OUT);
    EXPECT_EQ(std::string(texture_info.object_type_name_ptr),
              std::string("Texture") );
}

TEST(D3D8Arguments, ReturnedValuesAreDescribed)
{
    Interception::Hooks::D3D8::ArgumentInfo info = {};

    ASSERT_TRUE(Interception::Core::D3D8Utils::get_return_info(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_PRESENT,
                                                              &info) );
    EXPECT_EQ(info.kind,
              Interception::Hooks::D3D8::ValueKind::HRESULT);

    ASSERT_TRUE(Interception::Core::D3D8Utils::get_return_info(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_SHOWCURSOR,
                                                              &info) );
    EXPECT_EQ(info.kind,
              Interception::Hooks::D3D8::ValueKind::BOOLEAN);

    ASSERT_TRUE(Interception::Core::D3D8Utils::get_return_info(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DTEXTURE8_GETTYPE,
                                                              &info) );
    EXPECT_EQ(info.kind,
              Interception::Hooks::D3D8::ValueKind::RESOURCE_TYPE);

    EXPECT_FALSE(Interception::Core::D3D8Utils::get_return_info(APIInterceptor::APIFUNCTION_D3D8_DIRECT3DCREATE8,
                                                               &info) );
}

TEST(D3D8Arguments, StructuresAndScalarsAreTold)
{
    EXPECT_EQ(Tests::ArgumentInfoChecker::get_argument_info_or_fail(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_SETTRANSFORM,
                                                                    1).kind,
              Interception::Hooks::D3D8::ValueKind::TRANSFORM_STATE_TYPE);
    EXPECT_EQ(Tests::ArgumentInfoChecker::get_argument_info_or_fail(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_SETTRANSFORM,
                                                                    2).kind,
              Interception::Hooks::D3D8::ValueKind::MATRIX);
    EXPECT_EQ(Tests::ArgumentInfoChecker::get_argument_info_or_fail(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_GETTRANSFORM,
                                                                    2).kind,
              Interception::Hooks::D3D8::ValueKind::MATRIX);
    EXPECT_EQ(Tests::ArgumentInfoChecker::get_argument_info_or_fail(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_SETVIEWPORT,
                                                                    1).kind,
              Interception::Hooks::D3D8::ValueKind::VIEWPORT);
    EXPECT_EQ(Tests::ArgumentInfoChecker::get_argument_info_or_fail(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3D8_CREATEDEVICE,
                                                                    5).kind,
              Interception::Hooks::D3D8::ValueKind::PRESENT_PARAMETERS);
    EXPECT_EQ(Tests::ArgumentInfoChecker::get_argument_info_or_fail(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DTEXTURE8_SETPRIVATEDATA,
                                                                    1).kind,
              Interception::Hooks::D3D8::ValueKind::GUID);
}

TEST(D3D8Arguments, ExtraArgumentsAreDescribedOnlyWhenTheyHaveAKind)
{
    Interception::Hooks::D3D8::ArgumentInfo info = {};

    EXPECT_TRUE(Interception::Core::D3D8Utils::get_argument_info(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DTEXTURE8_LOCKRECT,
                                                                 5,
                                                                &info) );
    EXPECT_EQ(info.kind,
              Interception::Hooks::D3D8::ValueKind::RECT);
    EXPECT_FALSE(Interception::Core::D3D8Utils::get_argument_info(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DTEXTURE8_LOCKRECT,
                                                                  6,
                                                                 &info) );
    EXPECT_FALSE(Interception::Core::D3D8Utils::get_argument_info(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DTEXTURE8_UNLOCKRECT,
                                                                  2,
                                                                 &info) );
}

TEST(D3D8Arguments, VolumesAndCubesAreDescribed)
{
    EXPECT_EQ(Tests::ArgumentInfoChecker::get_argument_info_or_fail(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DVOLUMETEXTURE8_LOCKBOX,
                                                                    2).kind,
              Interception::Hooks::D3D8::ValueKind::LOCKED_BOX);
    EXPECT_EQ(Tests::ArgumentInfoChecker::get_argument_info_or_fail(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DVOLUMETEXTURE8_LOCKBOX,
                                                                    3).kind,
              Interception::Hooks::D3D8::ValueKind::BOX);
    EXPECT_EQ(Tests::ArgumentInfoChecker::get_argument_info_or_fail(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DVOLUMETEXTURE8_LOCKBOX,
                                                                    4).kind,
              Interception::Hooks::D3D8::ValueKind::LOCK_FLAGS);
    EXPECT_EQ(Tests::ArgumentInfoChecker::get_argument_info_or_fail(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DVOLUME8_GETDESC,
                                                                    1).kind,
              Interception::Hooks::D3D8::ValueKind::VOLUME_DESC);
    EXPECT_EQ(Tests::ArgumentInfoChecker::get_argument_info_or_fail(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DCUBETEXTURE8_LOCKRECT,
                                                                    1).kind,
              Interception::Hooks::D3D8::ValueKind::CUBE_MAP_FACE);

    const auto volume_info = Tests::ArgumentInfoChecker::get_argument_info_or_fail(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DVOLUMETEXTURE8_GETVOLUMELEVEL,
                                                                                   2);

    EXPECT_EQ(volume_info.kind,
              Interception::Hooks::D3D8::ValueKind::OBJECT_OUT);
    EXPECT_STREQ(volume_info.object_type_name_ptr,
                 "Volume");
}

TEST(D3D8Arguments, ArrayAndShaderExtrasAreDescribed)
{
    EXPECT_EQ(Tests::ArgumentInfoChecker::get_argument_info_or_fail(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_CLEAR,
                                                                    7).kind,
              Interception::Hooks::D3D8::ValueKind::RECT_ARRAY);
    EXPECT_EQ(Tests::ArgumentInfoChecker::get_argument_info_or_fail(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_COPYRECTS,
                                                                    7).kind,
              Interception::Hooks::D3D8::ValueKind::POINT_ARRAY);

    /* Shader tokens and palette entries are plain data chunks, with no kind of their own. */
    Interception::Hooks::D3D8::ArgumentInfo info = {};

    EXPECT_FALSE(Interception::Core::D3D8Utils::get_argument_info(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_CREATEVERTEXSHADER,
                                                                  5,
                                                                 &info) );
}

TEST(D3D8Arguments, PresentRectanglesAndCapsAreDescribed)
{
    EXPECT_EQ(Tests::ArgumentInfoChecker::get_argument_info_or_fail(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_PRESENT,
                                                                    5).kind,
              Interception::Hooks::D3D8::ValueKind::RECT);
    EXPECT_EQ(Tests::ArgumentInfoChecker::get_argument_info_or_fail(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_PRESENT,
                                                                    7).kind,
              Interception::Hooks::D3D8::ValueKind::RECT_ARRAY);
    EXPECT_EQ(Tests::ArgumentInfoChecker::get_argument_info_or_fail(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DSWAPCHAIN8_PRESENT,
                                                                    6).kind,
              Interception::Hooks::D3D8::ValueKind::RECT);
    EXPECT_EQ(Tests::ArgumentInfoChecker::get_argument_info_or_fail(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_GETDEVICECAPS,
                                                                    1).kind,
              Interception::Hooks::D3D8::ValueKind::CAPS);
}

TEST(D3D8Arguments, PatchesCarryTheirInfoAndSegmentCounts)
{
    EXPECT_EQ(Interception::Core::D3D8Utils::get_n_arguments(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_DRAWRECTPATCH),
              4u);
    EXPECT_EQ(Interception::Core::D3D8Utils::get_n_arguments(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_DRAWTRIPATCH),
              4u);

    EXPECT_EQ(Tests::ArgumentInfoChecker::get_argument_info_or_fail(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_DRAWRECTPATCH,
                                                                    3).kind,
              Interception::Hooks::D3D8::ValueKind::RECT_PATCH_INFO);
    EXPECT_EQ(Tests::ArgumentInfoChecker::get_argument_info_or_fail(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_DRAWRECTPATCH,
                                                                    4).kind,
              Interception::Hooks::D3D8::ValueKind::FLOAT_ARRAY);
    EXPECT_EQ(Tests::ArgumentInfoChecker::get_argument_info_or_fail(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_DRAWTRIPATCH,
                                                                    3).kind,
              Interception::Hooks::D3D8::ValueKind::TRI_PATCH_INFO);
    EXPECT_EQ(Tests::ArgumentInfoChecker::get_argument_info_or_fail(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_DRAWTRIPATCH,
                                                                    4).kind,
              Interception::Hooks::D3D8::ValueKind::FLOAT_ARRAY);
}
