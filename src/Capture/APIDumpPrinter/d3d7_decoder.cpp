/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "d3d7_decoder.h"
#include "Common/macros.h"
#include "Interception/Core/D3D7Utils/argument_info.h"
#include "Interception/Core/D3D7Utils/guids.h"
#include "Interception/Core/D3D7Utils/methods.h"
#include "Interception/Core/D3D7Utils/value_readers.h"
#include "value_formatter.h"
#include <sstream>
#include <string.h>

std::string Capture::APIDumpPrinter::D3D7Decoder::format_color_value(const Interception::Hooks::D3D7::D3DCOLORVALUE& in_value)
{
    std::ostringstream stream;

    stream << "(" << in_value.r << " " << in_value.g << " " << in_value.b << " " << in_value.a << ")";

    return stream.str();
}

std::string Capture::APIDumpPrinter::D3D7Decoder::format_enum(const Interception::Hooks::D3D7::ValueKind& in_kind,
                                                               const uint32_t&                             in_value)
{
    const ValueNameEntry* table_ptr = nullptr;
    uint32_t              n_entries = 0;

    D3D7Names::get_value_name_table(in_kind,
                                   &table_ptr,
                                   &n_entries);

    return ValueFormatter::format_enum(table_ptr,
                                       n_entries,
                                       in_value);
}

std::string Capture::APIDumpPrinter::D3D7Decoder::format_flag_table(const D3D7FlagTable& in_table,
                                                                     const uint32_t&      in_value)
{
    const FlagNameEntry* table_ptr = nullptr;
    uint32_t             n_entries = 0;

    D3D7Names::get_flag_name_table(in_table,
                                  &table_ptr,
                                  &n_entries);

    return ValueFormatter::format_flags(table_ptr,
                                        n_entries,
                                        in_value);
}

std::string Capture::APIDumpPrinter::D3D7Decoder::format_flags(const Interception::Hooks::D3D7::ValueKind& in_kind,
                                                                const uint32_t&                             in_value)
{
    struct FlagKind
    {
        Interception::Hooks::D3D7::ValueKind kind;
        D3D7FlagTable                        table;
    };

    static const FlagKind flag_kind_array[] =
    {
        {Interception::Hooks::D3D7::ValueKind::BLT_FAST_FLAGS,                D3D7FlagTable::BLT_FAST},
        {Interception::Hooks::D3D7::ValueKind::BLT_FLAGS,                     D3D7FlagTable::BLT},
        {Interception::Hooks::D3D7::ValueKind::CLEAR_FLAGS,                   D3D7FlagTable::CLEAR},
        {Interception::Hooks::D3D7::ValueKind::COLOR_KEY_FLAGS,               D3D7FlagTable::COLOR_KEY},
        {Interception::Hooks::D3D7::ValueKind::COOPERATIVE_LEVEL_FLAGS,       D3D7FlagTable::COOPERATIVE_LEVEL},
        {Interception::Hooks::D3D7::ValueKind::DRAW_FLAGS,                    D3D7FlagTable::DRAW},
        {Interception::Hooks::D3D7::ValueKind::ENUM_DISPLAY_MODES_FLAGS,      D3D7FlagTable::ENUM_DISPLAY_MODES},
        {Interception::Hooks::D3D7::ValueKind::ENUM_SURFACES_FLAGS,           D3D7FlagTable::ENUM_SURFACES},
        {Interception::Hooks::D3D7::ValueKind::FLIP_FLAGS,                    D3D7FlagTable::FLIP},
        {Interception::Hooks::D3D7::ValueKind::LOCK_FLAGS,                    D3D7FlagTable::LOCK},
        {Interception::Hooks::D3D7::ValueKind::OVERLAY_FLAGS,                 D3D7FlagTable::OVERLAY},
        {Interception::Hooks::D3D7::ValueKind::PALETTE_FLAGS,                 D3D7FlagTable::PALETTE},
        {Interception::Hooks::D3D7::ValueKind::SET_DISPLAY_MODE_FLAGS,        D3D7FlagTable::SET_DISPLAY_MODE},
        {Interception::Hooks::D3D7::ValueKind::VERTEX_OPERATION_FLAGS,        D3D7FlagTable::VERTEX_OPERATION},
        {Interception::Hooks::D3D7::ValueKind::WAIT_FOR_VERTICAL_BLANK_FLAGS, D3D7FlagTable::WAIT_FOR_VERTICAL_BLANK}
    };

    std::string result = ValueFormatter::format_hex(in_value);

    for (const auto& flag_kind : flag_kind_array)
    {
        if (flag_kind.kind == in_kind)
        {
            result = format_flag_table(flag_kind.table,
                                       in_value);

            break;
        }
    }

    return result;
}

std::string Capture::APIDumpPrinter::D3D7Decoder::format_four_cc(const uint32_t& in_value)
{
    constexpr size_t   N_CHARACTERS      = 4;
    constexpr uint32_t BITS_PER_CHAR     = 8;
    constexpr uint32_t FIRST_PRINTABLE   = 0x20;
    constexpr uint32_t LAST_PRINTABLE    = 0x7E;
    constexpr uint32_t CHARACTER_MASK    = 0xFF;

    std::string characters;
    bool        is_printable = true;

    for (size_t n_character = 0;
                n_character < N_CHARACTERS;
              ++n_character)
    {
        const uint32_t character = (in_value >> (BITS_PER_CHAR * n_character) ) & CHARACTER_MASK;

        if (character < FIRST_PRINTABLE ||
            character > LAST_PRINTABLE)
        {
            is_printable = false;
        }

        characters.push_back(static_cast<char>(character) );
    }

    return is_printable ? "'" + characters + "'"
                        : ValueFormatter::format_hex(in_value);
}

std::string Capture::APIDumpPrinter::D3D7Decoder::format_fvf(const uint32_t& in_value)
{
    /* No vertex shaders in Direct3D 7. */
    static const ValueFormatter::FvfStyle style = {"RESERVED1", false /* has_shader_handles */};

    return ValueFormatter::format_fvf(in_value,
                                      style);
}

