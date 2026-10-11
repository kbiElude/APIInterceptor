/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "api_info.h"
#include <string.h>

APIDumpPrinter::FunctionNameTable::FunctionNameTable(const FunctionNameEntry* in_entry_array_ptr,
                                                     size_t                   in_n_entries)
{
    for (size_t n_entry = 0;
                n_entry < in_n_entries;
              ++n_entry)
    {
        m_name_map[static_cast<uint32_t>(in_entry_array_ptr[n_entry].func)] = in_entry_array_ptr[n_entry].name_ptr;
    }
}

const char* APIDumpPrinter::FunctionNameTable::get_name(const APIInterceptor::APIFunction& in_func) const
{
    const auto  iterator   = m_name_map.find(static_cast<uint32_t>(in_func) );
    const char* result_ptr = nullptr;

    if (iterator != m_name_map.end() )
    {
        result_ptr = iterator->second;
    }

    return result_ptr;
}

APIDumpPrinter::APIGroup APIDumpPrinter::get_api_group(const APIInterceptor::APIFunction& in_func)
{
    APIGroup result = APIGroup::Unknown;

    if (in_func >= APIInterceptor::APIFUNCTION_GDI32_FIRST &&
        in_func <= APIInterceptor::APIFUNCTION_GDI32_LAST)
    {
        result = APIGroup::GDI32;
    }
    else
    if (in_func >= APIInterceptor::APIFUNCTION_GL_FIRST &&
        in_func <= APIInterceptor::APIFUNCTION_GL_LAST)
    {
        result = APIGroup::GL;
    }
    else
    if (in_func >= APIInterceptor::APIFUNCTION_WGL_FIRST &&
        in_func <= APIInterceptor::APIFUNCTION_WGL_LAST)
    {
        result = APIGroup::WGL;
    }
    else
    if (in_func >= APIInterceptor::APIFUNCTION_USER32_FIRST &&
        in_func <= APIInterceptor::APIFUNCTION_USER32_LAST)
    {
        result = APIGroup::USER32;
    }

    return result;
}

const char* APIDumpPrinter::get_api_group_name(const APIGroup& in_group)
{
    const char* result_ptr = "unknown";

    switch (in_group)
    {
        case APIGroup::GDI32:
        {
            result_ptr = "gdi32";

            break;
        }

        case APIGroup::GL:
        {
            result_ptr = "gl";

            break;
        }

        case APIGroup::WGL:
        {
            result_ptr = "wgl";

            break;
        }

        case APIGroup::USER32:
        {
            result_ptr = "user32";

            break;
        }

        default:
        {
            break;
        }
    }

    return result_ptr;
}

const char* APIDumpPrinter::get_function_name(const APIInterceptor::APIFunction& in_func)
{
    const char* result_ptr = nullptr;

    switch (get_api_group(in_func) )
    {
        case APIGroup::GL:
        {
            result_ptr = get_gl_function_name(in_func);

            break;
        }

        case APIGroup::GDI32:
        case APIGroup::WGL:
        case APIGroup::USER32:
        {
            result_ptr = get_win_function_name(in_func);

            break;
        }

        default:
        {
            break;
        }
    }

    return (result_ptr != nullptr) ? result_ptr
                                   : "?!";
}

bool APIDumpPrinter::is_frame_boundary(const APIInterceptor::APIFunction& in_func)
{
    return in_func == APIInterceptor::APIFUNCTION_GDI32_SWAPBUFFERS;
}

bool APIDumpPrinter::parse_api_group_name(const char* in_name_ptr,
                                          APIGroup*   out_group_ptr)
{
    bool result = false;

    for (APIGroup group  = APIGroup::GDI32;
                  group != APIGroup::Unknown;
                  group  = static_cast<APIGroup>(static_cast<int>(group) + 1) )
    {
        if (_stricmp(in_name_ptr,
                     get_api_group_name(group) ) == 0)
        {
            *out_group_ptr = group;
            result         = true;

            break;
        }
    }

    return result;
}
