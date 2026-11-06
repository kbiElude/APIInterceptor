/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * The text of the values which the APIs of Direct3D 7 and 8 have in common: booleans, colors, enums and flags by name from a table,
 * flexible vertex formats, and the values of render states and of texture stage states.
 */
#ifndef APIDUMPPRINTER_VALUE_FORMATTER_H
#define APIDUMPPRINTER_VALUE_FORMATTER_H

#include "types.h"
#include <stdint.h>
#include <string>

namespace Capture
{
    namespace APIDumpPrinter
    {
        class ValueFormatter
        {
        public:
            /* What differs in the vertex formats of the APIs. */
            struct FvfStyle
            {
                const char* reserved_bit_name_ptr;    /* the bit after the normal: PSIZE in Direct3D 8, RESERVED1 in Direct3D 7 */
                bool        has_shader_handles;       /* a value with the highest bit set is a vertex shader handle (Direct3D 8) */
            };

            static std::string format_boolean    (const int32_t&         in_value);
            static std::string format_color      (const uint32_t&        in_value);
            static std::string format_enum       (const ValueNameEntry*  in_table_ptr,
                                                  const uint32_t&        in_n_entries,
                                                  const uint32_t&        in_value);
            static std::string format_flags      (const FlagNameEntry*   in_table_ptr,
                                                  const uint32_t&        in_n_entries,
                                                  const uint32_t&        in_value);
            static std::string format_float      (const uint32_t&        in_value);
            static std::string format_fvf        (const uint32_t&        in_value,
                                                  const FvfStyle&        in_style);
            static std::string format_hex        (const uint32_t&        in_value);
            static std::string format_hresult    (const ValueNameEntry*  in_table_ptr,
                                                  const uint32_t&        in_n_entries,
                                                  const int32_t&         in_value);
            static std::string format_state_value(const StateValueInfo&  in_info,
                                                  const uint32_t&        in_value);

        private:
            static const uint32_t FVF_DIFFUSE;
            static const uint32_t FVF_LAST_BETA_UBYTE4;
            static const uint32_t FVF_NORMAL;
            static const uint32_t FVF_POSITION_MASK;
            static const uint32_t FVF_RESERVED_BIT;
            static const uint32_t FVF_SPECULAR;
            static const uint32_t FVF_TEXCOORD_SIZE_BASE_BIT;
            static const uint32_t FVF_TEXCOORD_SIZE_BITS;
            static const uint32_t FVF_TEXCOORD_SIZE_MASK;
            static const uint32_t FVF_TEXCOUNT_MASK;
            static const uint32_t FVF_TEXCOUNT_SHIFT;
            static const uint32_t TA_ALPHA_REPLICATE;
            static const uint32_t TA_COMPLEMENT;
            static const uint32_t TA_SELECT_MASK;
            static const uint32_t TCI_CAMERA_SPACE_NORMAL;
            static const uint32_t TCI_CAMERA_SPACE_POSITION;
            static const uint32_t TCI_CAMERA_SPACE_REFLECTION_VECTOR;
            static const uint32_t TCI_INDEX_MASK;
            static const uint32_t TCI_MODE_MASK;
            static const uint32_t TTFF_COUNT_MASK;
            static const uint32_t TTFF_PROJECTED;
        };
    }
}

#endif /* APIDUMPPRINTER_VALUE_FORMATTER_H */
