/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "d3d8_decoder.h"
#include "d3d8_names.h"
#include "D3D8Utils/argument_info.h"
#include "D3D8Utils/methods.h"
#include <sstream>
#include <string.h>

std::string APIDumpPrinter::D3D8Decoder::format_boolean(const int32_t& in_value)
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

std::string APIDumpPrinter::D3D8Decoder::format_color(const uint32_t& in_value)
{
    char buffer_i8vec16[16];

    snprintf(buffer_i8vec16,
             sizeof(buffer_i8vec16),
             "0x%08X",
             in_value);

    return buffer_i8vec16;
}

std::string APIDumpPrinter::D3D8Decoder::format_color_value(const D3D8::D3DCOLORVALUE& in_value)
{
    std::ostringstream stream;

    stream << "(" << in_value.r << " " << in_value.g << " " << in_value.b << " " << in_value.a << ")";

    return stream.str();
}

std::string APIDumpPrinter::D3D8Decoder::format_enum(const D3D8::ValueKind& in_kind,
                                                     const uint32_t&        in_value)
{
    const ValueNameEntry* table_ptr = nullptr;
    uint32_t              n_entries = 0;
    std::string           result    = std::to_string(in_value);

    if (get_value_name_table(in_kind,
                            &table_ptr,
                            &n_entries) )
    {
        for (uint32_t n_entry = 0;
                      n_entry < n_entries;
                    ++n_entry)
        {
            if (table_ptr[n_entry].value == in_value)
            {
                result = table_ptr[n_entry].name_ptr;

                break;
            }
        }
    }

    return result;
}

