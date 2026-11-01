/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "function_name_table.h"

APIDumpPrinter::FunctionNameTable::FunctionNameTable(const FunctionNameEntry* in_entry_array_ptr,
                                                     size_t                   in_n_entries)
{
    for (size_t n_entry = 0;
                n_entry < in_n_entries;
              ++n_entry)
    {
        m_name_map[static_cast<uint32_t>(in_entry_array_ptr[n_entry].function)] = in_entry_array_ptr[n_entry].name_ptr;
    }
}

const char* APIDumpPrinter::FunctionNameTable::get_name(const APIInterceptor::APIFunction& in_function) const
{
    const auto  iterator   = m_name_map.find(static_cast<uint32_t>(in_function) );
    const char* result_ptr = nullptr;

    if (iterator != m_name_map.end() )
    {
        result_ptr = iterator->second;
    }

    return result_ptr;
}
