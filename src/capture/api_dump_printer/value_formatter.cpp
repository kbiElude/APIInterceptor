/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "common/macros.h"
#include "value_formatter.h"
#include <sstream>
#include <stdio.h>
#include <string.h>

const uint32_t Capture::APIDumpPrinter::ValueFormatter::FVF_DIFFUSE                         = 0x00000040;
const uint32_t Capture::APIDumpPrinter::ValueFormatter::FVF_LAST_BETA_UBYTE4                = 0x00001000;
const uint32_t Capture::APIDumpPrinter::ValueFormatter::FVF_NORMAL                          = 0x00000010;
const uint32_t Capture::APIDumpPrinter::ValueFormatter::FVF_POSITION_MASK                   = 0x0000000e;
const uint32_t Capture::APIDumpPrinter::ValueFormatter::FVF_RESERVED_BIT                    = 0x00000020;
const uint32_t Capture::APIDumpPrinter::ValueFormatter::FVF_SPECULAR                        = 0x00000080;
const uint32_t Capture::APIDumpPrinter::ValueFormatter::FVF_TEXCOORD_SIZE_BASE_BIT          = 16; /* the size of the coordinates of stage 0; each stage has 2 more bits */
const uint32_t Capture::APIDumpPrinter::ValueFormatter::FVF_TEXCOORD_SIZE_BITS              = 2;
const uint32_t Capture::APIDumpPrinter::ValueFormatter::FVF_TEXCOORD_SIZE_MASK              = 0x00000003;
const uint32_t Capture::APIDumpPrinter::ValueFormatter::FVF_TEXCOUNT_MASK                   = 0x00000f00;
const uint32_t Capture::APIDumpPrinter::ValueFormatter::FVF_TEXCOUNT_SHIFT                  = 8;
const uint32_t Capture::APIDumpPrinter::ValueFormatter::TA_ALPHA_REPLICATE                  = 0x00000020;
const uint32_t Capture::APIDumpPrinter::ValueFormatter::TA_COMPLEMENT                       = 0x00000010;
const uint32_t Capture::APIDumpPrinter::ValueFormatter::TA_SELECT_MASK                      = 0x0000000f;
const uint32_t Capture::APIDumpPrinter::ValueFormatter::TCI_CAMERA_SPACE_NORMAL             = 0x00010000;
const uint32_t Capture::APIDumpPrinter::ValueFormatter::TCI_CAMERA_SPACE_POSITION           = 0x00020000;
const uint32_t Capture::APIDumpPrinter::ValueFormatter::TCI_CAMERA_SPACE_REFLECTION_VECTOR  = 0x00030000;
const uint32_t Capture::APIDumpPrinter::ValueFormatter::TCI_INDEX_MASK                      = 0x0000ffff;
const uint32_t Capture::APIDumpPrinter::ValueFormatter::TCI_MODE_MASK                       = 0xffff0000;
const uint32_t Capture::APIDumpPrinter::ValueFormatter::TTFF_COUNT_MASK                     = 0x000000ff;
const uint32_t Capture::APIDumpPrinter::ValueFormatter::TTFF_PROJECTED                      = 0x00000100;

std::string Capture::APIDumpPrinter::ValueFormatter::format_boolean(const int32_t& in_value)
{
    std::string result;

    switch (in_value)
    {
        case 0:
        {
            result = "FALSE";

            break;
        }

        case 1:
        {
            result = "TRUE";

            break;
        }

        default:
        {
            result = std::to_string(in_value);

            break;
        }
    }

    return result;
}

std::string Capture::APIDumpPrinter::ValueFormatter::format_color(const uint32_t& in_value)
{
    char buffer_i8vec16[16];

    snprintf(buffer_i8vec16,
             sizeof(buffer_i8vec16),
             "0x%08X",
             in_value);

    return buffer_i8vec16;
}

std::string Capture::APIDumpPrinter::ValueFormatter::format_enum(const ValueNameEntry* in_table_ptr,
                                                                 const uint32_t&       in_n_entries,
                                                                 const uint32_t&       in_value)
{
    std::string result = std::to_string(in_value);

    for (uint32_t n_entry = 0;
                  n_entry < in_n_entries;
                ++n_entry)
    {
        if (in_table_ptr[n_entry].value == in_value)
        {
            result = in_table_ptr[n_entry].name_ptr;

            break;
        }
    }

    return result;
}

