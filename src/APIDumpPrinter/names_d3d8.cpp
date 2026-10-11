/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Names of D3D8 enums and flags. Tables of values which the D3D8 types do not define use the D3D8 SDK values.
 */
#include "d3d8_names.h"
#include "D3D8/types.h"

#define D3D8_FLAG_NAME(flag)          {static_cast<uint32_t>(D3D8::flag), #flag}
#define D3D8_NAMED_VALUE(name, value) {name, value}
#define D3D8_VALUE_NAME(enumerator)   {#enumerator, static_cast<uint32_t>(D3D8::enumerator)}

#define D3D8_TABLE(array) array, static_cast<uint32_t>(sizeof(array) / sizeof(array[0]) )

bool APIDumpPrinter::get_flag_name_table(const D3D8::ValueKind& in_kind,
                                         const FlagNameEntry**  out_table_ptr_ptr,
                                         uint32_t*              out_n_entries_ptr)
{
    static const FlagNameEntry clear_flag_name_array[] =
    {
        D3D8_FLAG_NAME(D3DCLEAR_TARGET),
        D3D8_FLAG_NAME(D3DCLEAR_ZBUFFER),
        D3D8_FLAG_NAME(D3DCLEAR_STENCIL),
    };

    static const FlagNameEntry create_flag_name_array[] =
    {
        D3D8_FLAG_NAME(D3DCREATE_FPU_PRESERVE),
        D3D8_FLAG_NAME(D3DCREATE_MULTITHREADED),
        D3D8_FLAG_NAME(D3DCREATE_PUREDEVICE),
        D3D8_FLAG_NAME(D3DCREATE_SOFTWARE_VERTEXPROCESSING),
        D3D8_FLAG_NAME(D3DCREATE_HARDWARE_VERTEXPROCESSING),
        D3D8_FLAG_NAME(D3DCREATE_MIXED_VERTEXPROCESSING),
    };

    static const FlagNameEntry lock_flag_name_array[] =
    {
        D3D8_FLAG_NAME(D3DLOCK_READONLY),
        D3D8_FLAG_NAME(D3DLOCK_NOSYSLOCK),
        D3D8_FLAG_NAME(D3DLOCK_NOOVERWRITE),
        D3D8_FLAG_NAME(D3DLOCK_DISCARD),
        D3D8_FLAG_NAME(D3DLOCK_NO_DIRTY_UPDATE),
    };

    static const FlagNameEntry usage_flag_name_array[] =
    {
        D3D8_FLAG_NAME(D3DUSAGE_RENDERTARGET),
        D3D8_FLAG_NAME(D3DUSAGE_DEPTHSTENCIL),
        D3D8_FLAG_NAME(D3DUSAGE_WRITEONLY),
        D3D8_FLAG_NAME(D3DUSAGE_SOFTWAREPROCESSING),
        D3D8_FLAG_NAME(D3DUSAGE_DONOTCLIP),
        D3D8_FLAG_NAME(D3DUSAGE_POINTS),
        D3D8_FLAG_NAME(D3DUSAGE_RTPATCHES),
        D3D8_FLAG_NAME(D3DUSAGE_NPATCHES),
        D3D8_FLAG_NAME(D3DUSAGE_DYNAMIC),
    };

    const auto set_table_func = [&](const FlagNameEntry* in_table_ptr,
                                    const uint32_t&      in_n_entries)
    {
        *out_table_ptr_ptr = in_table_ptr;
        *out_n_entries_ptr = in_n_entries;
    };

    bool result = true;

    switch (in_kind)
    {
        case D3D8::ValueKind::ClearFlags:
        {
            set_table_func(D3D8_TABLE(clear_flag_name_array) );

            break;
        }

        case D3D8::ValueKind::CreateFlags:
        {
            set_table_func(D3D8_TABLE(create_flag_name_array) );

            break;
        }

        case D3D8::ValueKind::LockFlags:
        {
            set_table_func(D3D8_TABLE(lock_flag_name_array) );

            break;
        }

        case D3D8::ValueKind::UsageFlags:
        {
            set_table_func(D3D8_TABLE(usage_flag_name_array) );

            break;
        }

        default:
        {
            result = false;

            break;
        }
    }

    return result;
}

