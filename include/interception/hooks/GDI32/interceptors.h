/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef GDI32_INTERCEPTORS_H
#define GDI32_INTERCEPTORS_H

#include "common/globals.h"
#include "common/types.h"
#include <vector>

namespace Interception
{
    namespace Hooks
    {
        namespace GDI32
        {
            extern std::vector<APIInterceptor::FunctionInterceptor> get_function_interceptors();
        }
    }
}

#endif /* GDI32_INTERCEPTORS_H */