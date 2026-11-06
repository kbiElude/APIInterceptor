/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef COMMON_UTILS_H
#define COMMON_UTILS_H

#include "types.h"
#include <string>

namespace APIInterceptor
{
    void convert_api_command_to_string(const APICommand& in_api_command,
                                       std::string*      out_string_ptr);
}

#endif /* COMMON_UTILS_H */