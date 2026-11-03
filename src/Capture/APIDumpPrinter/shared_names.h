/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * The names of the enums which Direct3D 7 and 8 have the same, with the same values.
 */
#ifndef APIDUMPPRINTER_SHARED_NAMES_H
#define APIDUMPPRINTER_SHARED_NAMES_H

#include "types.h"

namespace Capture
{
    namespace APIDumpPrinter
    {
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

        struct NameTable
        {
            const ValueNameEntry* table_ptr;
            uint32_t              n_entries;
        };

        NameTable get_shared_name_table(const SharedNameTable& in_table);
    }
}

#endif /* APIDUMPPRINTER_SHARED_NAMES_H */
