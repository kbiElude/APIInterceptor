/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef APIDUMPPRINTER_TYPES_H
#define APIDUMPPRINTER_TYPES_H

#include "capture/api_dump_loader/api_info.h"
#include "common/types.h"
#include <set>
#include <string>

namespace Capture
{
    namespace APIDumpPrinter
    {
        /* The sets of flags of D3D7: those that arguments hold, and those in the fields of the structures. */
        enum class D3D7FlagTable
        {
            BLT,
            BLT_FAST,
            CLEAR,
            COLOR_KEY,
            COOPERATIVE_LEVEL,
            DEVICE_CAPS,
            DIRECT_DRAW_CAPS,
            DIRECT_DRAW_CAPS2,
            DRAW,
            ENUM_DISPLAY_MODES,
            ENUM_SURFACES,
            FLIP,
            LOCK,
            OVERLAY,
            PALETTE,
            PIXEL_FORMAT,
            SET_DISPLAY_MODE,
            SURFACE_CAPS,
            SURFACE_CAPS2,
            SURFACE_DESC,
            VERTEX_OPERATION,
            WAIT_FOR_VERTICAL_BLANK
        };

        struct FlagNameEntry
        {
            uint32_t    mask;
            const char* name_ptr;
        };

        struct Options
        {
            std::set<Capture::APIDumpLoader::APIGroup> allowed_api_group_set;          /* empty = all */
            std::string                                chunk_dump_directory;
            const char*                                compare_filename_ptr       = nullptr;
            uint32_t                                   first_frame                = 0;
            uint32_t                                   last_frame                 = UINT32_MAX;
            bool                                       lists_unreplayed_functions = false;
            bool                                       makes_index_only           = false;
            uint32_t                                   n_hexdump_bytes            = 0;
            bool                                       show_statistics            = false;
            bool                                       verifies_replay            = false;
            const char*                                workload_filename_ptr      = nullptr;
        };

        enum class SharedNameTable
        {
            BLEND,
            CMP_FUNC,
            CULL,
            FILL_MODE,
            FOG_MODE,
            MATERIAL_COLOR_SOURCE,
            PRIMITIVE_TYPE,
            SHADE_MODE,
            STATE_BLOCK_TYPE,
            STENCIL_OP,
            TEXTURE_ADDRESS,
            TEXTURE_ARGUMENT,
            TEXTURE_OP,
            Z_BUFFER_TYPE
        };

        /* How the value of a render state or of a texture stage state is printed. */
        enum class StateValueFormat
        {
            BOOLEAN,
            COLOR,
            FLOAT,
            HEX,
            NAME,
            RAW,
            TEX_COORD_INDEX,
            TEXTURE_ARGUMENT,
            TEXTURE_TRANSFORM_FLAGS
        };

        struct ValueNameEntry
        {
            const char* name_ptr;
            uint32_t    value;
        };

        /* Follows ValueNameEntry, which it depends on. */
        struct StateValueInfo
        {
            StateValueFormat      format    = StateValueFormat::RAW;
            uint32_t              n_entries = 0;
            const ValueNameEntry* table_ptr = nullptr; /* for StateValueFormat::NAME and ::TextureArgument */
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
}

#endif /* APIDUMPPRINTER_TYPES_H */
