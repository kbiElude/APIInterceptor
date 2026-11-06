/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Looks up D3D7 and D3D8 argument descriptions for the tests.
 */
#ifndef TESTS_ARGUMENT_INFO_CHECKER_H
#define TESTS_ARGUMENT_INFO_CHECKER_H

#include "interception/hooks/D3D7/types.h"
#include "interception/hooks/D3D8/types.h"

namespace Tests
{
    class ArgumentInfoChecker
    {
    public:
        /* Fails the running test if the argument has no description. */
        static Interception::Hooks::D3D8::ArgumentInfo get_argument_info_or_fail(const APIInterceptor::APIFunction& in_function,
                                                                                 const uint32_t&                    in_n_argument);

        static Interception::Hooks::D3D7::ArgumentInfo get_d3d7_argument_info_or_fail(const APIInterceptor::APIFunction& in_function,
                                                                                      const uint32_t&                    in_n_argument);
    };
}

#endif /* TESTS_ARGUMENT_INFO_CHECKER_H */