bool APIDumpPrinter::get_render_state_value_info(const uint32_t& in_render_state,
                                                 StateValueInfo* out_info_ptr)
{
    static const ValueNameEntry z_buffer_type_name_array[] =
    {
        D3D8_NAMED_VALUE("D3DZB_FALSE",  0),
        D3D8_NAMED_VALUE("D3DZB_TRUE",   1),
        D3D8_NAMED_VALUE("D3DZB_USEW",   2),
    };

    static const ValueNameEntry fill_mode_name_array[] =
    {
        D3D8_NAMED_VALUE("D3DFILL_POINT",     1),
        D3D8_NAMED_VALUE("D3DFILL_WIREFRAME", 2),
        D3D8_NAMED_VALUE("D3DFILL_SOLID",     3),
    };

    static const ValueNameEntry shade_mode_name_array[] =
    {
        D3D8_NAMED_VALUE("D3DSHADE_FLAT",    1),
        D3D8_NAMED_VALUE("D3DSHADE_GOURAUD", 2),
        D3D8_NAMED_VALUE("D3DSHADE_PHONG",   3),
    };

    static const ValueNameEntry blend_name_array[] =
    {
        D3D8_NAMED_VALUE("D3DBLEND_ZERO",            1),
        D3D8_NAMED_VALUE("D3DBLEND_ONE",             2),
        D3D8_NAMED_VALUE("D3DBLEND_SRCCOLOR",        3),
        D3D8_NAMED_VALUE("D3DBLEND_INVSRCCOLOR",     4),
        D3D8_NAMED_VALUE("D3DBLEND_SRCALPHA",        5),
        D3D8_NAMED_VALUE("D3DBLEND_INVSRCALPHA",     6),
        D3D8_NAMED_VALUE("D3DBLEND_DESTALPHA",       7),
        D3D8_NAMED_VALUE("D3DBLEND_INVDESTALPHA",    8),
        D3D8_NAMED_VALUE("D3DBLEND_DESTCOLOR",       9),
        D3D8_NAMED_VALUE("D3DBLEND_INVDESTCOLOR",    10),
        D3D8_NAMED_VALUE("D3DBLEND_SRCALPHASAT",     11),
        D3D8_NAMED_VALUE("D3DBLEND_BOTHSRCALPHA",    12),
        D3D8_NAMED_VALUE("D3DBLEND_BOTHINVSRCALPHA", 13),
    };

    static const ValueNameEntry cull_name_array[] =
    {
        D3D8_NAMED_VALUE("D3DCULL_NONE", 1),
        D3D8_NAMED_VALUE("D3DCULL_CW",   2),
        D3D8_NAMED_VALUE("D3DCULL_CCW",  3),
    };

    static const ValueNameEntry cmp_func_name_array[] =
    {
        D3D8_NAMED_VALUE("D3DCMP_NEVER",        1),
        D3D8_NAMED_VALUE("D3DCMP_LESS",         2),
        D3D8_NAMED_VALUE("D3DCMP_EQUAL",        3),
        D3D8_NAMED_VALUE("D3DCMP_LESSEQUAL",    4),
        D3D8_NAMED_VALUE("D3DCMP_GREATER",      5),
        D3D8_NAMED_VALUE("D3DCMP_NOTEQUAL",     6),
        D3D8_NAMED_VALUE("D3DCMP_GREATEREQUAL", 7),
        D3D8_NAMED_VALUE("D3DCMP_ALWAYS",       8),
    };

    static const ValueNameEntry stencil_op_name_array[] =
    {
        D3D8_NAMED_VALUE("D3DSTENCILOP_KEEP",    1),
        D3D8_NAMED_VALUE("D3DSTENCILOP_ZERO",    2),
        D3D8_NAMED_VALUE("D3DSTENCILOP_REPLACE", 3),
        D3D8_NAMED_VALUE("D3DSTENCILOP_INCRSAT", 4),
        D3D8_NAMED_VALUE("D3DSTENCILOP_DECRSAT", 5),
        D3D8_NAMED_VALUE("D3DSTENCILOP_INVERT",  6),
        D3D8_NAMED_VALUE("D3DSTENCILOP_INCR",    7),
        D3D8_NAMED_VALUE("D3DSTENCILOP_DECR",    8),
    };

    static const ValueNameEntry fog_mode_name_array[] =
    {
        D3D8_NAMED_VALUE("D3DFOG_NONE",   0),
        D3D8_NAMED_VALUE("D3DFOG_EXP",    1),
        D3D8_NAMED_VALUE("D3DFOG_EXP2",   2),
        D3D8_NAMED_VALUE("D3DFOG_LINEAR", 3),
    };

    static const ValueNameEntry material_color_source_name_array[] =
    {
        D3D8_NAMED_VALUE("D3DMCS_MATERIAL", 0),
        D3D8_NAMED_VALUE("D3DMCS_COLOR1",   1),
        D3D8_NAMED_VALUE("D3DMCS_COLOR2",   2),
    };

    static const ValueNameEntry blend_op_name_array[] =
    {
        D3D8_NAMED_VALUE("D3DBLENDOP_ADD",         1),
        D3D8_NAMED_VALUE("D3DBLENDOP_SUBTRACT",    2),
        D3D8_NAMED_VALUE("D3DBLENDOP_REVSUBTRACT", 3),
        D3D8_NAMED_VALUE("D3DBLENDOP_MIN",         4),
        D3D8_NAMED_VALUE("D3DBLENDOP_MAX",         5),
    };

    const auto set_info_func = [&](const StateValueFormat& in_format,
                                   const ValueNameEntry*   in_table_ptr,
                                   const uint32_t&         in_n_entries)
    {
        out_info_ptr->format    = in_format;
        out_info_ptr->n_entries = in_n_entries;
        out_info_ptr->table_ptr = in_table_ptr;
    };

    bool result = true;

    switch (in_render_state)
    {
        case D3D8::D3DRS_ZENABLE:
        {
            set_info_func(StateValueFormat::Name,
                          D3D8_TABLE(z_buffer_type_name_array) );

            break;
        }

        case D3D8::D3DRS_FILLMODE:
        {
            set_info_func(StateValueFormat::Name,
                          D3D8_TABLE(fill_mode_name_array) );

            break;
        }

        case D3D8::D3DRS_SHADEMODE:
        {
            set_info_func(StateValueFormat::Name,
                          D3D8_TABLE(shade_mode_name_array) );

            break;
        }

        case D3D8::D3DRS_SRCBLEND:
        case D3D8::D3DRS_DESTBLEND:
        {
            set_info_func(StateValueFormat::Name,
                          D3D8_TABLE(blend_name_array) );

            break;
        }

        case D3D8::D3DRS_CULLMODE:
        {
            set_info_func(StateValueFormat::Name,
                          D3D8_TABLE(cull_name_array) );

            break;
        }

        case D3D8::D3DRS_ZFUNC:
        case D3D8::D3DRS_ALPHAFUNC:
        case D3D8::D3DRS_STENCILFUNC:
        {
            set_info_func(StateValueFormat::Name,
                          D3D8_TABLE(cmp_func_name_array) );

            break;
        }

        case D3D8::D3DRS_STENCILFAIL:
        case D3D8::D3DRS_STENCILZFAIL:
        case D3D8::D3DRS_STENCILPASS:
        {
            set_info_func(StateValueFormat::Name,
                          D3D8_TABLE(stencil_op_name_array) );

            break;
        }

        case D3D8::D3DRS_FOGTABLEMODE:
        case D3D8::D3DRS_FOGVERTEXMODE:
        {
            set_info_func(StateValueFormat::Name,
                          D3D8_TABLE(fog_mode_name_array) );

            break;
        }

        case D3D8::D3DRS_DIFFUSEMATERIALSOURCE:
        case D3D8::D3DRS_SPECULARMATERIALSOURCE:
        case D3D8::D3DRS_AMBIENTMATERIALSOURCE:
        case D3D8::D3DRS_EMISSIVEMATERIALSOURCE:
        {
            set_info_func(StateValueFormat::Name,
                          D3D8_TABLE(material_color_source_name_array) );

            break;
        }

        case D3D8::D3DRS_BLENDOP:
        {
            set_info_func(StateValueFormat::Name,
                          D3D8_TABLE(blend_op_name_array) );

            break;
        }

        case D3D8::D3DRS_ALPHABLENDENABLE:
        case D3D8::D3DRS_ALPHATESTENABLE:
        case D3D8::D3DRS_CLIPPING:
        case D3D8::D3DRS_COLORVERTEX:
        case D3D8::D3DRS_DITHERENABLE:
        case D3D8::D3DRS_EDGEANTIALIAS:
        case D3D8::D3DRS_FOGENABLE:
        case D3D8::D3DRS_INDEXEDVERTEXBLENDENABLE:
        case D3D8::D3DRS_LASTPIXEL:
        case D3D8::D3DRS_LIGHTING:
        case D3D8::D3DRS_LOCALVIEWER:
        case D3D8::D3DRS_MULTISAMPLEANTIALIAS:
        case D3D8::D3DRS_NORMALIZENORMALS:
        case D3D8::D3DRS_POINTSCALEENABLE:
        case D3D8::D3DRS_POINTSPRITEENABLE:
        case D3D8::D3DRS_RANGEFOGENABLE:
        case D3D8::D3DRS_SOFTWAREVERTEXPROCESSING:
        case D3D8::D3DRS_SPECULARENABLE:
        case D3D8::D3DRS_STENCILENABLE:
        case D3D8::D3DRS_ZVISIBLE:
        case D3D8::D3DRS_ZWRITEENABLE:
        {
            set_info_func(StateValueFormat::Boolean,
                          nullptr,
                          0);

            break;
        }

        case D3D8::D3DRS_AMBIENT:
        case D3D8::D3DRS_FOGCOLOR:
        case D3D8::D3DRS_TEXTUREFACTOR:
        {
            set_info_func(StateValueFormat::Color,
                          nullptr,
                          0);

            break;
        }

        case D3D8::D3DRS_FOGDENSITY:
        case D3D8::D3DRS_FOGEND:
        case D3D8::D3DRS_FOGSTART:
        case D3D8::D3DRS_PATCHSEGMENTS:
        case D3D8::D3DRS_POINTSCALE_A:
        case D3D8::D3DRS_POINTSCALE_B:
        case D3D8::D3DRS_POINTSCALE_C:
        case D3D8::D3DRS_POINTSIZE:
        case D3D8::D3DRS_POINTSIZE_MAX:
        case D3D8::D3DRS_POINTSIZE_MIN:
        case D3D8::D3DRS_TWEENFACTOR:
        {
            set_info_func(StateValueFormat::Float,
                          nullptr,
                          0);

            break;
        }

        case D3D8::D3DRS_CLIPPLANEENABLE:
        case D3D8::D3DRS_COLORWRITEENABLE:
        case D3D8::D3DRS_MULTISAMPLEMASK:
        case D3D8::D3DRS_STENCILMASK:
        case D3D8::D3DRS_STENCILWRITEMASK:
        case D3D8::D3DRS_WRAP0:
        case D3D8::D3DRS_WRAP1:
        case D3D8::D3DRS_WRAP2:
        case D3D8::D3DRS_WRAP3:
        case D3D8::D3DRS_WRAP4:
        case D3D8::D3DRS_WRAP5:
        case D3D8::D3DRS_WRAP6:
        case D3D8::D3DRS_WRAP7:
        {
            set_info_func(StateValueFormat::Hex,
                          nullptr,
                          0);

            break;
        }

        default:
        {
            set_info_func(StateValueFormat::Raw,
                          nullptr,
                          0);

            result = false;

            break;
        }
    }

    return result;
}

