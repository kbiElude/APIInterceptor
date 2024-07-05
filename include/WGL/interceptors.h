/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef WGL_INTERCEPTORS_H
#define WGL_INTERCEPTORS_H

#include "Common/globals.h"
#include <vector>

namespace WGL
{
    extern std::vector<APIInterceptor::FunctionInterceptor> get_function_interceptors();
}

#endif /* WGL_INTERCEPTORS_H */