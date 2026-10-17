/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Per-API knowledge of the printer: function names.
 */
#ifndef APIDUMPPRINTER_API_INFO_H
#define APIDUMPPRINTER_API_INFO_H

#include "APIDumpLoader/api_info.h"
#include "types.h"

namespace APIDumpPrinter
{
    /* Returns "?!" for functions that are not recognized. */
    const char* get_function_name(const APIInterceptor::APIFunction& in_function);

    /* Implemented in names_gl.cpp / names_win.cpp. Return nullptr if the function does not belong to the file. */
    const char* get_gl_function_name (const APIInterceptor::APIFunction& in_function);
    const char* get_win_function_name(const APIInterceptor::APIFunction& in_function);
}

#endif /* APIDUMPPRINTER_API_INFO_H */