std::string Capture::APIDumpPrinter::ValueFormatter::format_flags(const FlagNameEntry* in_table_ptr,
                                                                  const uint32_t&      in_n_entries,
                                                                  const uint32_t&      in_value)
{
    uint32_t    remaining = in_value;
    std::string result;

    for (uint32_t n_entry = 0;
                  n_entry < in_n_entries;
                ++n_entry)
    {
        if ((remaining & in_table_ptr[n_entry].mask) == in_table_ptr[n_entry].mask)
        {
            result    += (result.empty() ? "" : " | ");
            result    += in_table_ptr[n_entry].name_ptr;
            remaining &= ~in_table_ptr[n_entry].mask;
        }
    }

    if (remaining != 0)
    {
        result += (result.empty() ? "" : " | ");
        result += format_hex(remaining);
    }

    if (result.empty() )
    {
        result = "0";
    }

    return result;
}

std::string Capture::APIDumpPrinter::ValueFormatter::format_float(const uint32_t& in_value)
{
    float              value_fp32 = 0.0f;
    std::ostringstream stream;

    memcpy(&value_fp32,
           &in_value,
           sizeof(value_fp32) );

    stream << value_fp32;

    return stream.str();
}

std::string Capture::APIDumpPrinter::ValueFormatter::format_fvf(const uint32_t& in_value,
                                                                const FvfStyle& in_style)
{
    constexpr uint32_t SHADER_HANDLE_BIT = 1u << 31;

    std::string result;

    if (in_style.has_shader_handles          &&
        (in_value & SHADER_HANDLE_BIT) != 0)
    {
        result = "shader " + std::to_string(in_value);
    }
    else
    {
        static const ValueNameEntry position_name_array[] =
        {
            {"D3DFVF_XYZ",    0x2},
            {"D3DFVF_XYZRHW", 0x4},
            {"D3DFVF_XYZB1",  0x6},
            {"D3DFVF_XYZB2",  0x8},
            {"D3DFVF_XYZB3",  0xa},
            {"D3DFVF_XYZB4",  0xc},
            {"D3DFVF_XYZB5",  0xe}
        };

        const uint32_t n_tex_coord_sets = (in_value & FVF_TEXCOUNT_MASK) >> FVF_TEXCOUNT_SHIFT;

        result = "<no position>";

        for (const auto& position_name : position_name_array)
        {
            if (position_name.value == (in_value & FVF_POSITION_MASK) )
            {
                result = position_name.name_ptr;

                break;
            }
        }

        result += ((in_value & FVF_NORMAL)       != 0) ? " | D3DFVF_NORMAL"                                         : "";
        result += ((in_value & FVF_RESERVED_BIT) != 0) ? std::string(" | D3DFVF_") + in_style.reserved_bit_name_ptr : "";
        result += ((in_value & FVF_DIFFUSE)      != 0) ? " | D3DFVF_DIFFUSE"                                        : "";
        result += ((in_value & FVF_SPECULAR)     != 0) ? " | D3DFVF_SPECULAR"                                       : "";
        result += " | D3DFVF_TEX" + std::to_string(n_tex_coord_sets);

        /* Coordinates are 2 floats, unless the format says otherwise. */
        for (uint32_t n_stage = 0;
                      n_stage < n_tex_coord_sets;
                    ++n_stage)
        {
            /* The value is the code the format has for the number of floats; 2 is the default, which has no name. */
            static const ValueNameEntry n_floats_array[] =
            {
                {"1", 3},
                {"3", 1},
                {"4", 2}
            };

            const uint32_t size_code = (in_value >> (FVF_TEXCOORD_SIZE_BASE_BIT + n_stage * FVF_TEXCOORD_SIZE_BITS) ) & FVF_TEXCOORD_SIZE_MASK;

            for (const auto& n_floats : n_floats_array)
            {
                if (n_floats.value == size_code)
                {
                    result += std::string(" | D3DFVF_TEXCOORDSIZE") + n_floats.name_ptr + "(" + std::to_string(n_stage) + ")";

                    break;
                }
            }
        }

        result += ((in_value & FVF_LAST_BETA_UBYTE4) != 0) ? " | D3DFVF_LASTBETA_UBYTE4" : "";
    }

    return result;
}

