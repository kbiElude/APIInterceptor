/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/globals.h"
#include "OpenGL/utils.h"
#include <cassert>

/* For GL 1.1 compatibility profile support */
#include "GL/gl.h"

uint32_t OpenGL::Utils::get_n_bytes_for_type(const GLenum& in_type)
{
    uint32_t result = 0;

    switch (in_type)
    {
        case GL_BYTE:                        result = static_cast<uint32_t>(sizeof(int8_t)  );  break;
        case GL_FLOAT:                       result = static_cast<uint32_t>(sizeof(float)   );  break;
        case GL_INT:                         result = static_cast<uint32_t>(sizeof(int32_t) );  break;
        case GL_SHORT:                       result = static_cast<uint32_t>(sizeof(int16_t) );  break;
        case GL_UNSIGNED_BYTE:               result = static_cast<uint32_t>(sizeof(uint8_t) );  break;
        case GL_UNSIGNED_BYTE_2_3_3_REV:     result = 1;                                        break;
        case GL_UNSIGNED_BYTE_3_3_2:         result = 1;                                        break;
        case GL_UNSIGNED_INT:                result = static_cast<uint32_t>(sizeof(uint32_t) ); break;
        case GL_UNSIGNED_INT_2_10_10_10_REV: result = 4;                                        break;
        case GL_UNSIGNED_INT_8_8_8_8:        result = 4;                                        break;
        case GL_UNSIGNED_INT_8_8_8_8_REV:    result = 4;                                        break;
        case GL_UNSIGNED_INT_10_10_10_2:     result = 4;                                        break;
        case GL_UNSIGNED_SHORT:              result = static_cast<uint32_t>(sizeof(uint16_t) ); break;
        case GL_UNSIGNED_SHORT_1_5_5_5_REV:  result = 2;                                        break;
        case GL_UNSIGNED_SHORT_4_4_4_4:      result = 2;                                        break;
        case GL_UNSIGNED_SHORT_4_4_4_4_REV:  result = 2;                                        break;
        case GL_UNSIGNED_SHORT_5_5_5_1:      result = 2;                                        break;
        case GL_UNSIGNED_SHORT_5_6_5:        result = 2;                                        break;
        case GL_UNSIGNED_SHORT_5_6_5_REV:    result = 2;                                        break;

        default:
        {
            assert(false);
        }
    }

    assert(result != 0);
    return result;
}

uint32_t OpenGL::Utils::get_n_components_for_format(const GLenum& in_format)
{
    uint32_t result = 0;

    switch (in_format)
    {
        case GL_BGR:             result = 3; break;
        case GL_BGRA:            result = 4; break;
        case GL_DEPTH_COMPONENT: result = 1; break;
        case GL_LUMINANCE:       result = 1; break;
        case GL_LUMINANCE_ALPHA: result = 2; break;
        case GL_RED:             result = 1; break;
        case GL_RG:              result = 2; break;
        case GL_RGB:             result = 3; break;
        case GL_RGBA:            result = 4; break;
        case GL_STENCIL_INDEX:   result = 1; break;

        default:
        {
            assert(false);
        }
    }

    assert(result != 0);
    return result;
}

uint32_t OpenGL::Utils::get_n_texture_data_bytes(const uint32_t& in_width,
                                                 const uint32_t& in_height,
                                                 const uint32_t& in_depth,
                                                 const GLenum&   in_format,
                                                 const GLenum&   in_type)
{
    const auto n_bytes_per_component = get_n_bytes_for_type       (in_type);
    const auto n_components          = get_n_components_for_format(in_format);
    const auto n_texels              = in_width * in_height * in_depth;

    const auto     n_bytes_per_texel = n_components * n_bytes_per_component;
    const uint32_t result            = n_texels     * n_bytes_per_texel;

    assert(result != 0);
    return result;
}