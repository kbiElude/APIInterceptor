/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Per-API knowledge of the printer: function names, API grouping and frame boundaries.
 */
#ifndef APIDUMPPRINTER_API_INFO_H
#define APIDUMPPRINTER_API_INFO_H

#include "types.h"

namespace APIDumpPrinter
{
    APIGroup    get_api_group     (const APIInterceptor::APIFunction& in_function);
    const char* get_api_group_name(const APIGroup&                    in_group);

    /* Returns "?!" for functions that are not recognized. */
    const char* get_function_name(const APIInterceptor::APIFunction& in_function);

    /* Implemented in names_gl.cpp / names_win.cpp. Return nullptr if the function does not belong to the file. */
    const char* get_gl_function_name (const APIInterceptor::APIFunction& in_function);
    const char* get_win_function_name(const APIInterceptor::APIFunction& in_function);

    /* True for calls which end a frame (a swapchain present). */
    bool is_frame_boundary(const APIInterceptor::APIFunction& in_function);

    bool parse_api_group_name(const char* in_name_ptr,
                              APIGroup*   out_group_ptr);
}

#endif /* APIDUMPPRINTER_API_INFO_H */
