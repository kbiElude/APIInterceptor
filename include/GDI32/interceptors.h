/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef GDI32_INTERCEPTORS_H
#define GDI32_INTERCEPTORS_H

#include "Common/globals.h"
#include "Common/types.h"
#include <vector>

namespace GDI32
{
    extern std::vector<APIInterceptor::FunctionInterceptor> get_function_interceptors();
}

#endif /* GDI32_INTERCEPTORS_H */