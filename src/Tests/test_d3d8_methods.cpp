/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Consistency checks of the D3D8 method table.
 */
#include <gtest/gtest.h>
#include "Interception/Core/D3D8Utils/methods.h"
#include <set>
#include <string>

TEST(D3D8Methods, Direct3DCreate8IsNamedButIsNotAMethod)
{
    EXPECT_EQ(std::string(Interception::Core::D3D8Utils::get_function_name_ptr(APIInterceptor::APIFUNCTION_D3D8_DIRECT3DCREATE8) ),
              std::string("Direct3DCreate8") );
    EXPECT_EQ(Interception::Core::D3D8Utils::get_method_info_ptr(APIInterceptor::APIFUNCTION_D3D8_DIRECT3DCREATE8),
              nullptr);

    EXPECT_EQ(std::string(Interception::Core::D3D8Utils::get_function_name_ptr(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_PRESENT) ),
              std::string("IDirect3DDevice8::Present") );
    EXPECT_EQ(Interception::Core::D3D8Utils::get_function_name_ptr(APIInterceptor::APIFUNCTION_GL_GLACCUM),
              nullptr);
    EXPECT_EQ(Interception::Core::D3D8Utils::get_function_name_ptr(APIInterceptor::APIFUNCTION_D3D8_METHODS_BEGIN),
              nullptr);

    EXPECT_EQ(static_cast<uint32_t>(APIInterceptor::APIFUNCTION_D3D8_FIRST),
              static_cast<uint32_t>(APIInterceptor::APIFUNCTION_D3D8_DIRECT3DCREATE8) );
    EXPECT_EQ(static_cast<uint32_t>(APIInterceptor::APIFUNCTION_D3D8_LAST),
              static_cast<uint32_t>(APIInterceptor::APIFUNCTION_D3D8_METHODS_LAST) );
}

TEST(D3D8Methods, EveryInterfaceHasTheExpectedNumberOfMethods)
{
    struct ExpectedCount
    {
        Interception::Hooks::D3D8::Interface interface_type;
        uint32_t                             n_methods;
    };

    static const ExpectedCount expected_count_array[] =
    {
        { Interception::Hooks::D3D8::Interface::IDIRECT3D8,              16 },
        { Interception::Hooks::D3D8::Interface::IDIRECT3DCUBETEXTURE8,   19 },
        { Interception::Hooks::D3D8::Interface::IDIRECT3DDEVICE8,        97 },
        { Interception::Hooks::D3D8::Interface::IDIRECT3DINDEXBUFFER8,   14 },
        { Interception::Hooks::D3D8::Interface::IDIRECT3DSURFACE8,       11 },
        { Interception::Hooks::D3D8::Interface::IDIRECT3DSWAPCHAIN8,      5 },
        { Interception::Hooks::D3D8::Interface::IDIRECT3DTEXTURE8,       19 },
        { Interception::Hooks::D3D8::Interface::IDIRECT3DVERTEXBUFFER8,  14 },
        { Interception::Hooks::D3D8::Interface::IDIRECT3DVOLUME8,        11 },
        { Interception::Hooks::D3D8::Interface::IDIRECT3DVOLUMETEXTURE8, 19 },
    };
    uint32_t total = 0;

    for (const auto& expected_count : expected_count_array)
    {
        EXPECT_EQ(Interception::Core::D3D8Utils::get_n_methods(expected_count.interface_type),
                  expected_count.n_methods) << Interception::Core::D3D8Utils::get_interface_name_ptr(expected_count.interface_type);

        total += expected_count.n_methods;
    }

    EXPECT_EQ(static_cast<uint32_t>(Interception::Hooks::D3D8::Interface::COUNT),
              sizeof(expected_count_array) / sizeof(expected_count_array[0]) );
    EXPECT_EQ(total,
              static_cast<uint32_t>(APIInterceptor::APIFUNCTION_D3D8_METHODS_LAST - APIInterceptor::APIFUNCTION_D3D8_METHODS_FIRST + 1) );
}

TEST(D3D8Methods, FunctionEnumFollowsTheTableOrder)
{
    uint32_t                                     n_methods   = 0;
    const Interception::Hooks::D3D8::MethodInfo* methods_ptr = Interception::Core::D3D8Utils::get_method_info_array_ptr(&n_methods);

    ASSERT_EQ(n_methods,
              static_cast<uint32_t>(APIInterceptor::APIFUNCTION_D3D8_METHODS_LAST - APIInterceptor::APIFUNCTION_D3D8_METHODS_FIRST + 1) );

    for (uint32_t n_method = 0;
                  n_method < n_methods;
                ++n_method)
    {
        EXPECT_EQ(static_cast<uint32_t>(methods_ptr[n_method].function),
                  static_cast<uint32_t>(APIInterceptor::APIFUNCTION_D3D8_METHODS_FIRST) + n_method);
        EXPECT_EQ(Interception::Core::D3D8Utils::get_method_info_ptr(methods_ptr[n_method].function),
                  methods_ptr + n_method);
    }
}

