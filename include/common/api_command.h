/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * An API function with the arguments it was called with.
 */
#ifndef COMMON_API_COMMAND_H
#define COMMON_API_COMMAND_H

#include "common/api_function_argument.h"
#include "common/types.h"
#include <vector>

namespace APIInterceptor
{
    struct APICommand
    {
        APIFunction                      api_func;
        std::vector<APIFunctionArgument> api_arg_vec;

        APICommand()
            :api_func(APIInterceptor::APIFUNCTION_UNKNOWN)
        {
            /* Stub */
        }
    };
}

#endif /* COMMON_API_COMMAND_H */
