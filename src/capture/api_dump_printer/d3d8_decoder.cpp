/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "d3d8_decoder.h"
#include "argument_formatter.h"
#include "common/macros.h"
#include "d3d8_names.h"
#include "interception/core/D3D8Utils/argument_info.h"
#include "interception/core/D3D8Utils/methods.h"
#include "value_formatter.h"
#include <sstream>
#include <string.h>

std::string Capture::APIDumpPrinter::D3D8Decoder::format_color_value(const Interception::Hooks::D3D8::D3DCOLORVALUE& in_value)
{
    std::ostringstream stream;

    stream << "(" << in_value.r << " " << in_value.g << " " << in_value.b << " " << in_value.a << ")";

    return stream.str();
}

std::string Capture::APIDumpPrinter::D3D8Decoder::format_enum(const Interception::Hooks::D3D8::ValueKind& in_kind,
                                                              const uint32_t&                             in_value)
{
    const ValueNameEntry* table_ptr = nullptr;
    uint32_t              n_entries = 0;

    get_value_name_table(in_kind,
                        &table_ptr,
                        &n_entries);

    return ValueFormatter::format_enum(table_ptr,
                                       n_entries,
                                       in_value);
}

std::string Capture::APIDumpPrinter::D3D8Decoder::format_flags(const Interception::Hooks::D3D8::ValueKind& in_kind,
                                                               const uint32_t&                             in_value)
{
    const FlagNameEntry* table_ptr = nullptr;
    uint32_t             n_entries = 0;

    get_flag_name_table(in_kind,
                       &table_ptr,
                       &n_entries);

    return ValueFormatter::format_flags(table_ptr,
                                        n_entries,
                                        in_value);
}

std::string Capture::APIDumpPrinter::D3D8Decoder::format_fvf(const uint32_t& in_value)
{
    /* A vertex shader handle has the highest bit set; a FVF never does. */
    static const ValueFormatter::FvfStyle style = {"PSIZE", true /* has_shader_handles */};

    return ValueFormatter::format_fvf(in_value,
                                      style);
}

std::string Capture::APIDumpPrinter::D3D8Decoder::format_hresult(const int32_t& in_value)
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

    return ValueFormatter::format_hresult(hresult_name_array,
                                          static_cast<uint32_t>(sizeof(hresult_name_array) / sizeof(hresult_name_array[0]) ),
                                          in_value);
}

std::string Capture::APIDumpPrinter::D3D8Decoder::format_resource_properties(const uint32_t& in_format,
                                                                             const uint32_t& in_type,
                                                                             const uint32_t& in_usage,
                                                                             const uint32_t& in_pool)
{
    const std::string format_name = format_enum(Interception::Hooks::D3D8::ValueKind::FORMAT,
                                                in_format);
    const std::string pool_name   = format_enum(Interception::Hooks::D3D8::ValueKind::POOL,
                                                in_pool);
    const std::string type_name   = format_enum(Interception::Hooks::D3D8::ValueKind::RESOURCE_TYPE,
                                                in_type);
    const std::string usage_names = format_flags(Interception::Hooks::D3D8::ValueKind::USAGE_FLAGS,
                                                 in_usage);

    return "Format=" + format_name + " Type=" + type_name + " Usage=" + usage_names + " Pool=" + pool_name;
}

