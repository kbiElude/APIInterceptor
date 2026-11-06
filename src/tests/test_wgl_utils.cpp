/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Checks of the helpers for the WGL entrypoints.
 */
#include <gtest/gtest.h>
#include "interception/hooks/WGL/utils.h"

TEST(WGLUtils, NullAttribListHasNoInts)
{
    EXPECT_EQ(Interception::Hooks::WGL::Utils::get_n_context_attrib_list_ints(nullptr),
              0u);
}

TEST(WGLUtils, EmptyAttribListIsJustTheTerminator)
{
    const int attrib_list_i32vec1[] = {0};

    EXPECT_EQ(Interception::Hooks::WGL::Utils::get_n_context_attrib_list_ints(attrib_list_i32vec1),
              1u);
}

TEST(WGLUtils, AttribListCountsPairsAndTheTerminator)
{
    const int attrib_list_i32vec7[] = {0x2091, 3, 0x2092, 3, 0x9126, 1, 0};

    EXPECT_EQ(Interception::Hooks::WGL::Utils::get_n_context_attrib_list_ints(attrib_list_i32vec7),
              7u);
}

TEST(WGLUtils, ValuesOfZeroDoNotEndTheList)
{
    const int attrib_list_i32vec5[] = {0x2094, 0, 0x2093, 0, 0};

    EXPECT_EQ(Interception::Hooks::WGL::Utils::get_n_context_attrib_list_ints(attrib_list_i32vec5),
              5u);
}
