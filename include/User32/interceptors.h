/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef USER32_INTERCEPTORS_H
#define USER32_INTERCEPTORS_H

#include "Common/globals.h"
#include "Common/types.h"
#include <vector>

namespace User32
{
    extern std::vector<APIInterceptor::FunctionInterceptor> get_function_interceptors();
}

#endif /* USER32_INTERCEPTORS_H */