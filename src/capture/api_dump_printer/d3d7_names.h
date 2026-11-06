/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Names of D3D7 (DirectDraw 7 and Direct3D 7) enums and flags, with the values of the DirectX 7 headers.
 */
#ifndef APIDUMPPRINTER_D3D7_NAMES_H
#define APIDUMPPRINTER_D3D7_NAMES_H

#include "interception/hooks/D3D7/types.h"
#include "types.h"

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

        class D3D7Names
        {
        public:
            /* Each function returns false if the kind (or state) has no table. */
            static bool get_flag_name_table               (const D3D7FlagTable&                         in_table,
                                                           const FlagNameEntry**                        out_table_ptr_ptr,
                                                           uint32_t*                                    out_n_entries_ptr);
            static bool get_hresult_name_table            (const ValueNameEntry**                       out_table_ptr_ptr,
                                                           uint32_t*                                    out_n_entries_ptr);
            static bool get_render_state_value_info       (const uint32_t&                              in_render_state,
                                                           StateValueInfo*                              out_info_ptr);
            static bool get_texture_stage_state_value_info(const uint32_t&                              in_texture_stage_state,
                                                           StateValueInfo*                              out_info_ptr);
            static bool get_value_name_table              (const Interception::Hooks::D3D7::ValueKind&  in_kind,
                                                           const ValueNameEntry**                       out_table_ptr_ptr,
                                                           uint32_t*                                    out_n_entries_ptr);

        private:
            /* The tables of the values of the states, which are the ones of the states themselves (see shared_names.h too). */
            enum class StateValueTable
            {
                NONE,
                BLEND,
                CMP_FUNC,
                CULL,
                FILL_MODE,
                FOG_MODE,
                MATERIAL_COLOR_SOURCE,
                SHADE_MODE,
                STENCIL_OP,
                TEXTURE_ADDRESS,
                TEXTURE_ARGUMENT,
                TEXTURE_BLEND,
                TEXTURE_FILTER_MAG,
                TEXTURE_FILTER_MAG_LEGACY,
                TEXTURE_FILTER_MIN,
                TEXTURE_FILTER_MIP,
                TEXTURE_OP,
                Z_BUFFER_TYPE
            };

            struct StateValueEntry
            {
                uint32_t         state;
                StateValueFormat format;
                StateValueTable  table;
            };

            static bool get_state_value_info(const StateValueEntry* in_entry_array_ptr,
                                             const uint32_t&        in_n_entries,
                                             const uint32_t&        in_state,
                                             StateValueInfo*        out_info_ptr);
        };
    }
}

#endif /* APIDUMPPRINTER_D3D7_NAMES_H */
