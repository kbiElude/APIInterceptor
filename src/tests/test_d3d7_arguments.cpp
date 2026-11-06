/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Checks of the compile-time description of D3D7 method arguments, the GUIDs of D3D7, and the reading of its surface descriptions.
 */
#include <gtest/gtest.h>
#include "interception/core/D3D7Utils/argument_info.h"
#include "interception/core/D3D7Utils/guids.h"
#include "interception/core/D3D7Utils/value_readers.h"
#include "argument_info_checker.h"
#include <string.h>
#include <string>
#include <vector>

TEST(D3D7Arguments, ArgumentCountsMatchTheSignatures)
{
    EXPECT_EQ(Interception::Core::D3D7Utils::get_n_arguments(APIInterceptor::APIFUNCTION_D3D7_IDIRECT3DDEVICE7_BEGINSCENE),     1u);
    EXPECT_EQ(Interception::Core::D3D7Utils::get_n_arguments(APIInterceptor::APIFUNCTION_D3D7_IDIRECT3DDEVICE7_SETRENDERSTATE), 3u);
    EXPECT_EQ(Interception::Core::D3D7Utils::get_n_arguments(APIInterceptor::APIFUNCTION_D3D7_DIRECTDRAWCREATEEX),              4u);
    EXPECT_EQ(Interception::Core::D3D7Utils::get_n_arguments(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_PRESENT),        0u);
}

TEST(D3D7Arguments, FlagArgumentsAreOverridden)
{
    EXPECT_EQ(Tests::ArgumentInfoChecker::get_d3d7_argument_info_or_fail(APIInterceptor::APIFUNCTION_D3D7_IDIRECT3DDEVICE7_CLEAR,
                                                                         3).kind,
              Interception::Hooks::D3D7::ValueKind::CLEAR_FLAGS);
    EXPECT_EQ(Tests::ArgumentInfoChecker::get_d3d7_argument_info_or_fail(APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAW7_SETCOOPERATIVELEVEL,
                                                                         2).kind,
              Interception::Hooks::D3D7::ValueKind::COOPERATIVE_LEVEL_FLAGS);
    EXPECT_EQ(Tests::ArgumentInfoChecker::get_d3d7_argument_info_or_fail(APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAWSURFACE7_FLIP,
                                                                         2).kind,
              Interception::Hooks::D3D7::ValueKind::FLIP_FLAGS);
    EXPECT_EQ(Tests::ArgumentInfoChecker::get_d3d7_argument_info_or_fail(APIInterceptor::APIFUNCTION_D3D7_IDIRECT3DDEVICE7_SETRENDERSTATE,
                                                                         2).kind,
              Interception::Hooks::D3D7::ValueKind::RENDER_STATE_VALUE);
}

TEST(D3D7Arguments, ObjectsAreNamedAfterTheirInterface)
{
    const auto self_info    = Tests::ArgumentInfoChecker::get_d3d7_argument_info_or_fail(APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAW7_CREATESURFACE,
                                                                                         0);
    const auto surface_info = Tests::ArgumentInfoChecker::get_d3d7_argument_info_or_fail(APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAW7_CREATESURFACE,
                                                                                         2);

    EXPECT_EQ(self_info.kind,
              Interception::Hooks::D3D7::ValueKind::OBJECT);
    EXPECT_EQ(std::string(self_info.object_type_name_ptr),
              std::string("DirectDraw7") );
    EXPECT_EQ(surface_info.kind,
              Interception::Hooks::D3D7::ValueKind::OBJECT_OUT);
    EXPECT_EQ(std::string(surface_info.object_type_name_ptr),
              std::string("Surface") );
}

TEST(D3D7Arguments, QueryInterfaceReturnsAnObjectOfTheTypeAskedFor)
{
    EXPECT_EQ(Tests::ArgumentInfoChecker::get_d3d7_argument_info_or_fail(APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAW7_QUERYINTERFACE,
                                                                         2).kind,
              Interception::Hooks::D3D7::ValueKind::OBJECT_OUT);
    EXPECT_EQ(Tests::ArgumentInfoChecker::get_d3d7_argument_info_or_fail(APIInterceptor::APIFUNCTION_D3D7_DIRECTDRAWCREATEEX,
                                                                         1).kind,
              Interception::Hooks::D3D7::ValueKind::OBJECT_OUT);
}

