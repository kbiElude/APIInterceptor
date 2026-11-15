/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef KERNEL32_INTERCEPTORS_H
#define KERNEL32_INTERCEPTORS_H

#include "common/globals.h"
#include <vector>

namespace Interception
{
    namespace Hooks
    {
        namespace Kernel32
        {
            extern std::vector<APIInterceptor::FunctionHookTarget> get_function_interceptors();
        }
    }
}

#endif /* KERNEL32_INTERCEPTORS_H */
