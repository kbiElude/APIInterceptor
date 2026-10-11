/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef APIDUMPPRINTER_FUNCTION_NAME_TABLE_H
#define APIDUMPPRINTER_FUNCTION_NAME_TABLE_H

#include "types.h"
#include <unordered_map>

namespace APIDumpPrinter
{
    /* Maps API functions to their names. Built once from a FunctionNameEntry array. */
    class FunctionNameTable
    {
    public:
        FunctionNameTable(const FunctionNameEntry* in_entry_array_ptr,
                          size_t                   in_n_entries);

        /* Returns nullptr if the function is not in the table. */
        const char* get_name(const APIInterceptor::APIFunction& in_function) const;

    private:
        std::unordered_map<uint32_t, const char*> m_name_map;
    };
}

#endif /* APIDUMPPRINTER_FUNCTION_NAME_TABLE_H */