std::string Capture::APIDumpPrinter::D3D7Decoder::format_guid(const GUID& in_value)
{
    constexpr size_t GUID_TEXT_N_BYTES = 39; /* "{8-4-4-4-12 hex digits}" and NUL */

    const Interception::Core::D3D7Utils::KnownGuid* known_guid_ptr = Interception::Core::D3D7Utils::find_known_guid(in_value);
    std::string                                     result;

    if (known_guid_ptr != nullptr)
    {
        result = known_guid_ptr->name_ptr;
    }
    else
    {
        char buffer_i8vec39[GUID_TEXT_N_BYTES];

        snprintf(buffer_i8vec39,
                 sizeof(buffer_i8vec39),
                 "{%08lX-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}",
                 in_value.Data1,
                 in_value.Data2,
                 in_value.Data3,
                 in_value.Data4[0],
                 in_value.Data4[1],
                 in_value.Data4[2],
                 in_value.Data4[3],
                 in_value.Data4[4],
                 in_value.Data4[5],
                 in_value.Data4[6],
                 in_value.Data4[7]);

        result = buffer_i8vec39;
    }

    return result;
}

std::string Capture::APIDumpPrinter::D3D7Decoder::format_hresult(const int32_t& in_value)
{
    const ValueNameEntry* table_ptr = nullptr;
    uint32_t              n_entries = 0;

    D3D7Names::get_hresult_name_table(&table_ptr,
                                      &n_entries);

    return ValueFormatter::format_hresult(table_ptr,
                                          n_entries,
                                          in_value);
}

std::string Capture::APIDumpPrinter::D3D7Decoder::format_pixel_format(const Interception::Hooks::D3D7::DDPIXELFORMAT& in_value)
{
    constexpr uint32_t PF_ALPHA_PIXELS = 0x00000001;
    constexpr uint32_t PF_FOUR_CC      = 0x00000004;

    std::ostringstream stream;

    stream << "{Flags=" << format_flag_table(D3D7FlagTable::PIXEL_FORMAT,
                                             in_value.dwFlags);

    if ( (in_value.dwFlags & PF_FOUR_CC) != 0)
    {
        stream << " FourCC=" << format_four_cc(in_value.dwFourCC);
    }

    stream << " BitCount=" << in_value.dwRGBBitCount
           << " RBitMask=" << ValueFormatter::format_hex(in_value.dwRBitMask)
           << " GBitMask=" << ValueFormatter::format_hex(in_value.dwGBitMask)
           << " BBitMask=" << ValueFormatter::format_hex(in_value.dwBBitMask);

    if ( (in_value.dwFlags & PF_ALPHA_PIXELS) != 0)
    {
        stream << " AlphaBitMask=" << ValueFormatter::format_hex(in_value.dwRGBAlphaBitMask);
    }

    stream << "}";

    return stream.str();
}