bool APIDumpPrinter::get_texture_stage_state_value_info(const uint32_t& in_texture_stage_state,
                                                        StateValueInfo* out_info_ptr)
{
    static const ValueNameEntry texture_op_name_array[] =
    {
        D3D8_NAMED_VALUE("D3DTOP_DISABLE",                   1),
        D3D8_NAMED_VALUE("D3DTOP_SELECTARG1",                2),
        D3D8_NAMED_VALUE("D3DTOP_SELECTARG2",                3),
        D3D8_NAMED_VALUE("D3DTOP_MODULATE",                  4),
        D3D8_NAMED_VALUE("D3DTOP_MODULATE2X",                5),
        D3D8_NAMED_VALUE("D3DTOP_MODULATE4X",                6),
        D3D8_NAMED_VALUE("D3DTOP_ADD",                       7),
        D3D8_NAMED_VALUE("D3DTOP_ADDSIGNED",                 8),
        D3D8_NAMED_VALUE("D3DTOP_ADDSIGNED2X",               9),
        D3D8_NAMED_VALUE("D3DTOP_SUBTRACT",                  10),
        D3D8_NAMED_VALUE("D3DTOP_ADDSMOOTH",                 11),
        D3D8_NAMED_VALUE("D3DTOP_BLENDDIFFUSEALPHA",         12),
        D3D8_NAMED_VALUE("D3DTOP_BLENDTEXTUREALPHA",         13),
        D3D8_NAMED_VALUE("D3DTOP_BLENDFACTORALPHA",          14),
        D3D8_NAMED_VALUE("D3DTOP_BLENDTEXTUREALPHAPM",       15),
        D3D8_NAMED_VALUE("D3DTOP_BLENDCURRENTALPHA",         16),
        D3D8_NAMED_VALUE("D3DTOP_PREMODULATE",               17),
        D3D8_NAMED_VALUE("D3DTOP_MODULATEALPHA_ADDCOLOR",    18),
        D3D8_NAMED_VALUE("D3DTOP_MODULATECOLOR_ADDALPHA",    19),
        D3D8_NAMED_VALUE("D3DTOP_MODULATEINVALPHA_ADDCOLOR", 20),
        D3D8_NAMED_VALUE("D3DTOP_MODULATEINVCOLOR_ADDALPHA", 21),
        D3D8_NAMED_VALUE("D3DTOP_BUMPENVMAP",                22),
        D3D8_NAMED_VALUE("D3DTOP_BUMPENVMAPLUMINANCE",       23),
        D3D8_NAMED_VALUE("D3DTOP_DOTPRODUCT3",               24),
        D3D8_NAMED_VALUE("D3DTOP_MULTIPLYADD",               25),
        D3D8_NAMED_VALUE("D3DTOP_LERP",                      26),
    };

    static const ValueNameEntry texture_argument_name_array[] =
    {
        D3D8_NAMED_VALUE("D3DTA_DIFFUSE",  0),
        D3D8_NAMED_VALUE("D3DTA_CURRENT",  1),
        D3D8_NAMED_VALUE("D3DTA_TEXTURE",  2),
        D3D8_NAMED_VALUE("D3DTA_TFACTOR",  3),
        D3D8_NAMED_VALUE("D3DTA_SPECULAR", 4),
        D3D8_NAMED_VALUE("D3DTA_TEMP",     5),
    };

    static const ValueNameEntry texture_address_name_array[] =
    {
        D3D8_NAMED_VALUE("D3DTADDRESS_WRAP",       1),
        D3D8_NAMED_VALUE("D3DTADDRESS_MIRROR",     2),
        D3D8_NAMED_VALUE("D3DTADDRESS_CLAMP",      3),
        D3D8_NAMED_VALUE("D3DTADDRESS_BORDER",     4),
        D3D8_NAMED_VALUE("D3DTADDRESS_MIRRORONCE", 5),
    };

    static const ValueNameEntry texture_filter_name_array[] =
    {
        D3D8_NAMED_VALUE("D3DTEXF_NONE",          0),
        D3D8_NAMED_VALUE("D3DTEXF_POINT",         1),
        D3D8_NAMED_VALUE("D3DTEXF_LINEAR",        2),
        D3D8_NAMED_VALUE("D3DTEXF_ANISOTROPIC",   3),
        D3D8_NAMED_VALUE("D3DTEXF_FLATCUBIC",     4),
        D3D8_NAMED_VALUE("D3DTEXF_GAUSSIANCUBIC", 5),
    };

    const auto set_info_func = [&](const StateValueFormat& in_format,
                                   const ValueNameEntry*   in_table_ptr,
                                   const uint32_t&         in_n_entries)
    {
        out_info_ptr->format    = in_format;
        out_info_ptr->n_entries = in_n_entries;
        out_info_ptr->table_ptr = in_table_ptr;
    };

    bool result = true;

    switch (in_texture_stage_state)
    {
        case D3D8::D3DTSS_COLOROP:
        case D3D8::D3DTSS_ALPHAOP:
        {
            set_info_func(StateValueFormat::Name,
                          D3D8_TABLE(texture_op_name_array) );

            break;
        }

        case D3D8::D3DTSS_COLORARG0:
        case D3D8::D3DTSS_COLORARG1:
        case D3D8::D3DTSS_COLORARG2:
        case D3D8::D3DTSS_ALPHAARG0:
        case D3D8::D3DTSS_ALPHAARG1:
        case D3D8::D3DTSS_ALPHAARG2:
        case D3D8::D3DTSS_RESULTARG:
        {
            set_info_func(StateValueFormat::TextureArgument,
                          D3D8_TABLE(texture_argument_name_array) );

            break;
        }

        case D3D8::D3DTSS_ADDRESSU:
        case D3D8::D3DTSS_ADDRESSV:
        case D3D8::D3DTSS_ADDRESSW:
        {
            set_info_func(StateValueFormat::Name,
                          D3D8_TABLE(texture_address_name_array) );

            break;
        }

        case D3D8::D3DTSS_MAGFILTER:
        case D3D8::D3DTSS_MINFILTER:
        case D3D8::D3DTSS_MIPFILTER:
        {
            set_info_func(StateValueFormat::Name,
                          D3D8_TABLE(texture_filter_name_array) );

            break;
        }

        case D3D8::D3DTSS_TEXCOORDINDEX:
        {
            set_info_func(StateValueFormat::TexCoordIndex,
                          nullptr,
                          0);

            break;
        }

        case D3D8::D3DTSS_TEXTURETRANSFORMFLAGS:
        {
            set_info_func(StateValueFormat::TextureTransformFlags,
                          nullptr,
                          0);

            break;
        }

        case D3D8::D3DTSS_BORDERCOLOR:
        {
            set_info_func(StateValueFormat::Color,
                          nullptr,
                          0);

            break;
        }

        case D3D8::D3DTSS_BUMPENVLOFFSET:
        case D3D8::D3DTSS_BUMPENVLSCALE:
        case D3D8::D3DTSS_BUMPENVMAT00:
        case D3D8::D3DTSS_BUMPENVMAT01:
        case D3D8::D3DTSS_BUMPENVMAT10:
        case D3D8::D3DTSS_BUMPENVMAT11:
        case D3D8::D3DTSS_MIPMAPLODBIAS:
        {
            set_info_func(StateValueFormat::Float,
                          nullptr,
                          0);

            break;
        }

        default:
        {
            set_info_func(StateValueFormat::Raw,
                          nullptr,
                          0);

            result = false;

            break;
        }
    }

    return result;
}

