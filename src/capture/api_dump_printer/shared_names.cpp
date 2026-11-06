/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "common/macros.h"
#include "shared_names.h"

#define SHARED_TABLE(array) {array, static_cast<uint32_t>(sizeof(array) / sizeof(array[0]) )}

Capture::APIDumpPrinter::NameTable Capture::APIDumpPrinter::get_shared_name_table(const SharedNameTable& in_table)
{
    static const ValueNameEntry blend_name_array[] =
    {
        {"D3DBLEND_ZERO",            1},
        {"D3DBLEND_ONE",             2},
        {"D3DBLEND_SRCCOLOR",        3},
        {"D3DBLEND_INVSRCCOLOR",     4},
        {"D3DBLEND_SRCALPHA",        5},
        {"D3DBLEND_INVSRCALPHA",     6},
        {"D3DBLEND_DESTALPHA",       7},
        {"D3DBLEND_INVDESTALPHA",    8},
        {"D3DBLEND_DESTCOLOR",       9},
        {"D3DBLEND_INVDESTCOLOR",    10},
        {"D3DBLEND_SRCALPHASAT",     11},
        {"D3DBLEND_BOTHSRCALPHA",    12},
        {"D3DBLEND_BOTHINVSRCALPHA", 13},
    };

    static const ValueNameEntry cmp_func_name_array[] =
    {
        {"D3DCMP_NEVER",        1},
        {"D3DCMP_LESS",         2},
        {"D3DCMP_EQUAL",        3},
        {"D3DCMP_LESSEQUAL",    4},
        {"D3DCMP_GREATER",      5},
        {"D3DCMP_NOTEQUAL",     6},
        {"D3DCMP_GREATEREQUAL", 7},
        {"D3DCMP_ALWAYS",       8},
    };

    static const ValueNameEntry cull_name_array[] =
    {
        {"D3DCULL_NONE", 1},
        {"D3DCULL_CW",   2},
        {"D3DCULL_CCW",  3},
    };

    static const ValueNameEntry fill_mode_name_array[] =
    {
        {"D3DFILL_POINT",     1},
        {"D3DFILL_WIREFRAME", 2},
        {"D3DFILL_SOLID",     3},
    };

    static const ValueNameEntry fog_mode_name_array[] =
    {
        {"D3DFOG_NONE",   0},
        {"D3DFOG_EXP",    1},
        {"D3DFOG_EXP2",   2},
        {"D3DFOG_LINEAR", 3},
    };

    static const ValueNameEntry material_color_source_name_array[] =
    {
        {"D3DMCS_MATERIAL", 0},
        {"D3DMCS_COLOR1",   1},
        {"D3DMCS_COLOR2",   2},
    };

    static const ValueNameEntry primitive_type_name_array[] =
    {
        {"D3DPT_POINTLIST",     1},
        {"D3DPT_LINELIST",      2},
        {"D3DPT_LINESTRIP",     3},
        {"D3DPT_TRIANGLELIST",  4},
        {"D3DPT_TRIANGLESTRIP", 5},
        {"D3DPT_TRIANGLEFAN",   6},
    };

    static const ValueNameEntry shade_mode_name_array[] =
    {
        {"D3DSHADE_FLAT",    1},
        {"D3DSHADE_GOURAUD", 2},
        {"D3DSHADE_PHONG",   3},
    };

    static const ValueNameEntry state_block_type_name_array[] =
    {
        {"D3DSBT_ALL",         1},
        {"D3DSBT_PIXELSTATE",  2},
        {"D3DSBT_VERTEXSTATE", 3},
    };

    static const ValueNameEntry stencil_op_name_array[] =
    {
        {"D3DSTENCILOP_KEEP",    1},
        {"D3DSTENCILOP_ZERO",    2},
        {"D3DSTENCILOP_REPLACE", 3},
        {"D3DSTENCILOP_INCRSAT", 4},
        {"D3DSTENCILOP_DECRSAT", 5},
        {"D3DSTENCILOP_INVERT",  6},
        {"D3DSTENCILOP_INCR",    7},
        {"D3DSTENCILOP_DECR",    8},
    };

    static const ValueNameEntry texture_address_name_array[] =
    {
        {"D3DTADDRESS_WRAP",       1},
        {"D3DTADDRESS_MIRROR",     2},
        {"D3DTADDRESS_CLAMP",      3},
        {"D3DTADDRESS_BORDER",     4},
        {"D3DTADDRESS_MIRRORONCE", 5},
    };

    static const ValueNameEntry texture_argument_name_array[] =
    {
        {"D3DTA_DIFFUSE",  0},
        {"D3DTA_CURRENT",  1},
        {"D3DTA_TEXTURE",  2},
        {"D3DTA_TFACTOR",  3},
        {"D3DTA_SPECULAR", 4},
        {"D3DTA_TEMP",     5},
    };

    static const ValueNameEntry texture_op_name_array[] =
    {
        {"D3DTOP_DISABLE",                   1},
        {"D3DTOP_SELECTARG1",                2},
        {"D3DTOP_SELECTARG2",                3},
        {"D3DTOP_MODULATE",                  4},
        {"D3DTOP_MODULATE2X",                5},
        {"D3DTOP_MODULATE4X",                6},
        {"D3DTOP_ADD",                       7},
        {"D3DTOP_ADDSIGNED",                 8},
        {"D3DTOP_ADDSIGNED2X",               9},
        {"D3DTOP_SUBTRACT",                  10},
        {"D3DTOP_ADDSMOOTH",                 11},
        {"D3DTOP_BLENDDIFFUSEALPHA",         12},
        {"D3DTOP_BLENDTEXTUREALPHA",         13},
        {"D3DTOP_BLENDFACTORALPHA",          14},
        {"D3DTOP_BLENDTEXTUREALPHAPM",       15},
        {"D3DTOP_BLENDCURRENTALPHA",         16},
        {"D3DTOP_PREMODULATE",               17},
        {"D3DTOP_MODULATEALPHA_ADDCOLOR",    18},
        {"D3DTOP_MODULATECOLOR_ADDALPHA",    19},
        {"D3DTOP_MODULATEINVALPHA_ADDCOLOR", 20},
        {"D3DTOP_MODULATEINVCOLOR_ADDALPHA", 21},
        {"D3DTOP_BUMPENVMAP",                22},
        {"D3DTOP_BUMPENVMAPLUMINANCE",       23},
        {"D3DTOP_DOTPRODUCT3",               24},
        {"D3DTOP_MULTIPLYADD",               25},
        {"D3DTOP_LERP",                      26},
    };

    static const ValueNameEntry z_buffer_type_name_array[] =
    {
        {"D3DZB_FALSE", 0},
        {"D3DZB_TRUE",  1},
        {"D3DZB_USEW",  2},
    };

    /* In the order of the enum. */
    const NameTable name_table_array[] =
    {
        SHARED_TABLE(blend_name_array),
        SHARED_TABLE(cmp_func_name_array),
        SHARED_TABLE(cull_name_array),
        SHARED_TABLE(fill_mode_name_array),
        SHARED_TABLE(fog_mode_name_array),
        SHARED_TABLE(material_color_source_name_array),
        SHARED_TABLE(primitive_type_name_array),
        SHARED_TABLE(shade_mode_name_array),
        SHARED_TABLE(state_block_type_name_array),
        SHARED_TABLE(stencil_op_name_array),
        SHARED_TABLE(texture_address_name_array),
        SHARED_TABLE(texture_argument_name_array),
        SHARED_TABLE(texture_op_name_array),
        SHARED_TABLE(z_buffer_type_name_array)
    };

    if (static_cast<size_t>(in_table) >= sizeof(name_table_array) / sizeof(name_table_array[0]) )
    {
        AI_FAIL_UNSUPPORTED(in_table);
    }

    return name_table_array[static_cast<size_t>(in_table)];
}
