/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Per-API knowledge needed by the printer: function names, API grouping and frame boundaries.
 * Support for a new API is added by extending APIGroup, the lookups in api_info.cpp, and adding
 * a names_<api>.cpp file holding a FunctionNameEntry table.
 */
#ifndef APIDUMPPRINTER_API_INFO_H
#define APIDUMPPRINTER_API_INFO_H

#include "Common/types.h"
#include <unordered_map>

namespace APIDumpPrinter
{
    enum class APIGroup
    {
        GDI32,
        GL,
        WGL,
        USER32,

        Unknown
    };

    struct FunctionNameEntry
    {
        APIInterceptor::APIFunction func;
        const char*                 name_ptr;
    };

    /* Maps API functions to their names. Built once from a FunctionNameEntry array. */
    class FunctionNameTable
    {
    public:
        FunctionNameTable(const FunctionNameEntry* in_entry_array_ptr,
                          size_t                   in_n_entries);

        /* Returns nullptr if the function is not in the table. */
        const char* get_name(const APIInterceptor::APIFunction& in_func) const;

    private:
        std::unordered_map<uint32_t, const char*> m_name_map;
    };

    APIGroup    get_api_group     (const APIInterceptor::APIFunction& in_func);
    const char* get_api_group_name(const APIGroup&                    in_group);

    /* Returns "?!" for functions that are not recognized. */
    const char* get_function_name(const APIInterceptor::APIFunction& in_func);

    /* Implemented in names_gl.cpp / names_win.cpp. Return nullptr if the function does not belong to the file. */
    const char* get_gl_function_name (const APIInterceptor::APIFunction& in_func);
    const char* get_win_function_name(const APIInterceptor::APIFunction& in_func);

    /* True for calls which end a frame (a swapchain present). */
    bool is_frame_boundary(const APIInterceptor::APIFunction& in_func);

    bool parse_api_group_name(const char* in_name_ptr,
                              APIGroup*   out_group_ptr);
}

#endif /* APIDUMPPRINTER_API_INFO_H */
