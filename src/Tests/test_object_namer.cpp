/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Checks of the names of the objects of a workload: by the order of creation, by the address when they were not seen being made, and
 * again after the object is gone.
 */
#include <gtest/gtest.h>
#include "Capture/APIDumpLoader/object_namer.h"

namespace
{
    constexpr uint64_t ADDRESS = 0x1000;
}

TEST(ObjectNamer, AnObjectIsNamedByTheOrderOfItsCreation)
{
    Capture::APIDumpLoader::ObjectNamer namer;

    namer.register_object(ADDRESS,
                          "Texture",
                          true); /* in_is_new */
    namer.register_object(ADDRESS + 8,
                          "Texture",
                          true); /* in_is_new */

    EXPECT_EQ(namer.get_name(ADDRESS,
                             "Texture"),
              "Texture#1");
    EXPECT_EQ(namer.get_name(ADDRESS + 8,
                             "Texture"),
              "Texture#2");
}

TEST(ObjectNamer, AnObjectWhichWasNotSeenBeingMadeIsNamedByItsAddress)
{
    Capture::APIDumpLoader::ObjectNamer namer;

    EXPECT_EQ(namer.get_name(ADDRESS,
                             "Surface"),
              "Surface@0x1000");
    EXPECT_EQ(namer.get_name(0,
                             "Surface"),
              "NULL");
}

TEST(ObjectNamer, AnAddressWhichIsReusedByANewObjectGetsANewName)
{
    Capture::APIDumpLoader::ObjectNamer namer;

    namer.register_object(ADDRESS,
                          "DirectDraw7",
                          true); /* in_is_new */
    namer.forget_object(ADDRESS);

    EXPECT_EQ(namer.get_name(ADDRESS,
                             "Surface"),
              "Surface@0x1000");

    /* An object that a Get call hands out is named by what it is, not by what had the address before. */
    namer.register_object(ADDRESS,
                          "Surface",
                          false); /* in_is_new */

    EXPECT_EQ(namer.get_name(ADDRESS,
                             "Surface"),
              "Surface#1");
}

TEST(ObjectNamer, OnlyTheLastReleaseMakesAnObjectForgotten)
{
    Capture::APIDumpLoader::ObjectNamer namer;
    Capture::APIDumpLoader::DumpedAPICall call;

    call.arg_in_vec.push_back(APIInterceptor::APIFunctionArgument::create_void_ptr(reinterpret_cast<void*>(ADDRESS) ) );

    namer.register_object(ADDRESS,
                          "Texture",
                          true); /* in_is_new */

    call.returned_value_ptr.reset(new APIInterceptor::APIFunctionArgument(APIInterceptor::APIFunctionArgument::create_u32(1) ) );
    namer.forget_after_release(call);

    EXPECT_EQ(namer.get_name(ADDRESS,
                             "Texture"),
              "Texture#1");

    call.returned_value_ptr.reset(new APIInterceptor::APIFunctionArgument(APIInterceptor::APIFunctionArgument::create_u32(0) ) );
    namer.forget_after_release(call);

    EXPECT_EQ(namer.get_name(ADDRESS,
                             "Texture"),
              "Texture@0x1000");
}
