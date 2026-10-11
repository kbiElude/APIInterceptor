/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Checks of the compile-time description of D3D8 method arguments.
 */
#include <gtest/gtest.h>
#include "D3D8Utils/argument_info.h"
#include "argument_info_checker.h"
#include <string>

TEST(D3D8Arguments, ArgumentCountsMatchTheSignatures)
{
    EXPECT_EQ(D3D8::Utils::get_n_arguments(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_PRESENT),       5u);
    EXPECT_EQ(D3D8::Utils::get_n_arguments(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_BEGINSCENE),    1u);
    EXPECT_EQ(D3D8::Utils::get_n_arguments(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3D8_CREATEDEVICE),        7u);
    EXPECT_EQ(D3D8::Utils::get_n_arguments(APIInterceptor::APIFUNCTION_D3D8_DIRECT3DCREATE8),                0u);
    EXPECT_EQ(D3D8::Utils::get_n_arguments(APIInterceptor::APIFUNCTION_GL_GLACCUM),                          0u);
}

TEST(D3D8Arguments, FlagArgumentsAreOverridden)
{
    EXPECT_EQ(Tests::ArgumentInfoChecker::get_argument_info_or_fail(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3D8_CREATEDEVICE,
                                                                    4).kind,
              D3D8::ValueKind::CreateFlags);
    EXPECT_EQ(Tests::ArgumentInfoChecker::get_argument_info_or_fail(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_CLEAR,
                                                                    3).kind,
              D3D8::ValueKind::ClearFlags);
    EXPECT_EQ(Tests::ArgumentInfoChecker::get_argument_info_or_fail(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_CREATETEXTURE,
                                                                    4).kind,
              D3D8::ValueKind::UsageFlags);
    EXPECT_EQ(Tests::ArgumentInfoChecker::get_argument_info_or_fail(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_SETRENDERSTATE,
                                                                    2).kind,
              D3D8::ValueKind::RenderStateValue);
}

TEST(D3D8Arguments, ObjectsAreNamedAfterTheirInterface)
{
    const auto self_info    = Tests::ArgumentInfoChecker::get_argument_info_or_fail(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_CREATETEXTURE,
                                                                                    0);
    const auto texture_info = Tests::ArgumentInfoChecker::get_argument_info_or_fail(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_CREATETEXTURE,
                                                                                    7);

    EXPECT_EQ(self_info.kind,
              D3D8::ValueKind::Object);
    EXPECT_EQ(std::string(self_info.object_type_name_ptr),
              std::string("Device") );
    EXPECT_EQ(texture_info.kind,
              D3D8::ValueKind::ObjectOut);
    EXPECT_EQ(std::string(texture_info.object_type_name_ptr),
              std::string("Texture") );
}

TEST(D3D8Arguments, ReturnedValuesAreDescribed)
{
    D3D8::ArgumentInfo info = {};

    ASSERT_TRUE(D3D8::Utils::get_return_info(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_PRESENT,
                                            &info) );
    EXPECT_EQ(info.kind,
              D3D8::ValueKind::Hresult);

    ASSERT_TRUE(D3D8::Utils::get_return_info(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_SHOWCURSOR,
                                            &info) );
    EXPECT_EQ(info.kind,
              D3D8::ValueKind::Boolean);

    ASSERT_TRUE(D3D8::Utils::get_return_info(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DTEXTURE8_GETTYPE,
                                            &info) );
    EXPECT_EQ(info.kind,
              D3D8::ValueKind::ResourceType);

    EXPECT_FALSE(D3D8::Utils::get_return_info(APIInterceptor::APIFUNCTION_D3D8_DIRECT3DCREATE8,
                                             &info) );
}

