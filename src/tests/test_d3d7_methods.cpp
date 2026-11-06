/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Consistency checks of the D3D7 method table.
 */
#include <gtest/gtest.h>
#include "interception/core/D3D7Utils/methods.h"
#include <set>
#include <string>

TEST(D3D7Methods, DirectDrawCreateExIsNamedButIsNotAMethod)
{
    EXPECT_EQ(std::string(Interception::Core::D3D7Utils::get_function_name_ptr(APIInterceptor::APIFUNCTION_D3D7_DIRECTDRAWCREATEEX) ),
              std::string("DirectDrawCreateEx") );
    EXPECT_EQ(Interception::Core::D3D7Utils::get_method_info_ptr(APIInterceptor::APIFUNCTION_D3D7_DIRECTDRAWCREATEEX),
              nullptr);

    EXPECT_EQ(std::string(Interception::Core::D3D7Utils::get_function_name_ptr(APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAWSURFACE7_FLIP) ),
              std::string("IDirectDrawSurface7::Flip") );
    EXPECT_EQ(Interception::Core::D3D7Utils::get_function_name_ptr(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_PRESENT),
              nullptr);
    EXPECT_EQ(Interception::Core::D3D7Utils::get_function_name_ptr(APIInterceptor::APIFUNCTION_D3D7_METHODS_BEGIN),
              nullptr);
}

TEST(D3D7Methods, FunctionsComeAfterThoseOfD3D8)
{
    EXPECT_GT(static_cast<uint32_t>(APIInterceptor::APIFUNCTION_D3D7_FIRST),
              static_cast<uint32_t>(APIInterceptor::APIFUNCTION_D3D8_LAST) );
    EXPECT_EQ(static_cast<uint32_t>(APIInterceptor::APIFUNCTION_D3D7_LAST) + 1,
              static_cast<uint32_t>(APIInterceptor::APIFUNCTION_COUNT) );
}

TEST(D3D7Methods, EveryInterfaceHasTheExpectedNumberOfMethods)
{
    struct ExpectedCount
    {
        Interception::Hooks::D3D7::Interface interface_type;
        uint32_t                             n_methods;
    };

    static const ExpectedCount expected_count_array[] =
    {
        { Interception::Hooks::D3D7::Interface::IDIRECT3D7,              8  },
        { Interception::Hooks::D3D7::Interface::IDIRECT3DDEVICE7,        49 },
        { Interception::Hooks::D3D7::Interface::IDIRECT3DVERTEXBUFFER7,  9  },
        { Interception::Hooks::D3D7::Interface::IDIRECTDRAW,             3  }, /* only the methods of IUnknown */
        { Interception::Hooks::D3D7::Interface::IDIRECTDRAW7,            30 },
        { Interception::Hooks::D3D7::Interface::IDIRECTDRAWCLIPPER,      9  },
        { Interception::Hooks::D3D7::Interface::IDIRECTDRAWCOLORCONTROL, 5  },
        { Interception::Hooks::D3D7::Interface::IDIRECTDRAWGAMMACONTROL, 5  },
        { Interception::Hooks::D3D7::Interface::IDIRECTDRAWPALETTE,      7  },
        { Interception::Hooks::D3D7::Interface::IDIRECTDRAWSURFACE7,     49 },
    };
    uint32_t total = 0;

    for (const auto& expected_count : expected_count_array)
    {
        EXPECT_EQ(Interception::Core::D3D7Utils::get_n_methods(expected_count.interface_type),
                  expected_count.n_methods) << Interception::Core::D3D7Utils::get_interface_name_ptr(expected_count.interface_type);

        total += expected_count.n_methods;
    }

    uint32_t n_methods = 0;

    Interception::Core::D3D7Utils::get_method_info_array_ptr(&n_methods);

    EXPECT_EQ(n_methods,
              total);
}

TEST(D3D7Methods, SlotsOfAnInterfaceAreContiguousFromZeroAndMapBackToTheirFunction)
{
    uint32_t                                     n_methods   = 0;
    const Interception::Hooks::D3D7::MethodInfo* methods_ptr = Interception::Core::D3D7Utils::get_method_info_array_ptr(&n_methods);

    for (uint32_t n_interface = 0;
                  n_interface < static_cast<uint32_t>(Interception::Hooks::D3D7::Interface::COUNT);
                ++n_interface)
    {
        const auto         interface_type = static_cast<Interception::Hooks::D3D7::Interface>(n_interface);
        std::set<uint32_t> slot_set;

        for (uint32_t n_method = 0;
                      n_method < n_methods;
                    ++n_method)
        {
            if (methods_ptr[n_method].interface_type == interface_type)
            {
                EXPECT_TRUE(slot_set.insert(methods_ptr[n_method].vtable_index).second) << "duplicate slot in "
                                                                                       << methods_ptr[n_method].full_name_ptr;

                EXPECT_EQ(Interception::Core::D3D7Utils::get_api_function(interface_type,
                                                                          methods_ptr[n_method].vtable_index),
                          methods_ptr[n_method].function) << methods_ptr[n_method].full_name_ptr;
            }
        }

        ASSERT_FALSE(slot_set.empty() );
        EXPECT_EQ(*slot_set.begin(),
                  0u)                                                                 << Interception::Core::D3D7Utils::get_interface_name_ptr(interface_type);
        EXPECT_EQ(*slot_set.rbegin(),
                  Interception::Core::D3D7Utils::get_n_methods(interface_type) - 1)  << Interception::Core::D3D7Utils::get_interface_name_ptr(interface_type);
    }
}
