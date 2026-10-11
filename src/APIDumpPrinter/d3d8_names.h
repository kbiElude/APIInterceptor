/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Names of D3D8 enums and flags (defined in names_d3d8.cpp).
 */
#ifndef APIDUMPPRINTER_D3D8_NAMES_H
#define APIDUMPPRINTER_D3D8_NAMES_H

#include "D3D8/types.h"
#include "types.h"

namespace APIDumpPrinter
{
    /* Each function returns false if the kind (or state) has no table. */
    bool get_flag_name_table                (const D3D8::ValueKind& in_kind,
                                             const FlagNameEntry**  out_table_ptr_ptr,
                                             uint32_t*              out_n_entries_ptr);
    bool get_render_state_value_info        (const uint32_t&        in_render_state,
                                             StateValueInfo*        out_info_ptr);
    bool get_texture_stage_state_value_info (const uint32_t&        in_texture_stage_state,
                                             StateValueInfo*        out_info_ptr);
    bool get_value_name_table               (const D3D8::ValueKind& in_kind,
                                             const ValueNameEntry** out_table_ptr_ptr,
                                             uint32_t*              out_n_entries_ptr);
}

#endif /* APIDUMPPRINTER_D3D8_NAMES_H */