TEST(D3D7Arguments, ReturnedValuesAreDescribed)
{
    Interception::Hooks::D3D7::ArgumentInfo info = {};

    ASSERT_TRUE(Interception::Core::D3D7Utils::get_return_info(APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAWSURFACE7_FLIP,
                                                              &info) );
    EXPECT_EQ(info.kind,
              Interception::Hooks::D3D7::ValueKind::HRESULT);

    EXPECT_FALSE(Interception::Core::D3D7Utils::get_return_info(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_PRESENT,
                                                               &info) );
}

TEST(D3D7Arguments, UnknownArgumentsAreRefused)
{
    Interception::Hooks::D3D7::ArgumentInfo info = {};

    EXPECT_FALSE(Interception::Core::D3D7Utils::get_argument_info(APIInterceptor::APIFUNCTION_D3D7_IDIRECT3DDEVICE7_BEGINSCENE,
                                                                  5,
                                                                 &info) );
    EXPECT_FALSE(Interception::Core::D3D7Utils::get_argument_info(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_PRESENT,
                                                                  0,
                                                                 &info) );
}

TEST(D3D7Guids, KnownInterfacesAreFound)
{
    /* IID_IDirect3D7 */
    const GUID direct3d7 = {0xf5049e77, 0x4861, 0x11d2, {0xa4, 0x07, 0x00, 0xa0, 0xc9, 0x06, 0x29, 0xa8} };

    const auto* known_guid_ptr = Interception::Core::D3D7Utils::find_known_guid(direct3d7);

    ASSERT_NE(known_guid_ptr,
              nullptr);
    EXPECT_EQ(std::string(known_guid_ptr->name_ptr),
              std::string("IID_IDirect3D7") );
    EXPECT_EQ(known_guid_ptr->object_type,
              Interception::Core::D3D7Utils::ObjectType::DIRECT3D7);
}

TEST(D3D7Guids, DeviceTypesTellNoObjectType)
{
    /* IID_IDirect3DHALDevice */
    const GUID hal_device = {0x84e63de0, 0x46aa, 0x11cf, {0x81, 0x6f, 0x00, 0x00, 0xc0, 0x20, 0x15, 0x6e} };

    const auto* known_guid_ptr = Interception::Core::D3D7Utils::find_known_guid(hal_device);

    ASSERT_NE(known_guid_ptr,
              nullptr);
    EXPECT_EQ(known_guid_ptr->object_type,
              Interception::Core::D3D7Utils::ObjectType::NONE);
}

TEST(D3D7Guids, UnknownGuidsAreNotFound)
{
    const GUID unknown = {0x12345678, 0x1234, 0x1234, {1, 2, 3, 4, 5, 6, 7, 8} };

    EXPECT_EQ(Interception::Core::D3D7Utils::find_known_guid(unknown),
              nullptr);
}

TEST(D3D7ValueReaders, SurfaceDescriptionOf32BitProcessIsRead)
{
    constexpr size_t N_BYTES = 124;

    std::vector<uint8_t> bytes_u8_vec(N_BYTES,
                                      0);

    const auto write_u32_func = [&](const size_t&   in_offset,
                                    const uint32_t& in_value)
    {
        memcpy(bytes_u8_vec.data() + in_offset,
               &in_value,
               sizeof(in_value) );
    };

    write_u32_func(0,  static_cast<uint32_t>(N_BYTES) ); /* dwSize           */
    write_u32_func(4,  0x1007);                          /* dwFlags          */
    write_u32_func(8,  480);                             /* dwHeight         */
    write_u32_func(12, 640);                             /* dwWidth          */
    write_u32_func(16, 2560);                            /* lPitch           */
    write_u32_func(36, 0x00401000);                      /* lpSurface        */

    Interception::Core::D3D7Utils::SurfaceDescription description;

    ASSERT_TRUE(Interception::Core::D3D7Utils::parse_surface_description(bytes_u8_vec.data(),
                                                                         bytes_u8_vec.size(),
                                                                        &description) );

    EXPECT_EQ(description.flags,           0x1007u);
    EXPECT_EQ(description.height,          480u);
    EXPECT_EQ(description.width,           640u);
    EXPECT_EQ(description.pitch,           2560);
    EXPECT_EQ(description.surface_address, 0x00401000u);
}

TEST(D3D7ValueReaders, SurfaceDescriptionOfUnexpectedSizeIsRefused)
{
    std::vector<uint8_t> bytes_u8_vec(100,
                                      0);

    Interception::Core::D3D7Utils::SurfaceDescription description;

    EXPECT_FALSE(Interception::Core::D3D7Utils::parse_surface_description(bytes_u8_vec.data(),
                                                                          bytes_u8_vec.size(),
                                                                         &description) );
}