TEST(D3D8Arguments, StructuresAndScalarsAreTold)
{
    EXPECT_EQ(Tests::ArgumentInfoChecker::get_argument_info_or_fail(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_SETTRANSFORM,
                                                                    1).kind,
              D3D8::ValueKind::TransformStateType);
    EXPECT_EQ(Tests::ArgumentInfoChecker::get_argument_info_or_fail(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_SETTRANSFORM,
                                                                    2).kind,
              D3D8::ValueKind::Matrix);
    EXPECT_EQ(Tests::ArgumentInfoChecker::get_argument_info_or_fail(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_GETTRANSFORM,
                                                                    2).kind,
              D3D8::ValueKind::Matrix);
    EXPECT_EQ(Tests::ArgumentInfoChecker::get_argument_info_or_fail(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_SETVIEWPORT,
                                                                    1).kind,
              D3D8::ValueKind::Viewport);
    EXPECT_EQ(Tests::ArgumentInfoChecker::get_argument_info_or_fail(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3D8_CREATEDEVICE,
                                                                    5).kind,
              D3D8::ValueKind::PresentParameters);
    EXPECT_EQ(Tests::ArgumentInfoChecker::get_argument_info_or_fail(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DTEXTURE8_SETPRIVATEDATA,
                                                                    1).kind,
              D3D8::ValueKind::Guid);
}

TEST(D3D8Arguments, ExtraArgumentsAreDescribedOnlyWhenTheyHaveAKind)
{
    D3D8::ArgumentInfo info = {};

    EXPECT_TRUE(D3D8::Utils::get_argument_info(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DTEXTURE8_LOCKRECT,
                                               5,
                                              &info) );
    EXPECT_EQ(info.kind,
              D3D8::ValueKind::Rect);
    EXPECT_FALSE(D3D8::Utils::get_argument_info(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DTEXTURE8_LOCKRECT,
                                                6,
                                               &info) );
    EXPECT_FALSE(D3D8::Utils::get_argument_info(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DTEXTURE8_UNLOCKRECT,
                                                2,
                                               &info) );
}

TEST(D3D8Arguments, VolumesAndCubesAreDescribed)
{
    EXPECT_EQ(Tests::ArgumentInfoChecker::get_argument_info_or_fail(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DVOLUMETEXTURE8_LOCKBOX,
                                                                    2).kind,
              D3D8::ValueKind::LockedBox);
    EXPECT_EQ(Tests::ArgumentInfoChecker::get_argument_info_or_fail(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DVOLUMETEXTURE8_LOCKBOX,
                                                                    3).kind,
              D3D8::ValueKind::Box);
    EXPECT_EQ(Tests::ArgumentInfoChecker::get_argument_info_or_fail(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DVOLUMETEXTURE8_LOCKBOX,
                                                                    4).kind,
              D3D8::ValueKind::LockFlags);
    EXPECT_EQ(Tests::ArgumentInfoChecker::get_argument_info_or_fail(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DVOLUME8_GETDESC,
                                                                    1).kind,
              D3D8::ValueKind::VolumeDesc);
    EXPECT_EQ(Tests::ArgumentInfoChecker::get_argument_info_or_fail(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DCUBETEXTURE8_LOCKRECT,
                                                                    1).kind,
              D3D8::ValueKind::CubeMapFace);

    const auto volume_info = Tests::ArgumentInfoChecker::get_argument_info_or_fail(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DVOLUMETEXTURE8_GETVOLUMELEVEL,
                                                                                   2);

    EXPECT_EQ(volume_info.kind,
              D3D8::ValueKind::ObjectOut);
    EXPECT_STREQ(volume_info.object_type_name_ptr,
                 "Volume");
}

TEST(D3D8Arguments, ArrayAndShaderExtrasAreDescribed)
{
    EXPECT_EQ(Tests::ArgumentInfoChecker::get_argument_info_or_fail(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_CLEAR,
                                                                    7).kind,
              D3D8::ValueKind::RectArray);
    EXPECT_EQ(Tests::ArgumentInfoChecker::get_argument_info_or_fail(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_COPYRECTS,
                                                                    7).kind,
              D3D8::ValueKind::PointArray);

    /* Shader tokens and palette entries are plain data chunks, with no kind of their own. */
    D3D8::ArgumentInfo info = {};

    EXPECT_FALSE(D3D8::Utils::get_argument_info(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_CREATEVERTEXSHADER,
                                                5,
                                               &info) );
}
