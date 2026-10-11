/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include <gtest/gtest.h>
#include "D3D8Utils/argument_info.h"
#include "argument_info_checker.h"

D3D8::ArgumentInfo Tests::ArgumentInfoChecker::get_argument_info_or_fail(const APIInterceptor::APIFunction& in_function,
                                                                         const uint32_t&                    in_n_argument)
{
    D3D8::ArgumentInfo result = {};

    EXPECT_TRUE(D3D8::Utils::get_argument_info(in_function,
                                               in_n_argument,
                                              &result) );

    return result;
}