std::string Capture::APIDumpPrinter::ValueFormatter::format_hex(const uint32_t& in_value)
{
    char buffer_i8vec16[16];

    snprintf(buffer_i8vec16,
             sizeof(buffer_i8vec16),
             "0x%X",
             in_value);

    return buffer_i8vec16;
}

std::string Capture::APIDumpPrinter::ValueFormatter::format_hresult(const ValueNameEntry* in_table_ptr,
                                                                    const uint32_t&       in_n_entries,
                                                                    const int32_t&        in_value)
{
    std::string result = format_hex(static_cast<uint32_t>(in_value) );

    for (uint32_t n_entry = 0;
                  n_entry < in_n_entries;
                ++n_entry)
    {
        if (in_table_ptr[n_entry].value == static_cast<uint32_t>(in_value) )
        {
            result = in_table_ptr[n_entry].name_ptr;

            break;
        }
    }

    return result;
}

std::string Capture::APIDumpPrinter::ValueFormatter::format_state_value(const StateValueInfo& in_info,
                                                                        const uint32_t&       in_value)
{
    std::string result = std::to_string(in_value);

    switch (in_info.format)
    {
        case StateValueFormat::BOOLEAN:
        {
            result = format_boolean(static_cast<int32_t>(in_value) );

            break;
        }

        case StateValueFormat::COLOR:
        {
            result = format_color(in_value);

            break;
        }

        case StateValueFormat::FLOAT:
        {
            result = format_float(in_value);

            break;
        }

        case StateValueFormat::HEX:
        {
            result = format_hex(in_value);

            break;
        }

        case StateValueFormat::NAME:
        {
            result = format_enum(in_info.table_ptr,
                                 in_info.n_entries,
                                 in_value);

            break;
        }

        case StateValueFormat::TEX_COORD_INDEX:
        {
            /* D3DTSS_TCI_PASSTHRU has no name here: it is the lack of a mode. */
            const ValueNameEntry mode_name_array[] =
            {
                {"D3DTSS_TCI_CAMERASPACENORMAL",           TCI_CAMERA_SPACE_NORMAL},
                {"D3DTSS_TCI_CAMERASPACEPOSITION",         TCI_CAMERA_SPACE_POSITION},
                {"D3DTSS_TCI_CAMERASPACEREFLECTIONVECTOR", TCI_CAMERA_SPACE_REFLECTION_VECTOR}
            };

            result = std::to_string(in_value & TCI_INDEX_MASK);

            for (const auto& mode_name : mode_name_array)
            {
                if (mode_name.value == (in_value & TCI_MODE_MASK) )
                {
                    result += std::string(" | ") + mode_name.name_ptr;

                    break;
                }
            }

            break;
        }

        case StateValueFormat::TEXTURE_ARGUMENT:
        {
            result = format_hex(in_value);

            for (uint32_t n_entry = 0;
                          n_entry < in_info.n_entries;
                        ++n_entry)
            {
                if (in_info.table_ptr[n_entry].value == (in_value & TA_SELECT_MASK) )
                {
                    result  = in_info.table_ptr[n_entry].name_ptr;
                    result += ((in_value & TA_COMPLEMENT)      != 0) ? " | D3DTA_COMPLEMENT"     : "";
                    result += ((in_value & TA_ALPHA_REPLICATE) != 0) ? " | D3DTA_ALPHAREPLICATE" : "";

                    break;
                }
            }

            break;
        }

        case StateValueFormat::TEXTURE_TRANSFORM_FLAGS:
        {
            const uint32_t n_coordinates = in_value & TTFF_COUNT_MASK;

            result  = (n_coordinates               == 0) ? "D3DTTFF_DISABLE"
                                                         : "D3DTTFF_COUNT" + std::to_string(n_coordinates);
            result += ((in_value & TTFF_PROJECTED) != 0) ? " | D3DTTFF_PROJECTED" 
                                                         : "";

            break;
        }

        case StateValueFormat::RAW:
        {
            /* Raw */
            break;
        }

        default:
        {
            AI_FAIL_UNSUPPORTED(in_info.format);

            break;
        }
    }

    return result;
}
