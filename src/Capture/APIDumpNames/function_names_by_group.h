/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * The functions of the groups that have their names in a table of their own (see function_names.cpp).
 */
#ifndef APIDUMPNAMES_FUNCTION_NAMES_BY_GROUP_H
#define APIDUMPNAMES_FUNCTION_NAMES_BY_GROUP_H

#include "Common/types.h"

namespace Capture
{
    namespace APIDumpNames
    {
        /* Implemented in function_names_gl.cpp and function_names_win.cpp. Return nullptr if the function does not belong to the file. */
        const char* get_gl_function_name (const APIInterceptor::APIFunction& in_function);
        const char* get_win_function_name(const APIInterceptor::APIFunction& in_function);
    }
}

#endif /* APIDUMPNAMES_FUNCTION_NAMES_BY_GROUP_H */