bool Capture::APIDumpPrinter::D3D7Decoder::format_struct(const Interception::Hooks::D3D7::ValueKind& in_kind,
                                                          const std::vector<uint8_t>&                 in_chunk_u8_vec,
                                                          std::string*                                out_text_ptr)
{
    /* The dumped process is a 32-bit one: DirectDraw 7 has no 64-bit version. */
    constexpr size_t   MAX_N_DISPLAYED_ITEMS      = 8;  /* of a printed array */
    constexpr size_t   N_STRIDED_ARRAYS           = 12; /* position, normal, diffuse, specular, 8 sets of texture coordinates */
    constexpr size_t   STRIDED_DATA_ELEMENT_BYTES = 2 * sizeof(uint32_t); /* data pointer, stride */
    constexpr uint32_t SD_ALPHA_BIT_DEPTH         = 0x00000080;
    constexpr uint32_t SD_BACK_BUFFER_COUNT       = 0x00000020;
    constexpr uint32_t SD_CAPS                    = 0x00000001;
    constexpr uint32_t SD_CK_DEST_BLT             = 0x00004000;
    constexpr uint32_t SD_CK_DEST_OVERLAY         = 0x00002000;
    constexpr uint32_t SD_CK_SRC_BLT              = 0x00010000;
    constexpr uint32_t SD_CK_SRC_OVERLAY          = 0x00008000;
    constexpr uint32_t SD_HEIGHT                  = 0x00000002;
    constexpr uint32_t SD_LINEAR_SIZE             = 0x00080000;
    constexpr uint32_t SD_LP_SURFACE              = 0x00000800;
    constexpr uint32_t SD_MIP_MAP_COUNT           = 0x00020000;
    constexpr uint32_t SD_PIXEL_FORMAT            = 0x00001000;
    constexpr uint32_t SD_PITCH                   = 0x00000008;
    constexpr uint32_t SD_TEXTURE_STAGE           = 0x00100000;
    constexpr uint32_t SD_WIDTH                   = 0x00000004;

    static const char* const strided_array_name_ptr_array[N_STRIDED_ARRAYS] =
    {
        "Position",
        "Normal",
        "Diffuse",
        "Specular",
        "TextureCoords0",
        "TextureCoords1",
        "TextureCoords2",
        "TextureCoords3",
        "TextureCoords4",
        "TextureCoords5",
        "TextureCoords6",
        "TextureCoords7"
    };

    static const ValueNameEntry light_type_name_array[] =
    {
        {"D3DLIGHT_POINT",       1},
        {"D3DLIGHT_SPOT",        2},
        {"D3DLIGHT_DIRECTIONAL", 3}
    };

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

    const auto format_color_key_func = [](const Interception::Hooks::D3D7::DDCOLORKEY& in_value)
    {
        return "{Low=" + ValueFormatter::format_hex(in_value.dwColorSpaceLowValue) + " High=" + ValueFormatter::format_hex(in_value.dwColorSpaceHighValue) + "}";
    };

    const auto format_primitive_caps_func = [](const Interception::Hooks::D3D7::D3DPRIMCAPS& in_value)
    {
        std::ostringstream caps_stream;

        caps_stream << "{MiscCaps="          << ValueFormatter::format_hex(in_value.dwMiscCaps)
                    << " RasterCaps="        << ValueFormatter::format_hex(in_value.dwRasterCaps)
                    << " ZCmpCaps="          << ValueFormatter::format_hex(in_value.dwZCmpCaps)
                    << " SrcBlendCaps="      << ValueFormatter::format_hex(in_value.dwSrcBlendCaps)
                    << " DestBlendCaps="     << ValueFormatter::format_hex(in_value.dwDestBlendCaps)
                    << " AlphaCmpCaps="      << ValueFormatter::format_hex(in_value.dwAlphaCmpCaps)
                    << " ShadeCaps="         << ValueFormatter::format_hex(in_value.dwShadeCaps)
                    << " TextureCaps="       << ValueFormatter::format_hex(in_value.dwTextureCaps)
                    << " TextureFilterCaps=" << ValueFormatter::format_hex(in_value.dwTextureFilterCaps)
                    << " TextureBlendCaps="  << ValueFormatter::format_hex(in_value.dwTextureBlendCaps)
                    << " TextureAddressCaps="<< ValueFormatter::format_hex(in_value.dwTextureAddressCaps)
                    << " StippleWidth="      << in_value.dwStippleWidth
                    << " StippleHeight="     << in_value.dwStippleHeight << "}";

        return caps_stream.str();
    };

    switch (in_kind)
    {
        case Interception::Hooks::D3D7::ValueKind::BLT_FX:
        {
            Interception::Hooks::D3D7::DDBLTFX value;

            if (read_func(&value,
                          sizeof(value) ))
            {
                stream << "{DDFX="                << ValueFormatter::format_hex(value.dwDDFX)
                       << " ROP="                 << ValueFormatter::format_hex(value.dwROP)
                       << " DDROP="               << ValueFormatter::format_hex(value.dwDDROP)
                       << " RotationAngle="       << value.dwRotationAngle
                       << " ZBufferOpCode="       << value.dwZBufferOpCode
                       << " ZBufferLow="          << value.dwZBufferLow
                       << " ZBufferHigh="         << value.dwZBufferHigh
                       << " ZBufferBaseDest="     << value.dwZBufferBaseDest
                       << " ZDestConst="          << value.dwZDestConst
                       << " ZSrcConst="           << value.dwZSrcConst
                       << " AlphaEdgeBlend="      << value.dwAlphaEdgeBlend
                       << " AlphaDestConst="      << value.dwAlphaDestConst
                       << " AlphaSrcConst="       << value.dwAlphaSrcConst
                       << " FillColor="           << ValueFormatter::format_hex(value.dwFillColor)
                       << " DestColorkey="        << format_color_key_func(value.ddckDestColorkey)
                       << " SrcColorkey="         << format_color_key_func(value.ddckSrcColorkey) << "}";

                result = true;
            }

            break;
        }

        case Interception::Hooks::D3D7::ValueKind::CAPS:
        {
            Interception::Hooks::D3D7::DDCAPS value;

            if (read_func(&value,
                          sizeof(value) ))
            {
                stream << "{Caps="                  << format_flag_table(D3D7FlagTable::DIRECT_DRAW_CAPS,
                                                                         value.dwCaps)
                       << " Caps2="                 << format_flag_table(D3D7FlagTable::DIRECT_DRAW_CAPS2,
                                                                         value.dwCaps2)
                       << " ColorKeyCaps="          << ValueFormatter::format_hex(value.dwCKeyCaps)
                       << " FXCaps="                << ValueFormatter::format_hex(value.dwFXCaps)
                       << " FXAlphaCaps="           << ValueFormatter::format_hex(value.dwFXAlphaCaps)
                       << " PaletteCaps="           << format_flag_table(D3D7FlagTable::PALETTE,
                                                                         value.dwPalCaps)
                       << " StereoViewCaps="        << ValueFormatter::format_hex(value.dwSVCaps)
                       << " ZBufferBitDepths="      << ValueFormatter::format_hex(value.dwZBufferBitDepths)
                       << " VideoMemoryTotal="      << value.dwVidMemTotal
                       << " VideoMemoryFree="       << value.dwVidMemFree
                       << " MaxVisibleOverlays="    << value.dwMaxVisibleOverlays
                       << " CurrentVisibleOverlays="<< value.dwCurrVisibleOverlays
                       << " NumFourCCCodes="        << value.dwNumFourCCCodes
                       << " MaxVideoPorts="         << value.dwMaxVideoPorts
                       << " CurrentVideoPorts="     << value.dwCurrVideoPorts
                       << " SurfaceCaps="           << format_surface_caps(value.ddsCaps) << "}";

                result = true;
            }

            break;
        }

        case Interception::Hooks::D3D7::ValueKind::CLIP_PLANE:
        {
            Interception::Hooks::D3D7::D3DCLIPPLANE value;

            if (read_func(&value,
                          sizeof(value) ))
            {
                stream << "{A=" << value.dvPlaneEquation[0]
                       << " B=" << value.dvPlaneEquation[1]
                       << " C=" << value.dvPlaneEquation[2]
                       << " D=" << value.dvPlaneEquation[3] << "}";

                result = true;
            }

            break;
        }

        case Interception::Hooks::D3D7::ValueKind::CLIP_STATUS:
        {
            Interception::Hooks::D3D7::D3DCLIPSTATUS value;

            if (read_func(&value,
                          sizeof(value) ))
            {
                stream << "{Flags="  << ValueFormatter::format_hex(value.dwFlags)
                       << " Status=" << ValueFormatter::format_hex(value.dwStatus)
                       << " MinX="   << value.minx
                       << " MaxX="   << value.maxx
                       << " MinY="   << value.miny
                       << " MaxY="   << value.maxy
                       << " MinZ="   << value.minz
                       << " MaxZ="   << value.maxz << "}";

                result = true;
            }

            break;
        }

        case Interception::Hooks::D3D7::ValueKind::COLOR_CONTROL:
        {
            Interception::Hooks::D3D7::DDCOLORCONTROL value;

            if (read_func(&value,
                          sizeof(value) ))
            {
                stream << "{Flags="       << ValueFormatter::format_hex(value.dwFlags)
                       << " Brightness="  << value.lBrightness
                       << " Contrast="    << value.lContrast
                       << " Hue="         << value.lHue
                       << " Saturation="  << value.lSaturation
                       << " Sharpness="   << value.lSharpness
                       << " Gamma="       << value.lGamma
                       << " ColorEnable=" << value.lColorEnable << "}";

                result = true;
            }

            break;
        }

        case Interception::Hooks::D3D7::ValueKind::COLOR_KEY:
        {
            Interception::Hooks::D3D7::DDCOLORKEY value;

            if (read_func(&value,
                          sizeof(value) ))
            {
                stream << format_color_key_func(value);

                result = true;
            }

            break;
        }

        case Interception::Hooks::D3D7::ValueKind::DEVICE_DESC:
        {
            Interception::Hooks::D3D7::D3DDEVICEDESC7 value;

            if (read_func(&value,
                          sizeof(value) ))
            {
                stream << "{DevCaps="                 << format_flag_table(D3D7FlagTable::DEVICE_CAPS,
                                                                           value.dwDevCaps)
                       << " LineCaps="                << format_primitive_caps_func(value.dpcLineCaps)
                       << " TriCaps="                 << format_primitive_caps_func(value.dpcTriCaps)
                       << " DeviceRenderBitDepth="    << ValueFormatter::format_hex(value.dwDeviceRenderBitDepth)
                       << " DeviceZBufferBitDepth="   << ValueFormatter::format_hex(value.dwDeviceZBufferBitDepth)
                       << " MinTextureSize="          << value.dwMinTextureWidth << "x" << value.dwMinTextureHeight
                       << " MaxTextureSize="          << value.dwMaxTextureWidth << "x" << value.dwMaxTextureHeight
                       << " MaxTextureRepeat="        << value.dwMaxTextureRepeat
                       << " MaxTextureAspectRatio="   << value.dwMaxTextureAspectRatio
                       << " MaxAnisotropy="           << value.dwMaxAnisotropy
                       << " GuardBand=(" << value.dvGuardBandLeft << " " << value.dvGuardBandTop << " " << value.dvGuardBandRight << " " << value.dvGuardBandBottom << ")"
                       << " ExtentsAdjust="           << value.dvExtentsAdjust
                       << " StencilCaps="             << ValueFormatter::format_hex(value.dwStencilCaps)
                       << " FVFCaps="                 << ValueFormatter::format_hex(value.dwFVFCaps)
                       << " TextureOpCaps="           << ValueFormatter::format_hex(value.dwTextureOpCaps)
                       << " MaxTextureBlendStages="   << value.wMaxTextureBlendStages
                       << " MaxSimultaneousTextures=" << value.wMaxSimultaneousTextures
                       << " MaxActiveLights="         << value.dwMaxActiveLights
                       << " MaxVertexW="              << value.dvMaxVertexW
                       << " DeviceGUID="              << format_guid(value.deviceGUID)
                       << " MaxUserClipPlanes="       << value.wMaxUserClipPlanes
                       << " MaxVertexBlendMatrices="  << value.wMaxVertexBlendMatrices
                       << " VertexProcessingCaps="    << ValueFormatter::format_hex(value.dwVertexProcessingCaps) << "}";

                result = true;
            }

            break;
        }

        case Interception::Hooks::D3D7::ValueKind::DEVICE_IDENTIFIER:
        {
            Interception::Hooks::D3D7::DDDEVICEIDENTIFIER2 value;

            if (read_func(&value,
                          sizeof(value) ))
            {
                const std::string driver_name(value.szDriver,
                                              strnlen(value.szDriver,
                                                      sizeof(value.szDriver) ));
                const std::string description(value.szDescription,
                                              strnlen(value.szDescription,
                                                      sizeof(value.szDescription) ));

                stream << "{Driver=\"" << driver_name << "\""
                       << " Description=\"" << description << "\""
                       << " DriverVersion=" << HIWORD(value.liDriverVersion.HighPart) << "." << LOWORD(value.liDriverVersion.HighPart)
                                            << "." << HIWORD(value.liDriverVersion.LowPart) << "." << LOWORD(value.liDriverVersion.LowPart)
                       << " VendorId=" << ValueFormatter::format_hex(value.dwVendorId)
                       << " DeviceId=" << ValueFormatter::format_hex(value.dwDeviceId)
                       << " SubSysId=" << ValueFormatter::format_hex(value.dwSubSysId)
                       << " Revision=" << value.dwRevision
                       << " DeviceIdentifier=" << format_guid(value.guidDeviceIdentifier)
                       << " WHQLLevel=" << value.dwWHQLLevel << "}";

                result = true;
            }

            break;
        }

        case Interception::Hooks::D3D7::ValueKind::GAMMA_RAMP:
        {
            Interception::Hooks::D3D7::DDGAMMARAMP value;

            if (read_func(&value,
                          sizeof(value) ))
            {
                constexpr size_t LAST_ENTRY = sizeof(value.red) / sizeof(value.red[0]) - 1;

                stream << "{Red=" << value.red[0] << ".." << value.red[LAST_ENTRY]
                       << " Green=" << value.green[0] << ".." << value.green[LAST_ENTRY]
                       << " Blue=" << value.blue[0] << ".." << value.blue[LAST_ENTRY] << "}";

                result = true;
            }

            break;
        }

        case Interception::Hooks::D3D7::ValueKind::GUID:
        {
            GUID value;

            if (read_func(&value,
                          sizeof(value) ))
            {
                stream << format_guid(value);

                result = true;
            }

            break;
        }

        case Interception::Hooks::D3D7::ValueKind::LIGHT:
        {
            Interception::Hooks::D3D7::D3DLIGHT7 value;

            if (read_func(&value,
                          sizeof(value) ))
            {
                stream << "{Type=" << ValueFormatter::format_enum(light_type_name_array,
                                                                   static_cast<uint32_t>(sizeof(light_type_name_array) / sizeof(light_type_name_array[0]) ),
                                                                   value.dltType)
                       << " Diffuse=" << format_color_value(value.dcvDiffuse)
                       << " Specular=" << format_color_value(value.dcvSpecular)
                       << " Ambient=" << format_color_value(value.dcvAmbient)
                       << " Position=(" << value.dvPosition[0] << " " << value.dvPosition[1] << " " << value.dvPosition[2] << ")"
                       << " Direction=(" << value.dvDirection[0] << " " << value.dvDirection[1] << " " << value.dvDirection[2] << ")"
                       << " Range=" << value.dvRange
                       << " Falloff=" << value.dvFalloff
                       << " Attenuation=(" << value.dvAttenuation0 << " " << value.dvAttenuation1 << " " << value.dvAttenuation2 << ")"
                       << " Theta=" << value.dvTheta
                       << " Phi=" << value.dvPhi << "}";

                result = true;
            }

            break;
        }

        case Interception::Hooks::D3D7::ValueKind::MATERIAL:
        {
            Interception::Hooks::D3D7::D3DMATERIAL7 value;

            if (read_func(&value,
                          sizeof(value) ))
            {
                stream << "{Diffuse=" << format_color_value(value.dcvDiffuse)
                       << " Ambient=" << format_color_value(value.dcvAmbient)
                       << " Specular=" << format_color_value(value.dcvSpecular)
                       << " Emissive=" << format_color_value(value.dcvEmissive)
                       << " Power=" << value.dvPower << "}";

                result = true;
            }

            break;
        }

        case Interception::Hooks::D3D7::ValueKind::MATRIX:
        {
            Interception::Hooks::D3D7::D3DMATRIX value;

            if (read_func(&value,
                          sizeof(value) ))
            {
                stream << "{";

                for (uint32_t n_row = 0;
                              n_row < 4;
                            ++n_row)
                {
                    stream << ( (n_row != 0) ? " " : "") << "(" << value.m[n_row][0] << " " << value.m[n_row][1] << " " << value.m[n_row][2] << " " << value.m[n_row][3] << ")";
                }

                stream << "}";

                result = true;
            }

            break;
        }

        case Interception::Hooks::D3D7::ValueKind::OVERLAY_FX:
        {
            Interception::Hooks::D3D7::DDOVERLAYFX value;

            if (read_func(&value,
                          sizeof(value) ))
            {
                stream << "{AlphaEdgeBlend="  << value.dwAlphaEdgeBlend
                       << " AlphaDestConst="  << value.dwAlphaDestConst
                       << " AlphaSrcConst="   << value.dwAlphaSrcConst
                       << " DestColorkey="    << format_color_key_func(value.dckDestColorkey)
                       << " SrcColorkey="     << format_color_key_func(value.dckSrcColorkey)
                       << " DDFX="            << ValueFormatter::format_hex(value.dwDDFX)
                       << " Flags="           << ValueFormatter::format_hex(value.dwFlags) << "}";

                result = true;
            }

            break;
        }

        case Interception::Hooks::D3D7::ValueKind::PALETTE_ENTRIES:
        {
            const size_t n_entries = in_chunk_u8_vec.size() / sizeof(PALETTEENTRY);

            if (in_chunk_u8_vec.size() % sizeof(PALETTEENTRY) == 0)
            {
                const PALETTEENTRY* entry_ptr = reinterpret_cast<const PALETTEENTRY*>(in_chunk_u8_vec.data() );

                stream << "[";

                for (size_t n_entry = 0;
                            n_entry < n_entries && n_entry < MAX_N_DISPLAYED_ITEMS;
                          ++n_entry)
                {
                    stream << ( (n_entry != 0) ? " " : "") << "("
                           << static_cast<uint32_t>(entry_ptr[n_entry].peRed)   << ","
                           << static_cast<uint32_t>(entry_ptr[n_entry].peGreen) << ","
                           << static_cast<uint32_t>(entry_ptr[n_entry].peBlue)  << ","
                           << static_cast<uint32_t>(entry_ptr[n_entry].peFlags) << ")";
                }

                if (n_entries > MAX_N_DISPLAYED_ITEMS)
                {
                    stream << " ... (" << n_entries << " entries)";
                }

                stream << "]";

                result = true;
            }

            break;
        }

        case Interception::Hooks::D3D7::ValueKind::PIXEL_FORMAT:
        {
            Interception::Hooks::D3D7::DDPIXELFORMAT value;

            if (read_func(&value,
                          sizeof(value) ))
            {
                stream << format_pixel_format(value);

                result = true;
            }

            break;
        }

        case Interception::Hooks::D3D7::ValueKind::POINT:
        {
            POINT value;

            if (read_func(&value,
                          sizeof(value) ))
            {
                stream << "{X=" << value.x << " Y=" << value.y << "}";

                result = true;
            }

            break;
        }

        case Interception::Hooks::D3D7::ValueKind::RECT:
        {
            RECT value;

            if (read_func(&value,
                          sizeof(value) ))
            {
                stream << "{Left=" << value.left << " Top=" << value.top << " Right=" << value.right << " Bottom=" << value.bottom << "}";

                result = true;
            }

            break;
        }

        case Interception::Hooks::D3D7::ValueKind::RECT_ARRAY:
        {
            const size_t n_rects = in_chunk_u8_vec.size() / sizeof(Interception::Hooks::D3D7::D3DRECT);

            if (in_chunk_u8_vec.size() % sizeof(Interception::Hooks::D3D7::D3DRECT) == 0)
            {
                const Interception::Hooks::D3D7::D3DRECT* rect_ptr = reinterpret_cast<const Interception::Hooks::D3D7::D3DRECT*>(in_chunk_u8_vec.data() );

                stream << "[";

                for (size_t n_rect = 0;
                            n_rect < n_rects && n_rect < MAX_N_DISPLAYED_ITEMS;
                          ++n_rect)
                {
                    stream << ( (n_rect != 0) ? " " : "")
                           << "{" << rect_ptr[n_rect].x1 << " " << rect_ptr[n_rect].y1 << " " << rect_ptr[n_rect].x2 << " " << rect_ptr[n_rect].y2 << "}";
                }

                if (n_rects > MAX_N_DISPLAYED_ITEMS)
                {
                    stream << " ... (" << n_rects << " rectangles)";
                }

                stream << "]";

                result = true;
            }

            break;
        }

        case Interception::Hooks::D3D7::ValueKind::STRIDED_DATA:
        {
            if (in_chunk_u8_vec.size() == N_STRIDED_ARRAYS * STRIDED_DATA_ELEMENT_BYTES)
            {
                bool is_first = true;

                stream << "{";

                for (size_t n_array = 0;
                            n_array < N_STRIDED_ARRAYS;
                          ++n_array)
                {
                    const uint32_t data_address = read_u32_func(n_array * STRIDED_DATA_ELEMENT_BYTES);
                    const uint32_t stride       = read_u32_func(n_array * STRIDED_DATA_ELEMENT_BYTES + sizeof(uint32_t) );

                    if (data_address != 0)
                    {
                        stream << (is_first ? "" : " ")
                               << strided_array_name_ptr_array[n_array] << "={Data=" << ValueFormatter::format_hex(data_address) << " Stride=" << stride << "}";

                        is_first = false;
                    }
                }

                stream << "}";

                result = true;
            }

            break;
        }

        case Interception::Hooks::D3D7::ValueKind::STRIDED_VERTEX_ARRAYS:
        {
            /* The number of the arrays, their sizes, and the arrays (see the hook). */
            const size_t head_n_bytes = sizeof(uint32_t) * (1 + N_STRIDED_ARRAYS);

            if (in_chunk_u8_vec.size() >= head_n_bytes &&
                read_u32_func(0)       == N_STRIDED_ARRAYS)
            {
                size_t n_array_bytes = 0;
                bool   is_first      = true;

                for (size_t n_array = 0;
                            n_array < N_STRIDED_ARRAYS;
                          ++n_array)
                {
                    n_array_bytes += read_u32_func(sizeof(uint32_t) * (1 + n_array) );
                }

                if (in_chunk_u8_vec.size() == head_n_bytes + n_array_bytes)
                {
                    stream << "{";

                    for (size_t n_array = 0;
                                n_array < N_STRIDED_ARRAYS;
                              ++n_array)
                    {
                        const uint32_t n_bytes = read_u32_func(sizeof(uint32_t) * (1 + n_array) );

                        if (n_bytes != 0)
                        {
                            stream << (is_first ? "" : " ")
                                   << strided_array_name_ptr_array[n_array] << "=" << n_bytes << " bytes";

                            is_first = false;
                        }
                    }

                    stream << "}";

                    result = true;
                }
            }

            break;
        }

        case Interception::Hooks::D3D7::ValueKind::SURFACE_CAPS:
        {
            Interception::Hooks::D3D7::DDSCAPS2 value;

            if (read_func(&value,
                          sizeof(value) ))
            {
                stream << format_surface_caps(value);

                result = true;
            }

            break;
        }

        case Interception::Hooks::D3D7::ValueKind::SURFACE_DESC:
        {
            Interception::Core::D3D7Utils::SurfaceDescription value;

            if (Interception::Core::D3D7Utils::parse_surface_description(in_chunk_u8_vec.data(),
                                                                         in_chunk_u8_vec.size(),
                                                                        &value) )
            {
                stream << "{Flags=" << format_flag_table(D3D7FlagTable::SURFACE_DESC,
                                                         value.flags);

                if ( (value.flags & SD_CAPS) != 0)
                {
                    stream << " Caps=" << format_surface_caps(value.caps);
                }

                if ( (value.flags & SD_HEIGHT) != 0)
                {
                    stream << " Height=" << value.height;
                }

                if ( (value.flags & SD_WIDTH) != 0)
                {
                    stream << " Width=" << value.width;
                }

                if ( (value.flags & SD_PITCH) != 0)
                {
                    stream << " Pitch=" << value.pitch;
                }

                if ( (value.flags & SD_LINEAR_SIZE) != 0)
                {
                    stream << " LinearSize=" << value.pitch;
                }

                if ( (value.flags & SD_BACK_BUFFER_COUNT) != 0)
                {
                    stream << " BackBufferCount=" << value.back_buffer_count;
                }

                if ( (value.flags & SD_MIP_MAP_COUNT) != 0)
                {
                    stream << " MipMapCount=" << value.mip_map_count;
                }

                if ( (value.flags & SD_ALPHA_BIT_DEPTH) != 0)
                {
                    stream << " AlphaBitDepth=" << value.alpha_bit_depth;
                }

                if ( (value.flags & SD_LP_SURFACE) != 0)
                {
                    stream << " Surface=" << ValueFormatter::format_hex(static_cast<uint32_t>(value.surface_address) );
                }

                if ( (value.flags & SD_PIXEL_FORMAT) != 0)
                {
                    stream << " PixelFormat=" << format_pixel_format(value.pixel_format);
                }

                if ( (value.flags & SD_CK_DEST_OVERLAY) != 0)
                {
                    stream << " ColorKeyDestOverlay=" << format_color_key_func(value.color_key_array[0]);
                }

                if ( (value.flags & SD_CK_DEST_BLT) != 0)
                {
                    stream << " ColorKeyDestBlt=" << format_color_key_func(value.color_key_array[1]);
                }

                if ( (value.flags & SD_CK_SRC_OVERLAY) != 0)
                {
                    stream << " ColorKeySrcOverlay=" << format_color_key_func(value.color_key_array[2]);
                }

                if ( (value.flags & SD_CK_SRC_BLT) != 0)
                {
                    stream << " ColorKeySrcBlt=" << format_color_key_func(value.color_key_array[3]);
                }

                if ( (value.flags & SD_TEXTURE_STAGE) != 0)
                {
                    stream << " TextureStage=" << value.texture_stage;
                }

                stream << "}";

                result = true;
            }

            break;
        }

        case Interception::Hooks::D3D7::ValueKind::VERTEX_BUFFER_DESC:
        {
            Interception::Hooks::D3D7::D3DVERTEXBUFFERDESC value;

            if (read_func(&value,
                          sizeof(value) ))
            {
                stream << "{Caps=" << ValueFormatter::format_hex(value.dwCaps)
                       << " FVF=" << format_fvf(value.dwFVF)
                       << " NumVertices=" << value.dwNumVertices << "}";

                result = true;
            }

            break;
        }

        case Interception::Hooks::D3D7::ValueKind::VIEWPORT:
        {
            Interception::Hooks::D3D7::D3DVIEWPORT7 value;

            if (read_func(&value,
                          sizeof(value) ))
            {
                stream << "{X=" << value.dwX
                       << " Y=" << value.dwY
                       << " Width=" << value.dwWidth
                       << " Height=" << value.dwHeight
                       << " MinZ=" << value.dvMinZ
                       << " MaxZ=" << value.dvMaxZ << "}";

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

std::string Capture::APIDumpPrinter::D3D7Decoder::format_surface_caps(const Interception::Hooks::D3D7::DDSCAPS2& in_value)
{
    std::ostringstream stream;

    stream << "{Caps=" << format_flag_table(D3D7FlagTable::SURFACE_CAPS,
                                            in_value.dwCaps)
           << " Caps2=" << format_flag_table(D3D7FlagTable::SURFACE_CAPS2,
                                             in_value.dwCaps2) << "}";

    return stream.str();
}

const char* Capture::APIDumpPrinter::D3D7Decoder::get_created_object_type_name_ptr(const Capture::APIDumpLoader::DumpedAPICall&   in_call,
                                                                                    const Interception::Hooks::D3D7::ArgumentInfo& in_info,
                                                                                    const Capture::APIDumpLoader::Workload&        in_workload)
{
    uint32_t    n_iid_argument = 0;
    const char* result_ptr     = in_info.object_type_name_ptr;

    /* What is asked for decides the type of the object. */
    if (Interception::Core::D3D7Utils::get_iid_argument_index(in_call.func,
                                                             &n_iid_argument) )
    {
        result_ptr = nullptr;

        if (n_iid_argument < in_call.arg_in_vec.size() )
        {
            const APIInterceptor::APIFunctionArgument& iid_argument = in_call.arg_in_vec.at(n_iid_argument);

            if (iid_argument.type == APIInterceptor::ARGTYPE_DATA_CHUNK_ID)
            {
                const auto chunk_ptr = Capture::APIDumpLoader::get_data_chunk_ptr(in_workload,
                                                                                  iid_argument.get_data_chunk_id() );

                if (chunk_ptr != nullptr)
                {
                    result_ptr = Interception::Core::D3D7Utils::get_object_type_name_ptr_for_iid(chunk_ptr->data(),
                                                                                                 chunk_ptr->size() );
                }
            }
        }
    }

    return (result_ptr != nullptr) ? result_ptr
                                   : "Object";
}

bool Capture::APIDumpPrinter::D3D7Decoder::print_argument(FILE*                                        in_file_handle,
                                                           const Capture::APIDumpLoader::DumpedAPICall& in_call,
                                                           const uint32_t&                              in_n_argument,
                                                           const bool&                                  in_is_out,
                                                           const APIInterceptor::APIFunctionArgument&   in_argument,
                                                           const Capture::APIDumpLoader::Workload&      in_workload) const
{
    Interception::Hooks::D3D7::ArgumentInfo info   = {};
    bool                                    result = false;
    std::string                             text;

    if (Interception::Core::D3D7Utils::get_argument_info(in_call.func,
                                                         in_n_argument,
                                                        &info) == false)
    {
        goto end;
    }

    switch (info.kind)
    {
        case Interception::Hooks::D3D7::ValueKind::BOOLEAN:
        {
            /* The flags which the hooks add are unsigned. */
            if (in_argument.type == APIInterceptor::ARGTYPE_I32)
            {
                text   = ValueFormatter::format_boolean(in_argument.get_i32() );
                result = true;
            }
            else
            if (in_argument.type == APIInterceptor::ARGTYPE_U32)
            {
                text   = ValueFormatter::format_boolean(static_cast<int32_t>(in_argument.get_u32() ));
                result = true;
            }

            break;
        }

        case Interception::Hooks::D3D7::ValueKind::PRIMITIVE_TYPE:
        case Interception::Hooks::D3D7::ValueKind::RENDER_STATE_TYPE:
        case Interception::Hooks::D3D7::ValueKind::STATE_BLOCK_TYPE:
        case Interception::Hooks::D3D7::ValueKind::TEXTURE_STAGE_STATE_TYPE:
        case Interception::Hooks::D3D7::ValueKind::TRANSFORM_STATE_TYPE:
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

        case Interception::Hooks::D3D7::ValueKind::BLT_FAST_FLAGS:
        case Interception::Hooks::D3D7::ValueKind::BLT_FLAGS:
        case Interception::Hooks::D3D7::ValueKind::CLEAR_FLAGS:
        case Interception::Hooks::D3D7::ValueKind::COLOR_KEY_FLAGS:
        case Interception::Hooks::D3D7::ValueKind::COOPERATIVE_LEVEL_FLAGS:
        case Interception::Hooks::D3D7::ValueKind::DRAW_FLAGS:
        case Interception::Hooks::D3D7::ValueKind::ENUM_DISPLAY_MODES_FLAGS:
        case Interception::Hooks::D3D7::ValueKind::ENUM_SURFACES_FLAGS:
        case Interception::Hooks::D3D7::ValueKind::FLIP_FLAGS:
        case Interception::Hooks::D3D7::ValueKind::LOCK_FLAGS:
        case Interception::Hooks::D3D7::ValueKind::OVERLAY_FLAGS:
        case Interception::Hooks::D3D7::ValueKind::PALETTE_FLAGS:
        case Interception::Hooks::D3D7::ValueKind::SET_DISPLAY_MODE_FLAGS:
        case Interception::Hooks::D3D7::ValueKind::VERTEX_OPERATION_FLAGS:
        case Interception::Hooks::D3D7::ValueKind::WAIT_FOR_VERTICAL_BLANK_FLAGS:
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

        case Interception::Hooks::D3D7::ValueKind::COLOR:
        {
            if (in_argument.type != APIInterceptor::ARGTYPE_U32)
            {
                goto end;
            }

            text   = ValueFormatter::format_color(in_argument.get_u32() );
            result = true;

            break;
        }

        case Interception::Hooks::D3D7::ValueKind::FVF_FLAGS:
        {
            if (in_argument.type != APIInterceptor::ARGTYPE_U32)
            {
                goto end;
            }

            text   = format_fvf(in_argument.get_u32() );
            result = true;

            break;
        }

        case Interception::Hooks::D3D7::ValueKind::HRESULT:
        {
            if (in_argument.type != APIInterceptor::ARGTYPE_I32)
            {
                goto end;
            }

            text   = format_hresult(in_argument.get_i32() );
            result = true;

            break;
        }

        case Interception::Hooks::D3D7::ValueKind::OBJECT:
        {
            if (in_argument.type != APIInterceptor::ARGTYPE_VOID_PTR)
            {
                goto end;
            }

            text   = m_object_namer.get_name(in_argument.get_ptr(),
                                             info.object_type_name_ptr);
            result = true;

            break;
        }

        case Interception::Hooks::D3D7::ValueKind::OBJECT_OUT:
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

            text   = m_object_namer.get_name(in_argument.get_ptr(),
                                             get_created_object_type_name_ptr(in_call,
                                                                              info,
                                                                              in_workload) );
            result = true;

            break;
        }

        case Interception::Hooks::D3D7::ValueKind::RENDER_STATE_VALUE:
        case Interception::Hooks::D3D7::ValueKind::TEXTURE_STAGE_STATE_VALUE:
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
            StateValueInfo value_info = {};
            const uint32_t state      = in_call.arg_in_vec.at(in_n_argument - 1).get_u32();

            if (info.kind == Interception::Hooks::D3D7::ValueKind::RENDER_STATE_VALUE)
            {
                D3D7Names::get_render_state_value_info(state,
                                                      &value_info);
            }
            else
            {
                D3D7Names::get_texture_stage_state_value_info(state,
                                                             &value_info);
            }

            text   = ValueFormatter::format_state_value(value_info,
                                                        in_argument.get_u32() );
            result = true;

            break;
        }

        case Interception::Hooks::D3D7::ValueKind::PLAIN:
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

            const auto chunk_ptr = Capture::APIDumpLoader::get_data_chunk_ptr(in_workload,
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

bool Capture::APIDumpPrinter::D3D7Decoder::print_returned_value(FILE*                                        in_file_handle,
                                                                 const Capture::APIDumpLoader::DumpedAPICall& in_call,
                                                                 const APIInterceptor::APIFunctionArgument&   in_returned_value) const
{
    Interception::Hooks::D3D7::ArgumentInfo info   = {};
    bool                                    result = false;
    std::string                             text;

    if (Interception::Core::D3D7Utils::get_return_info(in_call.func,
                                                      &info) == false)
    {
        goto end;
    }

    if (info.kind              == Interception::Hooks::D3D7::ValueKind::HRESULT &&
        in_returned_value.type == APIInterceptor::ARGTYPE_I32)
    {
        text   = format_hresult(in_returned_value.get_i32() );
        result = true;
    }
    else
    if (info.kind              == Interception::Hooks::D3D7::ValueKind::BOOLEAN &&
        in_returned_value.type == APIInterceptor::ARGTYPE_I32)
    {
        text   = ValueFormatter::format_boolean(in_returned_value.get_i32() );
        result = true;
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

void Capture::APIDumpPrinter::D3D7Decoder::register_created_objects(const Capture::APIDumpLoader::DumpedAPICall& in_call,
                                                                     const Capture::APIDumpLoader::Workload&      in_workload)
{
    const Interception::Hooks::D3D7::MethodInfo* method_info_ptr = Interception::Core::D3D7Utils::get_method_info_ptr(in_call.func);

    if (in_call.returned_value_ptr        != nullptr                     &&
        in_call.returned_value_ptr->type  == APIInterceptor::ARGTYPE_I32 &&
        in_call.returned_value_ptr->get_i32() >= 0)
    {
        /* The exports, Create* methods and DuplicateSurface always return new objects; Get* ones return existing objects, which may be
         * unknown to us, and so does QueryInterface.
         */
        const bool is_new = (method_info_ptr == nullptr)                                   ||
                            (strncmp(method_info_ptr->method_name_ptr,
                                     "Create",
                                     strlen("Create") ) == 0)                              ||
                            (strcmp(method_info_ptr->method_name_ptr,
                                    "DuplicateSurface") == 0);

        for (uint32_t n_argument = 0;
                      n_argument < in_call.arg_out_vec.size();
                    ++n_argument)
        {
            Interception::Hooks::D3D7::ArgumentInfo info = {};

            const bool is_argument_known = Interception::Core::D3D7Utils::get_argument_info(in_call.func,
                                                                                            n_argument,
                                                                                           &info);

            if (is_argument_known == false)
            {
                continue;
            }

            if (info.kind                               == Interception::Hooks::D3D7::ValueKind::OBJECT_OUT &&
                in_call.arg_out_vec.at(n_argument).type == APIInterceptor::ARGTYPE_VOID_PTR)
            {
                m_object_namer.register_object(in_call.arg_out_vec.at(n_argument).get_ptr(),
                                               get_created_object_type_name_ptr(in_call,
                                                                                info,
                                                                                in_workload),
                                               is_new);
            }
        }
    }
}