bool Capture::APIDumpPrinter::D3D8Decoder::format_struct(const Interception::Hooks::D3D8::ValueKind& in_kind,
                                                         const std::vector<uint8_t>&                 in_chunk_u8_vec,
                                                         std::string*                                out_text_ptr)
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
        case Interception::Hooks::D3D8::ValueKind::ADAPTER_IDENTIFIER:
        {
            Interception::Hooks::D3D8::D3DADAPTER_IDENTIFIER8 value;

            if (read_func(&value,
                          sizeof(value) ))
            {
                const size_t      driver_n_chars      = strnlen(value.Driver,
                                                                sizeof(value.Driver) );
                const size_t      description_n_chars = strnlen(value.Description,
                                                                sizeof(value.Description) );
                const std::string driver_name(value.Driver,
                                              driver_n_chars);
                const std::string description(value.Description,
                                              description_n_chars);

                stream << "{Driver=\"" << driver_name << "\""
                       << " Description=\"" << description << "\""
                       << " DriverVersion=" << HIWORD(value.DriverVersion.HighPart) << "." << LOWORD(value.DriverVersion.HighPart)
                                            << "." << HIWORD(value.DriverVersion.LowPart) << "." << LOWORD(value.DriverVersion.LowPart)
                       << " VendorId=" << ValueFormatter::format_hex(value.VendorId)
                       << " DeviceId=" << ValueFormatter::format_hex(value.DeviceId)
                       << " SubSysId=" << ValueFormatter::format_hex(value.SubSysId)
                       << " Revision=" << value.Revision
                       << " WHQLLevel=" << value.WHQLLevel << "}";

                result = true;
            }

            break;
        }

        case Interception::Hooks::D3D8::ValueKind::BOX:
        {
            Interception::Hooks::D3D8::D3DBOX value;

            if (read_func(&value,
                          sizeof(value) ))
            {
                stream << "{Left=" << value.Left << " Top=" << value.Top << " Right=" << value.Right << " Bottom=" << value.Bottom
                       << " Front=" << value.Front << " Back=" << value.Back << "}";

                result = true;
            }

            break;
        }

        case Interception::Hooks::D3D8::ValueKind::CAPS:
        {
            Interception::Hooks::D3D8::D3DCAPS8 value;

            if (read_func(&value,
                          sizeof(value) ))
            {
                stream << "{DeviceType=" << format_enum(Interception::Hooks::D3D8::ValueKind::DEVICE_TYPE,
                                                       static_cast<uint32_t>(value.DeviceType) )
                       << " AdapterOrdinal=" << value.AdapterOrdinal
                       << " Caps=" << ValueFormatter::format_hex(value.Caps)
                       << " Caps2=" << ValueFormatter::format_hex(value.Caps2)
                       << " Caps3=" << ValueFormatter::format_hex(value.Caps3)
                       << " PresentationIntervals=" << ValueFormatter::format_hex(value.PresentationIntervals)
                       << " CursorCaps=" << ValueFormatter::format_hex(value.CursorCaps)
                       << " DevCaps=" << ValueFormatter::format_hex(value.DevCaps)
                       << " PrimitiveMiscCaps=" << ValueFormatter::format_hex(value.PrimitiveMiscCaps)
                       << " RasterCaps=" << ValueFormatter::format_hex(value.RasterCaps)
                       << " ZCmpCaps=" << ValueFormatter::format_hex(value.ZCmpCaps)
                       << " SrcBlendCaps=" << ValueFormatter::format_hex(value.SrcBlendCaps)
                       << " DestBlendCaps=" << ValueFormatter::format_hex(value.DestBlendCaps)
                       << " AlphaCmpCaps=" << ValueFormatter::format_hex(value.AlphaCmpCaps)
                       << " ShadeCaps=" << ValueFormatter::format_hex(value.ShadeCaps)
                       << " TextureCaps=" << ValueFormatter::format_hex(value.TextureCaps)
                       << " TextureFilterCaps=" << ValueFormatter::format_hex(value.TextureFilterCaps)
                       << " CubeTextureFilterCaps=" << ValueFormatter::format_hex(value.CubeTextureFilterCaps)
                       << " VolumeTextureFilterCaps=" << ValueFormatter::format_hex(value.VolumeTextureFilterCaps)
                       << " TextureAddressCaps=" << ValueFormatter::format_hex(value.TextureAddressCaps)
                       << " VolumeTextureAddressCaps=" << ValueFormatter::format_hex(value.VolumeTextureAddressCaps)
                       << " LineCaps=" << ValueFormatter::format_hex(value.LineCaps)
                       << " MaxTextureWidth=" << value.MaxTextureWidth
                       << " MaxTextureHeight=" << value.MaxTextureHeight
                       << " MaxVolumeExtent=" << value.MaxVolumeExtent
                       << " MaxTextureRepeat=" << value.MaxTextureRepeat
                       << " MaxTextureAspectRatio=" << value.MaxTextureAspectRatio
                       << " MaxAnisotropy=" << value.MaxAnisotropy
                       << " MaxVertexW=" << value.MaxVertexW
                       << " GuardBandLeft=" << value.GuardBandLeft
                       << " GuardBandTop=" << value.GuardBandTop
                       << " GuardBandRight=" << value.GuardBandRight
                       << " GuardBandBottom=" << value.GuardBandBottom
                       << " ExtentsAdjust=" << value.ExtentsAdjust
                       << " StencilCaps=" << ValueFormatter::format_hex(value.StencilCaps)
                       << " FVFCaps=" << ValueFormatter::format_hex(value.FVFCaps)
                       << " TextureOpCaps=" << ValueFormatter::format_hex(value.TextureOpCaps)
                       << " MaxTextureBlendStages=" << value.MaxTextureBlendStages
                       << " MaxSimultaneousTextures=" << value.MaxSimultaneousTextures
                       << " VertexProcessingCaps=" << ValueFormatter::format_hex(value.VertexProcessingCaps)
                       << " MaxActiveLights=" << value.MaxActiveLights
                       << " MaxUserClipPlanes=" << value.MaxUserClipPlanes
                       << " MaxVertexBlendMatrices=" << value.MaxVertexBlendMatrices
                       << " MaxVertexBlendMatrixIndex=" << value.MaxVertexBlendMatrixIndex
                       << " MaxPointSize=" << value.MaxPointSize
                       << " MaxPrimitiveCount=" << value.MaxPrimitiveCount
                       << " MaxVertexIndex=" << value.MaxVertexIndex
                       << " MaxStreams=" << value.MaxStreams
                       << " MaxStreamStride=" << value.MaxStreamStride
                       << " VertexShaderVersion=" << ValueFormatter::format_hex(value.VertexShaderVersion)
                       << " MaxVertexShaderConst=" << value.MaxVertexShaderConst
                       << " PixelShaderVersion=" << ValueFormatter::format_hex(value.PixelShaderVersion)
                       << " MaxPixelShaderValue=" << value.MaxPixelShaderValue
                       << "}";

                result = true;
            }

            break;
        }

        case Interception::Hooks::D3D8::ValueKind::CLIP_STATUS:
        {
            Interception::Hooks::D3D8::D3DCLIPSTATUS8 value;

            if (read_func(&value,
                          sizeof(value) ))
            {
                stream << "{ClipUnion=" << ValueFormatter::format_hex(value.ClipUnion) << " ClipIntersection=" << ValueFormatter::format_hex(value.ClipIntersection) << "}";

                result = true;
            }

            break;
        }

        case Interception::Hooks::D3D8::ValueKind::CREATION_PARAMETERS:
        {
            /* The layout depends on the pointer size of the dumped process. */
            const size_t pointer_size = (in_chunk_u8_vec.size() == CREATION_PARAMETERS_N_BYTES_32) ? POINTER_N_BYTES_32
                                                                                                    : POINTER_N_BYTES_64;

            if (in_chunk_u8_vec.size() == CREATION_PARAMETERS_N_BYTES_32 ||
                in_chunk_u8_vec.size() == CREATION_PARAMETERS_N_BYTES_64)
            {
                const uint32_t behavior_flags = read_u32_func(CREATION_PARAMETERS_HEAD_N_BYTES + pointer_size);
                const uint32_t device_type    = read_u32_func(1 * sizeof(uint32_t));

                stream << "{AdapterOrdinal=" << read_u32_func(0 * sizeof(uint32_t))
                       << " DeviceType=" << format_enum(Interception::Hooks::D3D8::ValueKind::DEVICE_TYPE,
                                                        device_type)
                       << " BehaviorFlags=" << format_flags(Interception::Hooks::D3D8::ValueKind::CREATE_FLAGS,
                                                            behavior_flags) << "}";

                result = true;
            }

            break;
        }

        case Interception::Hooks::D3D8::ValueKind::DISPLAY_MODE:
        {
            Interception::Hooks::D3D8::D3DDISPLAYMODE value;

            if (read_func(&value,
                          sizeof(value) ))
            {
                stream << "{Width=" << value.Width << " Height=" << value.Height << " RefreshRate=" << value.RefreshRate
                       << " Format=" << format_enum(Interception::Hooks::D3D8::ValueKind::FORMAT,
                                                    value.Format) << "}";

                result = true;
            }

            break;
        }

        case Interception::Hooks::D3D8::ValueKind::FLOAT_ARRAY:
        {
            if (in_chunk_u8_vec.size() % sizeof(float) == 0)
            {
                const size_t n_floats = in_chunk_u8_vec.size() / sizeof(float);

                stream << "[";

                for (size_t n_float = 0;
                            n_float < n_floats && n_float < MAX_N_DISPLAYED_ITEMS;
                          ++n_float)
                {
                    float value;

                    ::memcpy(&value,
                             in_chunk_u8_vec.data() + n_float * sizeof(float),
                             sizeof(float) );

                    stream << ((n_float == 0) ? "" : " ") << value;
                }

                stream << ((n_floats > MAX_N_DISPLAYED_ITEMS) ? " ..." : "") << "]";

                result = true;
            }

            break;
        }

        case Interception::Hooks::D3D8::ValueKind::GAMMA_RAMP:
        {
            Interception::Hooks::D3D8::D3DGAMMARAMP value;

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

        case Interception::Hooks::D3D8::ValueKind::GUID:
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

        case Interception::Hooks::D3D8::ValueKind::INDEX_BUFFER_DESC:
        {
            Interception::Hooks::D3D8::D3DINDEXBUFFER_DESC value;

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

        case Interception::Hooks::D3D8::ValueKind::LIGHT:
        {
            Interception::Hooks::D3D8::D3DLIGHT8 value;

            if (read_func(&value,
                          sizeof(value) ))
            {
                stream << "{Type=" << format_enum(Interception::Hooks::D3D8::ValueKind::LIGHT_TYPE,
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

        case Interception::Hooks::D3D8::ValueKind::LOCKED_BOX:
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

        case Interception::Hooks::D3D8::ValueKind::LOCKED_RECT:
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

        case Interception::Hooks::D3D8::ValueKind::MATERIAL:
        {
            Interception::Hooks::D3D8::D3DMATERIAL8 value;

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

        case Interception::Hooks::D3D8::ValueKind::MATRIX:
        {
            Interception::Hooks::D3D8::D3DMATRIX value;

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

        case Interception::Hooks::D3D8::ValueKind::POINT_ARRAY:
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

        case Interception::Hooks::D3D8::ValueKind::PRESENT_PARAMETERS:
        {
            /* The layout depends on the pointer size of the dumped process. */
            const size_t pointer_size = (in_chunk_u8_vec.size() == PRESENT_PARAMETERS_N_BYTES_32) ? POINTER_N_BYTES_32
                                                                                                  : POINTER_N_BYTES_64;

            if (in_chunk_u8_vec.size() == PRESENT_PARAMETERS_N_BYTES_32 ||
                in_chunk_u8_vec.size() == PRESENT_PARAMETERS_N_BYTES_64)
            {
                const size_t   tail_offset               = PRESENT_PARAMETERS_HEAD_N_BYTES + pointer_size;
                const uint32_t auto_depth_stencil_format = read_u32_func(tail_offset + 2 * sizeof(uint32_t));
                const uint32_t back_buffer_format        = read_u32_func(2 * sizeof(uint32_t));
                const uint32_t multi_sample_type         = read_u32_func(4 * sizeof(uint32_t));
                const uint32_t swap_effect               = read_u32_func(5 * sizeof(uint32_t));

                stream << "{BackBufferWidth=" << read_u32_func(0 * sizeof(uint32_t))
                       << " BackBufferHeight=" << read_u32_func(1 * sizeof(uint32_t))
                       << " BackBufferFormat=" << format_enum(Interception::Hooks::D3D8::ValueKind::FORMAT,
                                                              back_buffer_format)
                       << " BackBufferCount=" << read_u32_func(3 * sizeof(uint32_t))
                       << " MultiSampleType=" << format_enum(Interception::Hooks::D3D8::ValueKind::MULTI_SAMPLE_TYPE,
                                                             multi_sample_type)
                       << " SwapEffect=" << format_enum(Interception::Hooks::D3D8::ValueKind::SWAP_EFFECT,
                                                        swap_effect)
                       << " Windowed=" << ValueFormatter::format_boolean(static_cast<int32_t>(read_u32_func(tail_offset + 0 * sizeof(uint32_t)) ))
                       << " EnableAutoDepthStencil=" << ValueFormatter::format_boolean(static_cast<int32_t>(read_u32_func(tail_offset + 1 * sizeof(uint32_t)) ))
                       << " AutoDepthStencilFormat=" << format_enum(Interception::Hooks::D3D8::ValueKind::FORMAT,
                                                                    auto_depth_stencil_format)
                       << " Flags=" << ValueFormatter::format_hex(read_u32_func(tail_offset + 3 * sizeof(uint32_t)) )
                       << " FullScreen_RefreshRateInHz=" << read_u32_func(tail_offset + 4 * sizeof(uint32_t))
                       << " FullScreen_PresentationInterval=" << ValueFormatter::format_hex(read_u32_func(tail_offset + 5 * sizeof(uint32_t)) ) << "}";

                result = true;
            }

            break;
        }

        case Interception::Hooks::D3D8::ValueKind::RASTER_STATUS:
        {
            Interception::Hooks::D3D8::D3DRASTER_STATUS value;

            if (read_func(&value,
                          sizeof(value) ))
            {
                stream << "{InVBlank=" << ValueFormatter::format_boolean(value.InVBlank) << " ScanLine=" << value.ScanLine << "}";

                result = true;
            }

            break;
        }

        case Interception::Hooks::D3D8::ValueKind::RECT:
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

        case Interception::Hooks::D3D8::ValueKind::RECT_ARRAY:
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

        case Interception::Hooks::D3D8::ValueKind::RECT_PATCH_INFO:
        {
            Interception::Hooks::D3D8::D3DRECTPATCH_INFO value;

            if (read_func(&value,
                          sizeof(value) ))
            {
                stream << "{StartVertexOffsetWidth=" << value.StartVertexOffsetWidth
                       << " StartVertexOffsetHeight=" << value.StartVertexOffsetHeight
                       << " Width=" << value.Width
                       << " Height=" << value.Height
                       << " Stride=" << value.Stride
                       << " Basis=" << format_enum(Interception::Hooks::D3D8::ValueKind::BASIS_TYPE,
                                                   value.Basis)
                       << " Order=" << format_enum(Interception::Hooks::D3D8::ValueKind::ORDER_TYPE,
                                                   value.Order) << "}";

                result = true;
            }

            break;
        }

        case Interception::Hooks::D3D8::ValueKind::SURFACE_DESC:
        {
            Interception::Hooks::D3D8::D3DSURFACE_DESC value;

            if (read_func(&value,
                          sizeof(value) ))
            {
                stream << "{" << format_resource_properties(value.Format,
                                                            value.Type,
                                                            value.Usage,
                                                            value.Pool)
                       << " Size=" << value.Size
                       << " MultiSampleType=" << format_enum(Interception::Hooks::D3D8::ValueKind::MULTI_SAMPLE_TYPE,
                                                             value.MultiSampleType)
                       << " Width=" << value.Width
                       << " Height=" << value.Height << "}";

                result = true;
            }

            break;
        }

        case Interception::Hooks::D3D8::ValueKind::TRI_PATCH_INFO:
        {
            Interception::Hooks::D3D8::D3DTRIPATCH_INFO value;

            if (read_func(&value,
                          sizeof(value) ))
            {
                stream << "{StartVertexOffset=" << value.StartVertexOffset
                       << " NumVertices=" << value.NumVertices
                       << " Basis=" << format_enum(Interception::Hooks::D3D8::ValueKind::BASIS_TYPE,
                                                   value.Basis)
                       << " Order=" << format_enum(Interception::Hooks::D3D8::ValueKind::ORDER_TYPE,
                                                   value.Order) << "}";

                result = true;
            }

            break;
        }

        case Interception::Hooks::D3D8::ValueKind::VERTEX_BUFFER_DESC:
        {
            Interception::Hooks::D3D8::D3DVERTEXBUFFER_DESC value;

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

        case Interception::Hooks::D3D8::ValueKind::VIEWPORT:
        {
            Interception::Hooks::D3D8::D3DVIEWPORT8 value;

            if (read_func(&value,
                          sizeof(value) ))
            {
                stream << "{X=" << value.X << " Y=" << value.Y << " Width=" << value.Width << " Height=" << value.Height
                       << " MinZ=" << value.MinZ << " MaxZ=" << value.MaxZ << "}";

                result = true;
            }

            break;
        }

        case Interception::Hooks::D3D8::ValueKind::VOLUME_DESC:
        {
            Interception::Hooks::D3D8::D3DVOLUME_DESC value;

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

std::string Capture::APIDumpPrinter::D3D8Decoder::get_object_name(const void* in_object_ptr,
                                                                  const char* in_type_name_ptr) const
{
    return m_object_namer.get_name(reinterpret_cast<uint64_t>(in_object_ptr),
                                   in_type_name_ptr);
}

bool Capture::APIDumpPrinter::D3D8Decoder::print_argument(FILE*                                        in_file_handle,
                                                          const Capture::APIDumpLoader::DumpedAPICall& in_call,
                                                          const uint32_t&                              in_n_argument,
                                                          const bool&                                  in_is_out,
                                                          const APIInterceptor::APIFunctionArgument&   in_argument,
                                                          const Capture::APIDumpLoader::Workload&      in_workload) const
{
    Interception::Hooks::D3D8::ArgumentInfo info   = {};
    bool                                    result = false;
    std::string                             text;

    if (Interception::Core::D3D8Utils::get_argument_info(in_call.func,
                                                         in_n_argument,
                                                        &info) == false)
    {
        goto end;
    }

    switch (info.kind)
    {
        case Interception::Hooks::D3D8::ValueKind::BOOLEAN:
        {
            result = ArgumentFormatter::format_boolean(in_argument,
                                                      &text);

            break;
        }

        case Interception::Hooks::D3D8::ValueKind::BACK_BUFFER_TYPE:
        case Interception::Hooks::D3D8::ValueKind::CUBE_MAP_FACE:
        case Interception::Hooks::D3D8::ValueKind::DEVICE_TYPE:
        case Interception::Hooks::D3D8::ValueKind::FORMAT:
        case Interception::Hooks::D3D8::ValueKind::MULTI_SAMPLE_TYPE:
        case Interception::Hooks::D3D8::ValueKind::POOL:
        case Interception::Hooks::D3D8::ValueKind::PRIMITIVE_TYPE:
        case Interception::Hooks::D3D8::ValueKind::RENDER_STATE_TYPE:
        case Interception::Hooks::D3D8::ValueKind::RESOURCE_TYPE:
        case Interception::Hooks::D3D8::ValueKind::STATE_BLOCK_TYPE:
        case Interception::Hooks::D3D8::ValueKind::SWAP_EFFECT:
        case Interception::Hooks::D3D8::ValueKind::TEXTURE_STAGE_STATE_TYPE:
        case Interception::Hooks::D3D8::ValueKind::TRANSFORM_STATE_TYPE:
        {
            const auto format_enum_func = [&info](const uint32_t& in_value)
            {
                return format_enum(info.kind,
                                   in_value);
            };

            result = ArgumentFormatter::format_u32(in_argument,
                                                   format_enum_func,
                                                  &text);

            break;
        }

        case Interception::Hooks::D3D8::ValueKind::CLEAR_FLAGS:
        case Interception::Hooks::D3D8::ValueKind::CREATE_FLAGS:
        case Interception::Hooks::D3D8::ValueKind::LOCK_FLAGS:
        case Interception::Hooks::D3D8::ValueKind::USAGE_FLAGS:
        {
            const auto format_flags_func = [&info](const uint32_t& in_value)
            {
                return format_flags(info.kind,
                                    in_value);
            };

            result = ArgumentFormatter::format_u32(in_argument,
                                                   format_flags_func,
                                                  &text);

            break;
        }

        case Interception::Hooks::D3D8::ValueKind::COLOR:
        {
            result = ArgumentFormatter::format_u32(in_argument,
                                                   &ValueFormatter::format_color,
                                                  &text);

            break;
        }

        case Interception::Hooks::D3D8::ValueKind::FVF_FLAGS:
        {
            result = ArgumentFormatter::format_u32(in_argument,
                                                   &format_fvf,
                                                  &text);

            break;
        }

        case Interception::Hooks::D3D8::ValueKind::HRESULT:
        {
            result = ArgumentFormatter::format_i32(in_argument,
                                                   &format_hresult,
                                                  &text);

            break;
        }

        case Interception::Hooks::D3D8::ValueKind::OBJECT:
        {
            const auto get_object_name_func = [this, &info](const void* in_pointer)
            {
                return get_object_name(in_pointer,
                                       info.object_type_name_ptr);
            };

            result = ArgumentFormatter::format_pointer(in_argument,
                                                       get_object_name_func,
                                                      &text);

            break;
        }

        case Interception::Hooks::D3D8::ValueKind::OBJECT_OUT:
        {
            const auto get_object_name_func = [this, &info](const void* in_pointer)
            {
                return get_object_name(in_pointer,
                                       info.object_type_name_ptr);
            };

            result = ArgumentFormatter::format_pointer_out(in_argument,
                                                           in_is_out,
                                                           get_object_name_func,
                                                          &text);

            break;
        }

        case Interception::Hooks::D3D8::ValueKind::RENDER_STATE_VALUE:
        case Interception::Hooks::D3D8::ValueKind::TEXTURE_STAGE_STATE_VALUE:
        {
            const auto format_state_value_func = [this, &info](const uint32_t& in_state,
                                                               const uint32_t& in_value)
            {
                StateValueInfo value_info = {};

                if (info.kind == Interception::Hooks::D3D8::ValueKind::RENDER_STATE_VALUE)
                {
                    get_render_state_value_info(in_state,
                                               &value_info);
                }
                else
                {
                    get_texture_stage_state_value_info(in_state,
                                                      &value_info);
                }

                return ValueFormatter::format_state_value(value_info,
                                                          in_value);
            };

            result = ArgumentFormatter::format_u32_after_state(in_call,
                                                               in_n_argument,
                                                               in_argument,
                                                               format_state_value_func,
                                                              &text);

            break;
        }

        case Interception::Hooks::D3D8::ValueKind::PLAIN:
        {
            break;
        }

        default:
        {
            const auto format_struct_func = [&info](const Capture::APIDumpLoader::DataChunk& in_chunk,
                                                    std::string*                             out_text_ptr)
            {
                return format_struct(info.kind,
                                     in_chunk,
                                     out_text_ptr);
            };

            /* Structures and GUIDs, stored as data chunks. */
            result = ArgumentFormatter::format_chunk(in_workload,
                                                     in_argument,
                                                     format_struct_func,
                                                    &text);

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

bool Capture::APIDumpPrinter::D3D8Decoder::print_returned_value(FILE*                                        in_file_handle,
                                                                const Capture::APIDumpLoader::DumpedAPICall& in_call,
                                                                const APIInterceptor::APIFunctionArgument&   in_returned_value) const
{
    Interception::Hooks::D3D8::ArgumentInfo info   = {};
    bool                                    result = false;
    std::string                             text;

    if (in_call.func == APIInterceptor::APIFUNCTION_D3D8_DIRECT3DCREATE8)
    {
        text   = get_object_name(in_returned_value.get_ptr(),
                                 "Direct3D8");
        result = true;
    }
    else
    {
        if (Interception::Core::D3D8Utils::get_return_info(in_call.func,
                                                          &info) == false)
        {
            goto end;
        }

        if (info.kind              == Interception::Hooks::D3D8::ValueKind::HRESULT &&
            in_returned_value.type == APIInterceptor::ARGTYPE_I32)
        {
            text   = format_hresult(in_returned_value.get_i32() );
            result = true;
        }
        else
        if (info.kind              == Interception::Hooks::D3D8::ValueKind::BOOLEAN &&
            in_returned_value.type == APIInterceptor::ARGTYPE_I32)
        {
            text   = ValueFormatter::format_boolean(in_returned_value.get_i32() );
            result = true;
        }
        else
        if (info.kind              == Interception::Hooks::D3D8::ValueKind::RESOURCE_TYPE &&
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

void Capture::APIDumpPrinter::D3D8Decoder::forget_released_objects(const Capture::APIDumpLoader::DumpedAPICall& in_call)
{
    const auto* method_info_ptr = Interception::Core::D3D8Utils::get_method_info_ptr(in_call.func);

    if (method_info_ptr != nullptr &&
        ::strcmp(method_info_ptr->method_name_ptr,
                 "Release") == 0)
    {
        m_object_namer.forget_after_release(in_call);
    }
}

void Capture::APIDumpPrinter::D3D8Decoder::register_created_objects(const Capture::APIDumpLoader::DumpedAPICall& in_call,
                                                                    const Capture::APIDumpLoader::Workload&      in_workload)
{
    (void) in_workload;

    const auto register_func = [&](const void* in_object_ptr,
                                   const char* in_type_name_ptr,
                                   const bool& in_is_new)
    {
        m_object_namer.register_object(reinterpret_cast<uint64_t>(in_object_ptr),
                                       in_type_name_ptr,
                                       in_is_new);
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
    {
        const auto* method_info_ptr = Interception::Core::D3D8Utils::get_method_info_ptr(in_call.func);

        if (in_call.returned_value_ptr        != nullptr                     &&
            in_call.returned_value_ptr->type  == APIInterceptor::ARGTYPE_I32 &&
            in_call.returned_value_ptr->get_i32() >= 0                       &&
            method_info_ptr                   != nullptr)
        {
            /* Create* methods always return new objects; Get* ones return existing objects, which may be unknown to us. */
            constexpr char CREATE_PREFIX[] = "Create";

            const bool is_create = (strncmp(method_info_ptr->method_name_ptr,
                                            CREATE_PREFIX,
                                            sizeof(CREATE_PREFIX) - 1) == 0);

            for (uint32_t n_argument = 0;
                          n_argument < in_call.arg_out_vec.size();
                        ++n_argument)
            {
                Interception::Hooks::D3D8::ArgumentInfo info = {};

                const bool is_argument_known = Interception::Core::D3D8Utils::get_argument_info(in_call.func,
                                                                                                n_argument,
                                                                                               &info);

                if (is_argument_known == false)
                {
                    continue;
                }

                if (info.kind                               == Interception::Hooks::D3D8::ValueKind::OBJECT_OUT &&
                    in_call.arg_out_vec.at(n_argument).type == APIInterceptor::ARGTYPE_VOID_PTR)
                {
                    register_func(in_call.arg_out_vec.at(n_argument).get_ptr(),
                                  info.object_type_name_ptr,
                                  is_create);
                }
            }
        }
    }
}