bool APIDumpPrinter::get_value_name_table(const D3D8::ValueKind& in_kind,
                                          const ValueNameEntry** out_table_ptr_ptr,
                                          uint32_t*              out_n_entries_ptr)
{
    static const ValueNameEntry back_buffer_type_name_array[] =
    {
        D3D8_VALUE_NAME(D3DBACKBUFFER_TYPE_MONO),
        D3D8_VALUE_NAME(D3DBACKBUFFER_TYPE_LEFT),
        D3D8_VALUE_NAME(D3DBACKBUFFER_TYPE_RIGHT),
    };

    static const ValueNameEntry cube_map_face_name_array[] =
    {
        D3D8_VALUE_NAME(D3DCUBEMAP_FACE_POSITIVE_X),
        D3D8_VALUE_NAME(D3DCUBEMAP_FACE_NEGATIVE_X),
        D3D8_VALUE_NAME(D3DCUBEMAP_FACE_POSITIVE_Y),
        D3D8_VALUE_NAME(D3DCUBEMAP_FACE_NEGATIVE_Y),
        D3D8_VALUE_NAME(D3DCUBEMAP_FACE_POSITIVE_Z),
        D3D8_VALUE_NAME(D3DCUBEMAP_FACE_NEGATIVE_Z),
    };

    static const ValueNameEntry device_type_name_array[] =
    {
        D3D8_VALUE_NAME(D3DDEVTYPE_HAL),
        D3D8_VALUE_NAME(D3DDEVTYPE_REF),
        D3D8_VALUE_NAME(D3DDEVTYPE_SW),
    };

    static const ValueNameEntry format_name_array[] =
    {
        D3D8_VALUE_NAME(D3DFMT_UNKNOWN),
        D3D8_VALUE_NAME(D3DFMT_R8G8B8),
        D3D8_VALUE_NAME(D3DFMT_A8R8G8B8),
        D3D8_VALUE_NAME(D3DFMT_X8R8G8B8),
        D3D8_VALUE_NAME(D3DFMT_R5G6B5),
        D3D8_VALUE_NAME(D3DFMT_X1R5G5B5),
        D3D8_VALUE_NAME(D3DFMT_A1R5G5B5),
        D3D8_VALUE_NAME(D3DFMT_A4R4G4B4),
        D3D8_VALUE_NAME(D3DFMT_R3G3B2),
        D3D8_VALUE_NAME(D3DFMT_A8),
        D3D8_VALUE_NAME(D3DFMT_A8R3G3B2),
        D3D8_VALUE_NAME(D3DFMT_X4R4G4B4),
        D3D8_VALUE_NAME(D3DFMT_A2B10G10R10),
        D3D8_VALUE_NAME(D3DFMT_G16R16),
        D3D8_VALUE_NAME(D3DFMT_A8P8),
        D3D8_VALUE_NAME(D3DFMT_P8),
        D3D8_VALUE_NAME(D3DFMT_L8),
        D3D8_VALUE_NAME(D3DFMT_A8L8),
        D3D8_VALUE_NAME(D3DFMT_A4L4),
        D3D8_VALUE_NAME(D3DFMT_V8U8),
        D3D8_VALUE_NAME(D3DFMT_L6V5U5),
        D3D8_VALUE_NAME(D3DFMT_X8L8V8U8),
        D3D8_VALUE_NAME(D3DFMT_Q8W8V8U8),
        D3D8_VALUE_NAME(D3DFMT_V16U16),
        D3D8_VALUE_NAME(D3DFMT_W11V11U10),
        D3D8_VALUE_NAME(D3DFMT_A2W10V10U10),
        D3D8_VALUE_NAME(D3DFMT_UYVY),
        D3D8_VALUE_NAME(D3DFMT_YUY2),
        D3D8_VALUE_NAME(D3DFMT_DXT1),
        D3D8_VALUE_NAME(D3DFMT_DXT2),
        D3D8_VALUE_NAME(D3DFMT_DXT3),
        D3D8_VALUE_NAME(D3DFMT_DXT4),
        D3D8_VALUE_NAME(D3DFMT_DXT5),
        D3D8_VALUE_NAME(D3DFMT_D16_LOCKABLE),
        D3D8_VALUE_NAME(D3DFMT_D32),
        D3D8_VALUE_NAME(D3DFMT_D15S1),
        D3D8_VALUE_NAME(D3DFMT_D24S8),
        D3D8_VALUE_NAME(D3DFMT_D16),
        D3D8_VALUE_NAME(D3DFMT_D24X8),
        D3D8_VALUE_NAME(D3DFMT_D24X4S4),
        D3D8_VALUE_NAME(D3DFMT_VERTEXDATA),
        D3D8_VALUE_NAME(D3DFMT_INDEX16),
        D3D8_VALUE_NAME(D3DFMT_INDEX32),
    };

    static const ValueNameEntry light_type_name_array[] =
    {
        D3D8_VALUE_NAME(D3DLIGHT_POINT),
        D3D8_VALUE_NAME(D3DLIGHT_SPOT),
        D3D8_VALUE_NAME(D3DLIGHT_DIRECTIONAL),
    };

    static const ValueNameEntry multisample_type_name_array[] =
    {
        D3D8_VALUE_NAME(D3DMULTISAMPLE_NONE),
        D3D8_VALUE_NAME(D3DMULTISAMPLE_2_SAMPLES),
        D3D8_VALUE_NAME(D3DMULTISAMPLE_3_SAMPLES),
        D3D8_VALUE_NAME(D3DMULTISAMPLE_4_SAMPLES),
        D3D8_VALUE_NAME(D3DMULTISAMPLE_5_SAMPLES),
        D3D8_VALUE_NAME(D3DMULTISAMPLE_6_SAMPLES),
        D3D8_VALUE_NAME(D3DMULTISAMPLE_7_SAMPLES),
        D3D8_VALUE_NAME(D3DMULTISAMPLE_8_SAMPLES),
        D3D8_VALUE_NAME(D3DMULTISAMPLE_9_SAMPLES),
        D3D8_VALUE_NAME(D3DMULTISAMPLE_10_SAMPLES),
        D3D8_VALUE_NAME(D3DMULTISAMPLE_11_SAMPLES),
        D3D8_VALUE_NAME(D3DMULTISAMPLE_12_SAMPLES),
        D3D8_VALUE_NAME(D3DMULTISAMPLE_13_SAMPLES),
        D3D8_VALUE_NAME(D3DMULTISAMPLE_14_SAMPLES),
        D3D8_VALUE_NAME(D3DMULTISAMPLE_15_SAMPLES),
        D3D8_VALUE_NAME(D3DMULTISAMPLE_16_SAMPLES),
    };

    static const ValueNameEntry pool_name_array[] =
    {
        D3D8_VALUE_NAME(D3DPOOL_DEFAULT),
        D3D8_VALUE_NAME(D3DPOOL_MANAGED),
        D3D8_VALUE_NAME(D3DPOOL_SYSTEMMEM),
        D3D8_VALUE_NAME(D3DPOOL_SCRATCH),
    };

    static const ValueNameEntry primitive_type_name_array[] =
    {
        D3D8_VALUE_NAME(D3DPT_POINTLIST),
        D3D8_VALUE_NAME(D3DPT_LINELIST),
        D3D8_VALUE_NAME(D3DPT_LINESTRIP),
        D3D8_VALUE_NAME(D3DPT_TRIANGLELIST),
        D3D8_VALUE_NAME(D3DPT_TRIANGLESTRIP),
        D3D8_VALUE_NAME(D3DPT_TRIANGLEFAN),
    };

    static const ValueNameEntry render_state_type_name_array[] =
    {
        D3D8_VALUE_NAME(D3DRS_ZENABLE),
        D3D8_VALUE_NAME(D3DRS_FILLMODE),
        D3D8_VALUE_NAME(D3DRS_SHADEMODE),
        D3D8_VALUE_NAME(D3DRS_LINEPATTERN),
        D3D8_VALUE_NAME(D3DRS_ZWRITEENABLE),
        D3D8_VALUE_NAME(D3DRS_ALPHATESTENABLE),
        D3D8_VALUE_NAME(D3DRS_LASTPIXEL),
        D3D8_VALUE_NAME(D3DRS_SRCBLEND),
        D3D8_VALUE_NAME(D3DRS_DESTBLEND),
        D3D8_VALUE_NAME(D3DRS_CULLMODE),
        D3D8_VALUE_NAME(D3DRS_ZFUNC),
        D3D8_VALUE_NAME(D3DRS_ALPHAREF),
        D3D8_VALUE_NAME(D3DRS_ALPHAFUNC),
        D3D8_VALUE_NAME(D3DRS_DITHERENABLE),
        D3D8_VALUE_NAME(D3DRS_ALPHABLENDENABLE),
        D3D8_VALUE_NAME(D3DRS_FOGENABLE),
        D3D8_VALUE_NAME(D3DRS_SPECULARENABLE),
        D3D8_VALUE_NAME(D3DRS_ZVISIBLE),
        D3D8_VALUE_NAME(D3DRS_FOGCOLOR),
        D3D8_VALUE_NAME(D3DRS_FOGTABLEMODE),
        D3D8_VALUE_NAME(D3DRS_FOGSTART),
        D3D8_VALUE_NAME(D3DRS_FOGEND),
        D3D8_VALUE_NAME(D3DRS_FOGDENSITY),
        D3D8_VALUE_NAME(D3DRS_EDGEANTIALIAS),
        D3D8_VALUE_NAME(D3DRS_ZBIAS),
        D3D8_VALUE_NAME(D3DRS_RANGEFOGENABLE),
        D3D8_VALUE_NAME(D3DRS_STENCILENABLE),
        D3D8_VALUE_NAME(D3DRS_STENCILFAIL),
        D3D8_VALUE_NAME(D3DRS_STENCILZFAIL),
        D3D8_VALUE_NAME(D3DRS_STENCILPASS),
        D3D8_VALUE_NAME(D3DRS_STENCILFUNC),
        D3D8_VALUE_NAME(D3DRS_STENCILREF),
        D3D8_VALUE_NAME(D3DRS_STENCILMASK),
        D3D8_VALUE_NAME(D3DRS_STENCILWRITEMASK),
        D3D8_VALUE_NAME(D3DRS_TEXTUREFACTOR),
        D3D8_VALUE_NAME(D3DRS_WRAP0),
        D3D8_VALUE_NAME(D3DRS_WRAP1),
        D3D8_VALUE_NAME(D3DRS_WRAP2),
        D3D8_VALUE_NAME(D3DRS_WRAP3),
        D3D8_VALUE_NAME(D3DRS_WRAP4),
        D3D8_VALUE_NAME(D3DRS_WRAP5),
        D3D8_VALUE_NAME(D3DRS_WRAP6),
        D3D8_VALUE_NAME(D3DRS_WRAP7),
        D3D8_VALUE_NAME(D3DRS_CLIPPING),
        D3D8_VALUE_NAME(D3DRS_LIGHTING),
        D3D8_VALUE_NAME(D3DRS_AMBIENT),
        D3D8_VALUE_NAME(D3DRS_FOGVERTEXMODE),
        D3D8_VALUE_NAME(D3DRS_COLORVERTEX),
        D3D8_VALUE_NAME(D3DRS_LOCALVIEWER),
        D3D8_VALUE_NAME(D3DRS_NORMALIZENORMALS),
        D3D8_VALUE_NAME(D3DRS_DIFFUSEMATERIALSOURCE),
        D3D8_VALUE_NAME(D3DRS_SPECULARMATERIALSOURCE),
        D3D8_VALUE_NAME(D3DRS_AMBIENTMATERIALSOURCE),
        D3D8_VALUE_NAME(D3DRS_EMISSIVEMATERIALSOURCE),
        D3D8_VALUE_NAME(D3DRS_VERTEXBLEND),
        D3D8_VALUE_NAME(D3DRS_CLIPPLANEENABLE),
        D3D8_VALUE_NAME(D3DRS_SOFTWAREVERTEXPROCESSING),
        D3D8_VALUE_NAME(D3DRS_POINTSIZE),
        D3D8_VALUE_NAME(D3DRS_POINTSIZE_MIN),
        D3D8_VALUE_NAME(D3DRS_POINTSPRITEENABLE),
        D3D8_VALUE_NAME(D3DRS_POINTSCALEENABLE),
        D3D8_VALUE_NAME(D3DRS_POINTSCALE_A),
        D3D8_VALUE_NAME(D3DRS_POINTSCALE_B),
        D3D8_VALUE_NAME(D3DRS_POINTSCALE_C),
        D3D8_VALUE_NAME(D3DRS_MULTISAMPLEANTIALIAS),
        D3D8_VALUE_NAME(D3DRS_MULTISAMPLEMASK),
        D3D8_VALUE_NAME(D3DRS_PATCHEDGESTYLE),
        D3D8_VALUE_NAME(D3DRS_PATCHSEGMENTS),
        D3D8_VALUE_NAME(D3DRS_DEBUGMONITORTOKEN),
        D3D8_VALUE_NAME(D3DRS_POINTSIZE_MAX),
        D3D8_VALUE_NAME(D3DRS_INDEXEDVERTEXBLENDENABLE),
        D3D8_VALUE_NAME(D3DRS_COLORWRITEENABLE),
        D3D8_VALUE_NAME(D3DRS_TWEENFACTOR),
        D3D8_VALUE_NAME(D3DRS_BLENDOP),
        D3D8_VALUE_NAME(D3DRS_POSITIONORDER),
        D3D8_VALUE_NAME(D3DRS_NORMALORDER),
    };

    static const ValueNameEntry resource_type_name_array[] =
    {
        D3D8_VALUE_NAME(D3DRTYPE_SURFACE),
        D3D8_VALUE_NAME(D3DRTYPE_VOLUME),
        D3D8_VALUE_NAME(D3DRTYPE_TEXTURE),
        D3D8_VALUE_NAME(D3DRTYPE_VOLUMETEXTURE),
        D3D8_VALUE_NAME(D3DRTYPE_CUBETEXTURE),
        D3D8_VALUE_NAME(D3DRTYPE_VERTEXBUFFER),
        D3D8_VALUE_NAME(D3DRTYPE_INDEXBUFFER),
    };

    static const ValueNameEntry state_block_type_name_array[] =
    {
        D3D8_VALUE_NAME(D3DSBT_ALL),
        D3D8_VALUE_NAME(D3DSBT_PIXELSTATE),
        D3D8_VALUE_NAME(D3DSBT_VERTEXSTATE),
    };

    static const ValueNameEntry swap_effect_name_array[] =
    {
        D3D8_VALUE_NAME(D3DSWAPEFFECT_DISCARD),
        D3D8_VALUE_NAME(D3DSWAPEFFECT_FLIP),
        D3D8_VALUE_NAME(D3DSWAPEFFECT_COPY),
        D3D8_VALUE_NAME(D3DSWAPEFFECT_COPY_VSYNC),
    };

    static const ValueNameEntry texture_stage_state_type_name_array[] =
    {
        D3D8_VALUE_NAME(D3DTSS_COLOROP),
        D3D8_VALUE_NAME(D3DTSS_COLORARG1),
        D3D8_VALUE_NAME(D3DTSS_COLORARG2),
        D3D8_VALUE_NAME(D3DTSS_ALPHAOP),
        D3D8_VALUE_NAME(D3DTSS_ALPHAARG1),
        D3D8_VALUE_NAME(D3DTSS_ALPHAARG2),
        D3D8_VALUE_NAME(D3DTSS_BUMPENVMAT00),
        D3D8_VALUE_NAME(D3DTSS_BUMPENVMAT01),
        D3D8_VALUE_NAME(D3DTSS_BUMPENVMAT10),
        D3D8_VALUE_NAME(D3DTSS_BUMPENVMAT11),
        D3D8_VALUE_NAME(D3DTSS_TEXCOORDINDEX),
        D3D8_VALUE_NAME(D3DTSS_ADDRESSU),
        D3D8_VALUE_NAME(D3DTSS_ADDRESSV),
        D3D8_VALUE_NAME(D3DTSS_BORDERCOLOR),
        D3D8_VALUE_NAME(D3DTSS_MAGFILTER),
        D3D8_VALUE_NAME(D3DTSS_MINFILTER),
        D3D8_VALUE_NAME(D3DTSS_MIPFILTER),
        D3D8_VALUE_NAME(D3DTSS_MIPMAPLODBIAS),
        D3D8_VALUE_NAME(D3DTSS_MAXMIPLEVEL),
        D3D8_VALUE_NAME(D3DTSS_MAXANISOTROPY),
        D3D8_VALUE_NAME(D3DTSS_BUMPENVLSCALE),
        D3D8_VALUE_NAME(D3DTSS_BUMPENVLOFFSET),
        D3D8_VALUE_NAME(D3DTSS_TEXTURETRANSFORMFLAGS),
        D3D8_VALUE_NAME(D3DTSS_ADDRESSW),
        D3D8_VALUE_NAME(D3DTSS_COLORARG0),
        D3D8_VALUE_NAME(D3DTSS_ALPHAARG0),
        D3D8_VALUE_NAME(D3DTSS_RESULTARG),
    };

    static const ValueNameEntry transform_state_type_name_array[] =
    {
        D3D8_VALUE_NAME(D3DTS_VIEW),
        D3D8_VALUE_NAME(D3DTS_PROJECTION),
        D3D8_VALUE_NAME(D3DTS_TEXTURE0),
        D3D8_VALUE_NAME(D3DTS_TEXTURE1),
        D3D8_VALUE_NAME(D3DTS_TEXTURE2),
        D3D8_VALUE_NAME(D3DTS_TEXTURE3),
        D3D8_VALUE_NAME(D3DTS_TEXTURE4),
        D3D8_VALUE_NAME(D3DTS_TEXTURE5),
        D3D8_VALUE_NAME(D3DTS_TEXTURE6),
        D3D8_VALUE_NAME(D3DTS_TEXTURE7),
        D3D8_VALUE_NAME(D3DTS_WORLD),
        D3D8_VALUE_NAME(D3DTS_WORLD1),
        D3D8_VALUE_NAME(D3DTS_WORLD2),
        D3D8_VALUE_NAME(D3DTS_WORLD3),
    };

    const auto set_table_func = [&](const ValueNameEntry* in_table_ptr,
                                    const uint32_t&       in_n_entries)
    {
        *out_table_ptr_ptr = in_table_ptr;
        *out_n_entries_ptr = in_n_entries;
    };

    bool result = true;

    switch (in_kind)
    {
        case D3D8::ValueKind::BackBufferType:
        {
            set_table_func(D3D8_TABLE(back_buffer_type_name_array) );

            break;
        }

        case D3D8::ValueKind::CubeMapFace:
        {
            set_table_func(D3D8_TABLE(cube_map_face_name_array) );

            break;
        }

        case D3D8::ValueKind::DeviceType:
        {
            set_table_func(D3D8_TABLE(device_type_name_array) );

            break;
        }

        case D3D8::ValueKind::Format:
        {
            set_table_func(D3D8_TABLE(format_name_array) );

            break;
        }

        case D3D8::ValueKind::LightType:
        {
            set_table_func(D3D8_TABLE(light_type_name_array) );

            break;
        }

        case D3D8::ValueKind::MultiSampleType:
        {
            set_table_func(D3D8_TABLE(multisample_type_name_array) );

            break;
        }

        case D3D8::ValueKind::Pool:
        {
            set_table_func(D3D8_TABLE(pool_name_array) );

            break;
        }

        case D3D8::ValueKind::PrimitiveType:
        {
            set_table_func(D3D8_TABLE(primitive_type_name_array) );

            break;
        }

        case D3D8::ValueKind::RenderStateType:
        {
            set_table_func(D3D8_TABLE(render_state_type_name_array) );

            break;
        }

        case D3D8::ValueKind::ResourceType:
        {
            set_table_func(D3D8_TABLE(resource_type_name_array) );

            break;
        }

        case D3D8::ValueKind::StateBlockType:
        {
            set_table_func(D3D8_TABLE(state_block_type_name_array) );

            break;
        }

        case D3D8::ValueKind::SwapEffect:
        {
            set_table_func(D3D8_TABLE(swap_effect_name_array) );

            break;
        }

        case D3D8::ValueKind::TextureStageStateType:
        {
            set_table_func(D3D8_TABLE(texture_stage_state_type_name_array) );

            break;
        }

        case D3D8::ValueKind::TransformStateType:
        {
            set_table_func(D3D8_TABLE(transform_state_type_name_array) );

            break;
        }

        default:
        {
            result = false;

            break;
        }
    }

    return result;
}