std::string APIDumpPrinter::D3D8Decoder::format_flags(const D3D8::ValueKind& in_kind,
                                                      const uint32_t&        in_value)
{
    const FlagNameEntry* table_ptr = nullptr;
    uint32_t             n_entries = 0;
    uint32_t             remaining = in_value;
    std::string          result;

    if (get_flag_name_table(in_kind,
                           &table_ptr,
                           &n_entries) )
    {
        for (uint32_t n_entry = 0;
                      n_entry < n_entries;
                    ++n_entry)
        {
            if ((remaining & table_ptr[n_entry].mask) == table_ptr[n_entry].mask)
            {
                result    += (result.empty() ? "" : " | ");
                result    += table_ptr[n_entry].name_ptr;
                remaining &= ~table_ptr[n_entry].mask;
            }
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

std::string APIDumpPrinter::D3D8Decoder::format_fvf(const uint32_t& in_value)
{
    /* A vertex shader handle has the highest bit set; a FVF never does. */
    constexpr uint32_t VERTEX_SHADER_HANDLE_BIT = 1u << 31;

    std::string result;

    if ((in_value & VERTEX_SHADER_HANDLE_BIT) != 0)
    {
        result = "shader " + std::to_string(in_value);
    }
    else
    {
        const uint32_t n_tex_coord_sets = (in_value & D3D8::D3DFVF_TEXCOUNT_MASK) >> D3D8::D3DFVF_TEXCOUNT_SHIFT;

        switch (in_value & D3D8::D3DFVF_POSITION_MASK)
        {
            case D3D8::D3DFVF_XYZ:
            {
                result = "D3DFVF_XYZ";

                break;
            }

            case D3D8::D3DFVF_XYZRHW:
            {
                result = "D3DFVF_XYZRHW";

                break;
            }

            case D3D8::D3DFVF_XYZB1:
            {
                result = "D3DFVF_XYZB1";

                break;
            }

            case D3D8::D3DFVF_XYZB2:
            {
                result = "D3DFVF_XYZB2";

                break;
            }

            case D3D8::D3DFVF_XYZB3:
            {
                result = "D3DFVF_XYZB3";

                break;
            }

            case D3D8::D3DFVF_XYZB4:
            {
                result = "D3DFVF_XYZB4";

                break;
            }

            case D3D8::D3DFVF_XYZB5:
            {
                result = "D3DFVF_XYZB5";

                break;
            }

            default:
            {
                result = "<no position>";

                break;
            }
        }

        result += ((in_value & D3D8::D3DFVF_NORMAL)   != 0) ? " | D3DFVF_NORMAL"   : "";
        result += ((in_value & D3D8::D3DFVF_PSIZE)    != 0) ? " | D3DFVF_PSIZE"    : "";
        result += ((in_value & D3D8::D3DFVF_DIFFUSE)  != 0) ? " | D3DFVF_DIFFUSE"  : "";
        result += ((in_value & D3D8::D3DFVF_SPECULAR) != 0) ? " | D3DFVF_SPECULAR" : "";
        result += " | D3DFVF_TEX" + std::to_string(n_tex_coord_sets);
        result += ((in_value & D3D8::D3DFVF_LASTBETA_UBYTE4) != 0) ? " | D3DFVF_LASTBETA_UBYTE4" : "";
    }

    return result;
}

std::string APIDumpPrinter::D3D8Decoder::format_hex(const uint32_t& in_value)
{
    char buffer_i8vec16[16];

    snprintf(buffer_i8vec16,
             sizeof(buffer_i8vec16),
             "0x%X",
             in_value);

    return buffer_i8vec16;
}

std::string APIDumpPrinter::D3D8Decoder::format_hresult(const int32_t& in_value)
{
    /* HRESULTs returned by D3D8. */
    static const ValueNameEntry hresult_name_array[] =
    {
        {"S_OK",                                    0x00000000},
        {"S_FALSE",                                 0x00000001},
        {"E_NOINTERFACE",                           0x80004002},
        {"E_FAIL",                                  0x80004005},
        {"E_OUTOFMEMORY",                           0x8007000E},
        {"E_INVALIDARG",                            0x80070057},
        {"D3DERR_OUTOFVIDEOMEMORY",                 0x8876017C},
        {"D3DERR_WASSTILLDRAWING",                  0x8876021C},
        {"D3DERR_WRONGTEXTUREFORMAT",               0x88760818},
        {"D3DERR_UNSUPPORTEDCOLOROPERATION",        0x88760819},
        {"D3DERR_UNSUPPORTEDCOLORARG",              0x8876081A},
        {"D3DERR_UNSUPPORTEDALPHAOPERATION",        0x8876081B},
        {"D3DERR_UNSUPPORTEDALPHAARG",              0x8876081C},
        {"D3DERR_TOOMANYOPERATIONS",                0x8876081D},
        {"D3DERR_CONFLICTINGTEXTUREFILTER",         0x8876081E},
        {"D3DERR_UNSUPPORTEDFACTORVALUE",           0x8876081F},
        {"D3DERR_CONFLICTINGRENDERSTATE",           0x88760821},
        {"D3DERR_UNSUPPORTEDTEXTUREFILTER",         0x88760822},
        {"D3DERR_CONFLICTINGTEXTUREPALETTE",        0x88760826},
        {"D3DERR_DRIVERINTERNALERROR",              0x88760827},
        {"D3DERR_NOTFOUND",                         0x88760866},
        {"D3DERR_MOREDATA",                         0x88760867},
        {"D3DERR_DEVICELOST",                       0x88760868},
        {"D3DERR_DEVICENOTRESET",                   0x88760869},
        {"D3DERR_NOTAVAILABLE",                     0x8876086A},
        {"D3DERR_INVALIDDEVICE",                    0x8876086B},
        {"D3DERR_INVALIDCALL",                      0x8876086C},
        {"D3DERR_DRIVERINVALIDCALL",                0x8876086D},
    };

    std::string result = format_hex(static_cast<uint32_t>(in_value) );

    for (const auto& current_entry : hresult_name_array)
    {
        if (current_entry.value == static_cast<uint32_t>(in_value) )
        {
            result = current_entry.name_ptr;

            break;
        }
    }

    return result;
}

std::string APIDumpPrinter::D3D8Decoder::format_resource_properties(const uint32_t& in_format,
                                                                    const uint32_t& in_type,
                                                                    const uint32_t& in_usage,
                                                                    const uint32_t& in_pool)
{
    const std::string format_name = format_enum(D3D8::ValueKind::Format,
                                                in_format);
    const std::string pool_name   = format_enum(D3D8::ValueKind::Pool,
                                                in_pool);
    const std::string type_name   = format_enum(D3D8::ValueKind::ResourceType,
                                                in_type);
    const std::string usage_names = format_flags(D3D8::ValueKind::UsageFlags,
                                                 in_usage);

    return "Format=" + format_name + " Type=" + type_name + " Usage=" + usage_names + " Pool=" + pool_name;
}

std::string APIDumpPrinter::D3D8Decoder::format_state_value(const StateValueInfo& in_info,
                                                            const uint32_t&       in_value)
{
    std::string result = std::to_string(in_value);

    switch (in_info.format)
    {
        case StateValueFormat::Boolean:
        {
            result = format_boolean(static_cast<int32_t>(in_value) );

            break;
        }

        case StateValueFormat::Color:
        {
            result = format_color(in_value);

            break;
        }

        case StateValueFormat::Float:
        {
            float              value_fp32 = 0.0f;
            std::ostringstream stream;

            memcpy(&value_fp32,
                   &in_value,
                   sizeof(value_fp32) );

            stream << value_fp32;

            result = stream.str();

            break;
        }

        case StateValueFormat::Hex:
        {
            result = format_hex(in_value);

            break;
        }

        case StateValueFormat::Name:
        {
            for (uint32_t n_entry = 0;
                          n_entry < in_info.n_entries;
                        ++n_entry)
            {
                if (in_info.table_ptr[n_entry].value == in_value)
                {
                    result = in_info.table_ptr[n_entry].name_ptr;

                    break;
                }
            }

            break;
        }

        case StateValueFormat::TexCoordIndex:
        {
            const uint32_t mode = in_value & D3D8::D3DTSS_TCI_MODE_MASK;

            result = std::to_string(in_value & D3D8::D3DTSS_TCI_INDEX_MASK);

            switch (mode)
            {
                case D3D8::D3DTSS_TCI_CAMERASPACENORMAL:
                {
                    result += " | D3DTSS_TCI_CAMERASPACENORMAL";

                    break;
                }

                case D3D8::D3DTSS_TCI_CAMERASPACEPOSITION:
                {
                    result += " | D3DTSS_TCI_CAMERASPACEPOSITION";

                    break;
                }

                case D3D8::D3DTSS_TCI_CAMERASPACEREFLECTIONVECTOR:
                {
                    result += " | D3DTSS_TCI_CAMERASPACEREFLECTIONVECTOR";

                    break;
                }

                default:
                {
                    /* D3DTSS_TCI_PASSTHRU */
                    break;
                }
            }

            break;
        }

        case StateValueFormat::TextureArgument:
        {
            result = format_hex(in_value);

            for (uint32_t n_entry = 0;
                          n_entry < in_info.n_entries;
                        ++n_entry)
            {
                if (in_info.table_ptr[n_entry].value == (in_value & D3D8::D3DTA_SELECTMASK) )
                {
                    result  = in_info.table_ptr[n_entry].name_ptr;
                    result += ((in_value & D3D8::D3DTA_COMPLEMENT) != 0)     ? " | D3DTA_COMPLEMENT"     : "";
                    result += ((in_value & D3D8::D3DTA_ALPHAREPLICATE) != 0) ? " | D3DTA_ALPHAREPLICATE" : "";

                    break;
                }
            }

            break;
        }

        case StateValueFormat::TextureTransformFlags:
        {
            const uint32_t n_coordinates = in_value & D3D8::D3DTTFF_COUNT_MASK;

            result  = (n_coordinates == 0) ? "D3DTTFF_DISABLE"
                                           : "D3DTTFF_COUNT" + std::to_string(n_coordinates);
            result += ((in_value & D3D8::D3DTTFF_PROJECTED) != 0) ? " | D3DTTFF_PROJECTED" : "";

            break;
        }

        default:
        {
            /* Raw */
            break;
        }
    }

    return result;
}

bool APIDumpPrinter::D3D8Decoder::format_struct(const D3D8::ValueKind&      in_kind,
                                                const std::vector<uint8_t>& in_chunk_u8_vec,
                                                std::string*                out_text_ptr)
{
    /* The dumped process may be 32- or 64-bit, so the layout of the structures holding pointers differs. */
    constexpr size_t POINTER_N_BYTES_32 = 4;
    constexpr size_t POINTER_N_BYTES_64 = 8;

    constexpr size_t CREATION_PARAMETERS_HEAD_N_BYTES = 2 * sizeof(uint32_t); /* AdapterOrdinal, DeviceType */
    constexpr size_t CREATION_PARAMETERS_N_BYTES_32   = CREATION_PARAMETERS_HEAD_N_BYTES + POINTER_N_BYTES_32 + sizeof(uint32_t); /* hFocusWindow, BehaviorFlags */
    constexpr size_t CREATION_PARAMETERS_N_BYTES_64   = 3 * POINTER_N_BYTES_64; /* the same, padded to pointer alignment */
    constexpr size_t GUID_TEXT_N_BYTES                = 39;                     /* "{8-4-4-4-12 hex digits}" and NUL */
    constexpr size_t LOCKED_BOX_BITS_OFFSET           = 2 * sizeof(uint32_t); /* RowPitch, SlicePitch */
    constexpr size_t LOCKED_BOX_N_BYTES_32            = LOCKED_BOX_BITS_OFFSET + POINTER_N_BYTES_32;
    constexpr size_t LOCKED_BOX_N_BYTES_64            = LOCKED_BOX_BITS_OFFSET + POINTER_N_BYTES_64;
    constexpr size_t LOCKED_RECT_N_BYTES_32           = sizeof(uint32_t) + POINTER_N_BYTES_32;
    constexpr size_t LOCKED_RECT_N_BYTES_64           = 2 * POINTER_N_BYTES_64; /* Pitch, padded to pointer alignment; pBits */
    constexpr size_t MAX_N_DISPLAYED_ITEMS            = 8;                      /* of a printed array */
    constexpr size_t PRESENT_PARAMETERS_HEAD_N_BYTES  = 6 * sizeof(uint32_t); /* BackBufferWidth to SwapEffect */
    constexpr size_t PRESENT_PARAMETERS_TAIL_N_BYTES  = 6 * sizeof(uint32_t); /* Windowed to FullScreen_PresentationInterval */
    constexpr size_t PRESENT_PARAMETERS_N_BYTES_32    = PRESENT_PARAMETERS_HEAD_N_BYTES + POINTER_N_BYTES_32 + PRESENT_PARAMETERS_TAIL_N_BYTES; /* hDeviceWindow in between */
    constexpr size_t PRESENT_PARAMETERS_N_BYTES_64    = PRESENT_PARAMETERS_HEAD_N_BYTES + POINTER_N_BYTES_64 + PRESENT_PARAMETERS_TAIL_N_BYTES;

    std::ostringstream stream;
    bool               result = false;

    const auto read_func = [&](void*         out_data_ptr,
                               const size_t& in_n_bytes)
    {
        const bool is_size_ok = (in_chunk_u8_vec.size() == in_n_bytes);

        if (is_size_ok)
        {
            memcpy(out_data_ptr,
                   in_chunk_u8_vec.data(),
                   in_n_bytes);
        }

        return is_size_ok;
    };

    const auto read_u32_func = [&](const size_t& in_offset)
    {
        uint32_t value = 0;

        memcpy(&value,
               in_chunk_u8_vec.data() + in_offset,
               sizeof(value) );

        return value;
    };

    switch (in_kind)
    {
        case D3D8::ValueKind::AdapterIdentifier:
        {
            D3D8::D3DADAPTER_IDENTIFIER8 value;

            if (read_func(&value,
                          sizeof(value) ))
            {
                const std::string driver_name(value.Driver,
                                              strnlen(value.Driver,
                                                      sizeof(value.Driver) ));
                const std::string description(value.Description,
                                              strnlen(value.Description,
                                                      sizeof(value.Description) ));

                stream << "{Driver=\"" << driver_name << "\""
                       << " Description=\"" << description << "\""
                       << " DriverVersion=" << HIWORD(value.DriverVersion.HighPart) << "." << LOWORD(value.DriverVersion.HighPart)
                                            << "." << HIWORD(value.DriverVersion.LowPart) << "." << LOWORD(value.DriverVersion.LowPart)
                       << " VendorId=" << format_hex(value.VendorId)
                       << " DeviceId=" << format_hex(value.DeviceId)
                       << " SubSysId=" << format_hex(value.SubSysId)
                       << " Revision=" << value.Revision
                       << " WHQLLevel=" << value.WHQLLevel << "}";

                result = true;
            }

            break;
        }

        case D3D8::ValueKind::Box:
        {
            D3D8::D3DBOX value;

            if (read_func(&value,
                          sizeof(value) ))
            {
                stream << "{Left=" << value.Left << " Top=" << value.Top << " Right=" << value.Right << " Bottom=" << value.Bottom
                       << " Front=" << value.Front << " Back=" << value.Back << "}";

                result = true;
            }

            break;
        }

        case D3D8::ValueKind::ClipStatus:
        {
            D3D8::D3DCLIPSTATUS8 value;

            if (read_func(&value,
                          sizeof(value) ))
            {
                stream << "{ClipUnion=" << format_hex(value.ClipUnion) << " ClipIntersection=" << format_hex(value.ClipIntersection) << "}";

                result = true;
            }

            break;
        }

        case D3D8::ValueKind::CreationParameters:
        {
            /* The layout depends on the pointer size of the dumped process. */
            const size_t pointer_size = (in_chunk_u8_vec.size() == CREATION_PARAMETERS_N_BYTES_32) ? POINTER_N_BYTES_32
                                                                                                    : POINTER_N_BYTES_64;

            if (in_chunk_u8_vec.size() == CREATION_PARAMETERS_N_BYTES_32 ||
                in_chunk_u8_vec.size() == CREATION_PARAMETERS_N_BYTES_64)
            {
                stream << "{AdapterOrdinal=" << read_u32_func(0 * sizeof(uint32_t))
                       << " DeviceType=" << format_enum(D3D8::ValueKind::DeviceType,
                                                        read_u32_func(1 * sizeof(uint32_t)) )
                       << " BehaviorFlags=" << format_flags(D3D8::ValueKind::CreateFlags,
                                                            read_u32_func(CREATION_PARAMETERS_HEAD_N_BYTES + pointer_size) ) << "}";

                result = true;
            }

            break;
        }

        case D3D8::ValueKind::DisplayMode:
        {
            D3D8::D3DDISPLAYMODE value;

            if (read_func(&value,
                          sizeof(value) ))
            {
                stream << "{Width=" << value.Width << " Height=" << value.Height << " RefreshRate=" << value.RefreshRate
                       << " Format=" << format_enum(D3D8::ValueKind::Format,
                                                    value.Format) << "}";

                result = true;
            }

            break;
        }

        case D3D8::ValueKind::GammaRamp:
        {
            D3D8::D3DGAMMARAMP value;

            if (read_func(&value,
                          sizeof(value) ))
            {
                const size_t last_entry = (sizeof(value.red) / sizeof(value.red[0]) ) - 1;

                stream << "{red[0]=" << value.red[0] << " red[" << last_entry << "]=" << value.red[last_entry]
                       << " green[0]=" << value.green[0] << " green[" << last_entry << "]=" << value.green[last_entry]
                       << " blue[0]=" << value.blue[0] << " blue[" << last_entry << "]=" << value.blue[last_entry] << "}";

                result = true;
            }

            break;
        }

        case D3D8::ValueKind::Guid:
        {
            GUID value;

            if (read_func(&value,
                          sizeof(value) ))
            {
                char buffer_i8vec39[GUID_TEXT_N_BYTES];

                snprintf(buffer_i8vec39,
                         sizeof(buffer_i8vec39),
                         "{%08lX-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}",
                         value.Data1,
                         value.Data2,
                         value.Data3,
                         value.Data4[0],
                         value.Data4[1],
                         value.Data4[2],
                         value.Data4[3],
                         value.Data4[4],
                         value.Data4[5],
                         value.Data4[6],
                         value.Data4[7]);

                stream << buffer_i8vec39;

                result = true;
            }

            break;
        }

        case D3D8::ValueKind::IndexBufferDesc:
        {
            D3D8::D3DINDEXBUFFER_DESC value;

            if (read_func(&value,
                          sizeof(value) ))
            {
                stream << "{" << format_resource_properties(value.Format,
                                                            value.Type,
                                                            value.Usage,
                                                            value.Pool)
                       << " Size=" << value.Size << "}";

                result = true;
            }

            break;
        }

        case D3D8::ValueKind::Light:
        {
            D3D8::D3DLIGHT8 value;

            if (read_func(&value,
                          sizeof(value) ))
            {
                stream << "{Type=" << format_enum(D3D8::ValueKind::LightType,
                                                  value.Type)
                       << " Diffuse=" << format_color_value(value.Diffuse)
                       << " Specular=" << format_color_value(value.Specular)
                       << " Ambient=" << format_color_value(value.Ambient)
                       << " Position=(" << value.Position.x << " " << value.Position.y << " " << value.Position.z << ")"
                       << " Direction=(" << value.Direction.x << " " << value.Direction.y << " " << value.Direction.z << ")"
                       << " Range=" << value.Range
                       << " Falloff=" << value.Falloff
                       << " Attenuation=(" << value.Attenuation0 << " " << value.Attenuation1 << " " << value.Attenuation2 << ")"
                       << " Theta=" << value.Theta
                       << " Phi=" << value.Phi << "}";

                result = true;
            }

            break;
        }

        case D3D8::ValueKind::LockedBox:
        {
            /* The layout depends on the pointer size of the dumped process. */
            if (in_chunk_u8_vec.size() == LOCKED_BOX_N_BYTES_32 ||
                in_chunk_u8_vec.size() == LOCKED_BOX_N_BYTES_64)
            {
                uint64_t bits_ptr = 0;

                memcpy(&bits_ptr,
                       in_chunk_u8_vec.data() + LOCKED_BOX_BITS_OFFSET,
                       in_chunk_u8_vec.size() - LOCKED_BOX_BITS_OFFSET);

                stream << "{RowPitch=" << static_cast<int32_t>(read_u32_func(0 * sizeof(uint32_t)) )
                       << " SlicePitch=" << static_cast<int32_t>(read_u32_func(1 * sizeof(uint32_t)) )
                       << " pBits=0x" << std::hex << bits_ptr << "}";

                result = true;
            }

            break;
        }

        case D3D8::ValueKind::LockedRect:
        {
            /* The layout depends on the pointer size of the dumped process. */
            if (in_chunk_u8_vec.size() == LOCKED_RECT_N_BYTES_32 ||
                in_chunk_u8_vec.size() == LOCKED_RECT_N_BYTES_64)
            {
                const size_t pointer_size = (in_chunk_u8_vec.size() == LOCKED_RECT_N_BYTES_32) ? POINTER_N_BYTES_32
                                                                                                : POINTER_N_BYTES_64;

                uint64_t bits_ptr = 0;

                memcpy(&bits_ptr,
                       in_chunk_u8_vec.data() + in_chunk_u8_vec.size() - pointer_size,
                       pointer_size);

                stream << "{Pitch=" << static_cast<int32_t>(read_u32_func(0 * sizeof(uint32_t)) ) << " pBits=0x" << std::hex << bits_ptr << "}";

                result = true;
            }

            break;
        }

        case D3D8::ValueKind::Material:
        {
            D3D8::D3DMATERIAL8 value;

            if (read_func(&value,
                          sizeof(value) ))
            {
                stream << "{Diffuse=" << format_color_value(value.Diffuse)
                       << " Ambient=" << format_color_value(value.Ambient)
                       << " Specular=" << format_color_value(value.Specular)
                       << " Emissive=" << format_color_value(value.Emissive)
                       << " Power=" << value.Power << "}";

                result = true;
            }

            break;
        }

        case D3D8::ValueKind::Matrix:
        {
            D3D8::D3DMATRIX value;

            if (read_func(&value,
                          sizeof(value) ))
            {
                stream << "{";

                for (uint32_t n_row = 0;
                              n_row < sizeof(value.m) / sizeof(value.m[0]);
                            ++n_row)
                {
                    stream << ((n_row == 0) ? "" : " ")
                           << "[" << value.m[n_row][0] << " " << value.m[n_row][1] << " " << value.m[n_row][2] << " " << value.m[n_row][3] << "]";
                }

                stream << "}";

                result = true;
            }

            break;
        }

        case D3D8::ValueKind::PointArray:
        {
            if (in_chunk_u8_vec.size() % sizeof(POINT) == 0)
            {
                const size_t n_points = in_chunk_u8_vec.size() / sizeof(POINT);

                stream << "[";

                for (size_t n_point = 0;
                            n_point < n_points && n_point < MAX_N_DISPLAYED_ITEMS;
                          ++n_point)
                {
                    stream << ((n_point == 0) ? "" : " ")
                           << "(" << static_cast<int32_t>(read_u32_func(n_point * sizeof(POINT) + 0 * sizeof(uint32_t)) )
                           << " " << static_cast<int32_t>(read_u32_func(n_point * sizeof(POINT) + 1 * sizeof(uint32_t)) ) << ")";
                }

                stream << ((n_points > MAX_N_DISPLAYED_ITEMS) ? " ..." : "") << "] (" << n_points << " points)";

                result = true;
            }

            break;
        }

        case D3D8::ValueKind::PresentParameters:
        {
            /* The layout depends on the pointer size of the dumped process. */
            const size_t pointer_size = (in_chunk_u8_vec.size() == PRESENT_PARAMETERS_N_BYTES_32) ? POINTER_N_BYTES_32
                                                                                                  : POINTER_N_BYTES_64;

            if (in_chunk_u8_vec.size() == PRESENT_PARAMETERS_N_BYTES_32 ||
                in_chunk_u8_vec.size() == PRESENT_PARAMETERS_N_BYTES_64)
            {
                const size_t tail_offset = PRESENT_PARAMETERS_HEAD_N_BYTES + pointer_size;

                stream << "{BackBufferWidth=" << read_u32_func(0 * sizeof(uint32_t))
                       << " BackBufferHeight=" << read_u32_func(1 * sizeof(uint32_t))
                       << " BackBufferFormat=" << format_enum(D3D8::ValueKind::Format,
                                                              read_u32_func(2 * sizeof(uint32_t)) )
                       << " BackBufferCount=" << read_u32_func(3 * sizeof(uint32_t))
                       << " MultiSampleType=" << format_enum(D3D8::ValueKind::MultiSampleType,
                                                             read_u32_func(4 * sizeof(uint32_t)) )
                       << " SwapEffect=" << format_enum(D3D8::ValueKind::SwapEffect,
                                                        read_u32_func(5 * sizeof(uint32_t)) )
                       << " Windowed=" << format_boolean(static_cast<int32_t>(read_u32_func(tail_offset + 0 * sizeof(uint32_t)) ))
                       << " EnableAutoDepthStencil=" << format_boolean(static_cast<int32_t>(read_u32_func(tail_offset + 1 * sizeof(uint32_t)) ))
                       << " AutoDepthStencilFormat=" << format_enum(D3D8::ValueKind::Format,
                                                                    read_u32_func(tail_offset + 2 * sizeof(uint32_t)) )
                       << " Flags=" << format_hex(read_u32_func(tail_offset + 3 * sizeof(uint32_t)) )
                       << " FullScreen_RefreshRateInHz=" << read_u32_func(tail_offset + 4 * sizeof(uint32_t))
                       << " FullScreen_PresentationInterval=" << format_hex(read_u32_func(tail_offset + 5 * sizeof(uint32_t)) ) << "}";

                result = true;
            }

            break;
        }

        case D3D8::ValueKind::RasterStatus:
        {
            D3D8::D3DRASTER_STATUS value;

            if (read_func(&value,
                          sizeof(value) ))
            {
                stream << "{InVBlank=" << format_boolean(value.InVBlank) << " ScanLine=" << value.ScanLine << "}";

                result = true;
            }

            break;
        }

        case D3D8::ValueKind::Rect:
        {
            RECT value;

            if (read_func(&value,
                          sizeof(value) ))
            {
                stream << "{left=" << value.left << " top=" << value.top << " right=" << value.right << " bottom=" << value.bottom << "}";

                result = true;
            }

            break;
        }

        case D3D8::ValueKind::RectArray:
        {
            /* D3DRECT and RECT are both four 32-bit integers. */
            if (in_chunk_u8_vec.size() % sizeof(RECT) == 0)
            {
                const size_t n_rects = in_chunk_u8_vec.size() / sizeof(RECT);

                stream << "[";

                for (size_t n_rect = 0;
                            n_rect < n_rects && n_rect < MAX_N_DISPLAYED_ITEMS;
                          ++n_rect)
                {
                    stream << ((n_rect == 0) ? "" : " ")
                           << "{" << static_cast<int32_t>(read_u32_func(n_rect * sizeof(RECT) + 0 * sizeof(uint32_t)) )
                           << " " << static_cast<int32_t>(read_u32_func(n_rect * sizeof(RECT) + 1 * sizeof(uint32_t)) )
                           << " " << static_cast<int32_t>(read_u32_func(n_rect * sizeof(RECT) + 2 * sizeof(uint32_t)) )
                           << " " << static_cast<int32_t>(read_u32_func(n_rect * sizeof(RECT) + 3 * sizeof(uint32_t)) ) << "}";
                }

                stream << ((n_rects > MAX_N_DISPLAYED_ITEMS) ? " ..." : "") << "] (" << n_rects << " rects)";

                result = true;
            }

            break;
        }

        case D3D8::ValueKind::SurfaceDesc:
        {
            D3D8::D3DSURFACE_DESC value;

            if (read_func(&value,
                          sizeof(value) ))
            {
                stream << "{" << format_resource_properties(value.Format,
                                                            value.Type,
                                                            value.Usage,
                                                            value.Pool)
                       << " Size=" << value.Size
                       << " MultiSampleType=" << format_enum(D3D8::ValueKind::MultiSampleType,
                                                             value.MultiSampleType)
                       << " Width=" << value.Width
                       << " Height=" << value.Height << "}";

                result = true;
            }

            break;
        }

        case D3D8::ValueKind::VertexBufferDesc:
        {
            D3D8::D3DVERTEXBUFFER_DESC value;

            if (read_func(&value,
                          sizeof(value) ))
            {
                stream << "{" << format_resource_properties(value.Format,
                                                            value.Type,
                                                            value.Usage,
                                                            value.Pool)
                       << " Size=" << value.Size
                       << " FVF=" << format_fvf(value.FVF) << "}";

                result = true;
            }

            break;
        }

        case D3D8::ValueKind::Viewport:
        {
            D3D8::D3DVIEWPORT8 value;

            if (read_func(&value,
                          sizeof(value) ))
            {
                stream << "{X=" << value.X << " Y=" << value.Y << " Width=" << value.Width << " Height=" << value.Height
                       << " MinZ=" << value.MinZ << " MaxZ=" << value.MaxZ << "}";

                result = true;
            }

            break;
        }

        case D3D8::ValueKind::VolumeDesc:
        {
            D3D8::D3DVOLUME_DESC value;

            if (read_func(&value,
                          sizeof(value) ))
            {
                stream << "{" << format_resource_properties(value.Format,
                                                            value.Type,
                                                            value.Usage,
                                                            value.Pool)
                       << " Size=" << value.Size
                       << " Width=" << value.Width
                       << " Height=" << value.Height
                       << " Depth=" << value.Depth << "}";

                result = true;
            }

            break;
        }

        default:
        {
            break;
        }
    }

    if (result)
    {
        *out_text_ptr = stream.str();
    }

    return result;
}

std::string APIDumpPrinter::D3D8Decoder::get_object_name(const void* in_object_ptr,
                                                         const char* in_type_name_ptr) const
{
    constexpr size_t OBJECT_ADDRESS_TEXT_N_BYTES = 3 + 16 + 1; /* "@0x", 16 hex digits and NUL */

    const auto  map_iterator = m_object_name_map.find(in_object_ptr);
    std::string result;

    if (in_object_ptr == nullptr)
    {
        result = "NULL";
    }
    else
    if (map_iterator != m_object_name_map.end() )
    {
        result = map_iterator->second;
    }
    else
    {
        char buffer_i8vec20[OBJECT_ADDRESS_TEXT_N_BYTES];

        snprintf(buffer_i8vec20,
                 sizeof(buffer_i8vec20),
                 "@0x%llx",
                 static_cast<unsigned long long>(reinterpret_cast<uintptr_t>(in_object_ptr) ));

        result = std::string((in_type_name_ptr != nullptr) ? in_type_name_ptr
                                                           : "Object") + buffer_i8vec20;
    }

    return result;
}

bool APIDumpPrinter::D3D8Decoder::print_argument(FILE*                                      in_file_handle,
                                                 const APIDumpLoader::DumpedAPICall&        in_call,
                                                 const uint32_t&                            in_n_argument,
                                                 const bool&                                in_is_out,
                                                 const APIInterceptor::APIFunctionArgument& in_argument,
                                                 const APIDumpLoader::Workload&             in_workload) const
{
    D3D8::ArgumentInfo info   = {};
    bool               result = false;
    std::string        text;

    if (D3D8::Utils::get_argument_info(in_call.func,
                                       in_n_argument,
                                      &info) == false)
    {
        goto end;
    }

    switch (info.kind)
    {
        case D3D8::ValueKind::Boolean:
        {
            if (in_argument.type != APIInterceptor::ARGTYPE_I32)
            {
                goto end;
            }

            text   = format_boolean(in_argument.get_i32() );
            result = true;

            break;
        }

        case D3D8::ValueKind::BackBufferType:
        case D3D8::ValueKind::CubeMapFace:
        case D3D8::ValueKind::DeviceType:
        case D3D8::ValueKind::Format:
        case D3D8::ValueKind::MultiSampleType:
        case D3D8::ValueKind::Pool:
        case D3D8::ValueKind::PrimitiveType:
        case D3D8::ValueKind::RenderStateType:
        case D3D8::ValueKind::ResourceType:
        case D3D8::ValueKind::StateBlockType:
        case D3D8::ValueKind::SwapEffect:
        case D3D8::ValueKind::TextureStageStateType:
        case D3D8::ValueKind::TransformStateType:
        {
            if (in_argument.type != APIInterceptor::ARGTYPE_U32)
            {
                goto end;
            }

            text   = format_enum(info.kind,
                                 in_argument.get_u32() );
            result = true;

            break;
        }

        case D3D8::ValueKind::ClearFlags:
        case D3D8::ValueKind::CreateFlags:
        case D3D8::ValueKind::LockFlags:
        case D3D8::ValueKind::UsageFlags:
        {
            if (in_argument.type != APIInterceptor::ARGTYPE_U32)
            {
                goto end;
            }

            text   = format_flags(info.kind,
                                  in_argument.get_u32() );
            result = true;

            break;
        }

        case D3D8::ValueKind::Color:
        {
            if (in_argument.type != APIInterceptor::ARGTYPE_U32)
            {
                goto end;
            }

            text   = format_color(in_argument.get_u32() );
            result = true;

            break;
        }

        case D3D8::ValueKind::FvfFlags:
        {
            if (in_argument.type != APIInterceptor::ARGTYPE_U32)
            {
                goto end;
            }

            text   = format_fvf(in_argument.get_u32() );
            result = true;

            break;
        }

        case D3D8::ValueKind::Hresult:
        {
            if (in_argument.type != APIInterceptor::ARGTYPE_I32)
            {
                goto end;
            }

            text   = format_hresult(in_argument.get_i32() );
            result = true;

            break;
        }

        case D3D8::ValueKind::Object:
        {
            if (in_argument.type != APIInterceptor::ARGTYPE_VOID_PTR)
            {
                goto end;
            }

            text   = get_object_name(in_argument.get_ptr(),
                                     info.object_type_name_ptr);
            result = true;

            break;
        }

        case D3D8::ValueKind::ObjectOut:
        {
            if (in_argument.type != APIInterceptor::ARGTYPE_VOID_PTR)
            {
                goto end;
            }

            /* Before the call, the argument is the address of the returned pointer. */
            if (in_is_out == false)
            {
                goto end;
            }

            text   = get_object_name(in_argument.get_ptr(),
                                     info.object_type_name_ptr);
            result = true;

            break;
        }

        case D3D8::ValueKind::RenderStateValue:
        case D3D8::ValueKind::TextureStageStateValue:
        {
            if (in_argument.type != APIInterceptor::ARGTYPE_U32)
            {
                goto end;
            }

            if (in_n_argument == 0)
            {
                goto end;
            }

            /* The state is the argument before the value. */
            StateValueInfo value_info;
            const uint32_t state = in_call.arg_in_vec.at(in_n_argument - 1).get_u32();

            if (info.kind == D3D8::ValueKind::RenderStateValue)
            {
                get_render_state_value_info(state,
                                           &value_info);
            }
            else
            {
                get_texture_stage_state_value_info(state,
                                                  &value_info);
            }

            text   = format_state_value(value_info,
                                        in_argument.get_u32() );
            result = true;

            break;
        }

        case D3D8::ValueKind::Plain:
        {
            break;
        }

        default:
        {
            /* Structures and GUIDs, stored as data chunks. */
            if (in_argument.type != APIInterceptor::ARGTYPE_DATA_CHUNK_ID)
            {
                goto end;
            }

            const auto chunk_ptr = APIDumpLoader::get_data_chunk_ptr(in_workload,
                                                                     in_argument.get_data_chunk_id() );

            if (chunk_ptr == nullptr)
            {
                goto end;
            }

            if (chunk_ptr->empty() )
            {
                text   = "NULL";
                result = true;
            }
            else
            {
                result = format_struct(info.kind,
                                       *chunk_ptr,
                                      &text);
            }

            break;
        }
    }

    if (result == false)
    {
        goto end;
    }

    fprintf(in_file_handle,
            "%s",
            text.c_str() );

end:
    return result;
}

bool APIDumpPrinter::D3D8Decoder::print_returned_value(FILE*                                      in_file_handle,
                                                       const APIDumpLoader::DumpedAPICall&        in_call,
                                                       const APIInterceptor::APIFunctionArgument& in_returned_value) const
{
    D3D8::ArgumentInfo info   = {};
    bool               result = false;
    std::string        text;

    if (in_call.func == APIInterceptor::APIFUNCTION_D3D8_DIRECT3DCREATE8)
    {
        text   = get_object_name(in_returned_value.get_ptr(),
                                 "Direct3D8");
        result = true;
    }
    else
    {
        if (D3D8::Utils::get_return_info(in_call.func,
                                        &info) == false)
        {
            goto end;
        }

        if (info.kind              == D3D8::ValueKind::Hresult &&
            in_returned_value.type == APIInterceptor::ARGTYPE_I32)
        {
            text   = format_hresult(in_returned_value.get_i32() );
            result = true;
        }
        else
        if (info.kind              == D3D8::ValueKind::Boolean &&
            in_returned_value.type == APIInterceptor::ARGTYPE_I32)
        {
            text   = format_boolean(in_returned_value.get_i32() );
            result = true;
        }
        else
        if (info.kind              == D3D8::ValueKind::ResourceType &&
            in_returned_value.type == APIInterceptor::ARGTYPE_U32)
        {
            text   = format_enum(info.kind,
                                 in_returned_value.get_u32() );
            result = true;
        }
    }

    if (result == false)
    {
        goto end;
    }

    fprintf(in_file_handle,
            "%s",
            text.c_str() );

end:
    return result;
}

void APIDumpPrinter::D3D8Decoder::register_created_objects(const APIDumpLoader::DumpedAPICall& in_call)
{
    const auto register_func = [&](const void* in_object_ptr,
                                   const char* in_type_name_ptr,
                                   const bool& in_is_new)
    {
        if (in_object_ptr != nullptr &&
            (in_is_new                                           ||
             m_object_name_map.find(in_object_ptr) == m_object_name_map.end() ))
        {
            const std::string type_name(in_type_name_ptr);
            const auto        n_object = ++m_n_created_objects_map[type_name];

            m_object_name_map[in_object_ptr] = type_name + "#" + std::to_string(n_object);
        }
    };

    if (in_call.func == APIInterceptor::APIFUNCTION_D3D8_DIRECT3DCREATE8)
    {
        if (in_call.returned_value_ptr != nullptr &&
            in_call.returned_value_ptr->type == APIInterceptor::ARGTYPE_VOID_PTR)
        {
            register_func(in_call.returned_value_ptr->get_ptr(),
                          "Direct3D8",
                          true);  /* in_is_new */
        }
    }
    else
    if (in_call.returned_value_ptr != nullptr                                  &&
        in_call.returned_value_ptr->type == APIInterceptor::ARGTYPE_I32        &&
        in_call.returned_value_ptr->get_i32() >= 0                             &&
        D3D8::Utils::get_method_info_ptr(in_call.func) != nullptr)
    {
        /* Create* methods always return new objects; Get* ones return existing objects, which may be unknown to us. */
        const bool is_create = (strncmp(D3D8::Utils::get_method_info_ptr(in_call.func)->method_name_ptr,
                                        "Create",
                                        strlen("Create") ) == 0);

        for (uint32_t n_argument = 0;
                      n_argument < in_call.arg_out_vec.size();
                    ++n_argument)
        {
            D3D8::ArgumentInfo info = {};

            const bool is_argument_known = D3D8::Utils::get_argument_info(in_call.func,
                                                                          n_argument,
                                                                         &info);

            if (is_argument_known == false)
            {
                continue;
            }

            if (info.kind                               == D3D8::ValueKind::ObjectOut &&
                in_call.arg_out_vec.at(n_argument).type == APIInterceptor::ARGTYPE_VOID_PTR)
            {
                register_func(in_call.arg_out_vec.at(n_argument).get_ptr(),
                              info.object_type_name_ptr,
                              is_create);
            }
        }
    }
}
