/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef APIDUMPPRINTER_TYPES_H
#define APIDUMPPRINTER_TYPES_H

#include "Common/types.h"
#include <set>
#include <string>

namespace APIDumpPrinter
{
    enum class APIGroup
    {
        GDI32,
        GL,
        WGL,
        USER32,
        D3D8,

        Unknown
    };

    struct FlagNameEntry
    {
        uint32_t    mask;
        const char* name_ptr;
    };

    struct FunctionNameEntry
    {
        APIInterceptor::APIFunction function;
        const char*                 name_ptr;
    };

    struct Options
    {
        std::set<APIGroup> allowed_api_group_set; /* empty = all */
        std::string        chunk_dump_directory;
        uint32_t           first_frame           = 0;
        uint32_t           last_frame            = UINT32_MAX;
        uint32_t           n_hexdump_bytes       = 0;
        bool               show_statistics       = false;
        const char*        workload_filename_ptr = nullptr;
    };

    /* How the value of a render state or of a texture stage state is printed. */
    enum class StateValueFormat
    {
        Boolean,
        Color,
        Float,
        Hex,
        Name,
        Raw,
        TexCoordIndex,
        TextureArgument,
        TextureTransformFlags
    };

    struct ValueNameEntry
    {
        const char* name_ptr;
        uint32_t    value;
    };

    /* Follows ValueNameEntry, which it depends on. */
    struct StateValueInfo
    {
        StateValueFormat      format    = StateValueFormat::Raw;
        uint32_t              n_entries = 0;
        const ValueNameEntry* table_ptr = nullptr; /* for StateValueFormat::Name and ::TextureArgument */
    };

    /* What a workload holds, summed over all of its segments. */
    struct WorkloadTotals
    {
        uint32_t n_api_calls        = 0;
        uint64_t n_data_chunk_bytes = 0;
        uint32_t n_data_chunks      = 0;
        uint32_t n_surfaces         = 0;
    };
}

#endif /* APIDUMPPRINTER_TYPES_H */