TEST(D3D8Methods, FunctionsOutsideTheD3D8RangeHaveNoInfo)
{
    EXPECT_EQ(Interception::Core::D3D8Utils::get_method_info_ptr(APIInterceptor::APIFUNCTION_D3D8_METHODS_BEGIN),
              nullptr);
    EXPECT_EQ(Interception::Core::D3D8Utils::get_method_info_ptr(APIInterceptor::APIFUNCTION_GDI32_SWAPBUFFERS),
              nullptr);
    EXPECT_EQ(Interception::Core::D3D8Utils::get_method_info_ptr(APIInterceptor::APIFUNCTION_GL_GLACCUM),
              nullptr);
    EXPECT_EQ(Interception::Core::D3D8Utils::get_method_info_ptr(APIInterceptor::APIFUNCTION_USER32_RELEASEDC),
              nullptr);
    EXPECT_EQ(Interception::Core::D3D8Utils::get_method_info_ptr(APIInterceptor::APIFUNCTION_UNKNOWN),
              nullptr);
}

TEST(D3D8Methods, LookupByVtableSlotRoundTrips)
{
    uint32_t                                     n_methods   = 0;
    const Interception::Hooks::D3D8::MethodInfo* methods_ptr = Interception::Core::D3D8Utils::get_method_info_array_ptr(&n_methods);

    for (uint32_t n_method = 0;
                  n_method < n_methods;
                ++n_method)
    {
        EXPECT_EQ(Interception::Core::D3D8Utils::get_api_function(methods_ptr[n_method].interface_type,
                                                                  methods_ptr[n_method].vtable_index),
                  methods_ptr[n_method].function) << methods_ptr[n_method].full_name_ptr;
    }

    EXPECT_EQ(Interception::Core::D3D8Utils::get_api_function(Interception::Hooks::D3D8::Interface::IDIRECT3DDEVICE8,
                                                              9999),
              APIInterceptor::APIFUNCTION_UNKNOWN);
    EXPECT_EQ(Interception::Core::D3D8Utils::get_api_function(Interception::Hooks::D3D8::Interface::IDIRECT3DDEVICE8,
                                                              Interception::Hooks::D3D8::VTABLE_INDEX_IDIRECT3DDEVICE8_PRESENT),
              APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_PRESENT);
}

TEST(D3D8Methods, NamesAreConsistent)
{
    struct NameCheck
    {
        const char* interface_tag_ptr;
        const char* interface_name_ptr;
        const char* method_tag_ptr;
        const char* method_name_ptr;
    };

    static const NameCheck name_check_array[] =
    {
        #define D3D8_METHOD(INTERFACE_TAG, interface_name, METHOD_TAG, method_name, vtable_index, return_type, parameters) { #INTERFACE_TAG, #interface_name, #METHOD_TAG, #method_name },
        #include "Interception/Hooks/D3D8/d3d8_methods.inl"
        #undef D3D8_METHOD
    };

    std::set<std::string>                        full_name_set;
    uint32_t                                     n_methods   = 0;
    const Interception::Hooks::D3D8::MethodInfo* methods_ptr = Interception::Core::D3D8Utils::get_method_info_array_ptr(&n_methods);

    ASSERT_EQ(n_methods,
              sizeof(name_check_array) / sizeof(name_check_array[0]) );

    for (uint32_t n_method = 0;
                  n_method < n_methods;
                ++n_method)
    {
        const auto&       name_check = name_check_array[n_method];
        const std::string full_name  = std::string(name_check.interface_name_ptr) + "::" + name_check.method_name_ptr;

        EXPECT_EQ(_stricmp(name_check.interface_tag_ptr,
                           name_check.interface_name_ptr),
                  0) << full_name;
        EXPECT_EQ(_stricmp(name_check.method_tag_ptr,
                           name_check.method_name_ptr),
                  0) << full_name;

        EXPECT_EQ(full_name,
                  std::string(methods_ptr[n_method].full_name_ptr) );
        EXPECT_EQ(std::string(name_check.interface_name_ptr),
                  std::string(Interception::Core::D3D8Utils::get_interface_name_ptr(methods_ptr[n_method].interface_type) ));
        EXPECT_EQ(std::string(name_check.method_name_ptr),
                  std::string(methods_ptr[n_method].method_name_ptr) );

        EXPECT_TRUE(full_name_set.insert(full_name).second) << "duplicate " << full_name;
    }
}

TEST(D3D8Methods, VtableSlotsAreContiguousForEveryInterface)
{
    uint32_t                                     n_methods   = 0;
    const Interception::Hooks::D3D8::MethodInfo* methods_ptr = Interception::Core::D3D8Utils::get_method_info_array_ptr(&n_methods);

    for (uint32_t n_interface = 0;
                  n_interface < static_cast<uint32_t>(Interception::Hooks::D3D8::Interface::COUNT);
                ++n_interface)
    {
        const auto            interface_type = static_cast<Interception::Hooks::D3D8::Interface>(n_interface);
        std::set<uint32_t>    slot_set;

        for (uint32_t n_method = 0;
                      n_method < n_methods;
                    ++n_method)
        {
            if (methods_ptr[n_method].interface_type == interface_type)
            {
                EXPECT_TRUE(slot_set.insert(methods_ptr[n_method].vtable_index).second) << "duplicate slot in "
                                                                                       << methods_ptr[n_method].full_name_ptr;
            }
        }

        ASSERT_EQ(slot_set.size(),
                  Interception::Core::D3D8Utils::get_n_methods(interface_type) ) << Interception::Core::D3D8Utils::get_interface_name_ptr(interface_type);
        EXPECT_EQ(*slot_set.begin(),
                  0u)                                 << Interception::Core::D3D8Utils::get_interface_name_ptr(interface_type);
        EXPECT_EQ(*slot_set.rbegin(),
                  Interception::Core::D3D8Utils::get_n_methods(interface_type) - 1) << Interception::Core::D3D8Utils::get_interface_name_ptr(interface_type);
    }
}
