/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/globals.h"
#include "OpenGL/utils.h"
#include <cassert>

/* gl/gl.h provides compatibility-profile tokens (GL_LUMINANCE, GL_LUMINANCE_ALPHA, etc.)
 * that are absent from glcorearb.h but valid as pixel transfer formats. */
#include "gl/gl.h"

bool OpenGL::Utils::get_texture_binding_target_for_gl_enum(const GLenum&         in_target,
                                                           TextureBindingTarget* out_result_ptr)
{
    bool result = true;

    switch (in_target)
    {
        case GL_TEXTURE_1D:         *out_result_ptr = TextureBindingTarget::TEXTURE_1D;         break;
        case GL_TEXTURE_1D_ARRAY:   *out_result_ptr = TextureBindingTarget::TEXTURE_1D_ARRAY;   break;
        case GL_TEXTURE_2D:         *out_result_ptr = TextureBindingTarget::TEXTURE_2D;         break;
        case GL_TEXTURE_2D_ARRAY:   *out_result_ptr = TextureBindingTarget::TEXTURE_2D_ARRAY;   break;
        case GL_TEXTURE_3D:         *out_result_ptr = TextureBindingTarget::TEXTURE_3D;         break;
        case GL_TEXTURE_BUFFER:     *out_result_ptr = TextureBindingTarget::TEXTURE_BUFFER;     break;

        case GL_TEXTURE_CUBE_MAP:
        case GL_TEXTURE_CUBE_MAP_POSITIVE_X:
        case GL_TEXTURE_CUBE_MAP_NEGATIVE_X:
        case GL_TEXTURE_CUBE_MAP_POSITIVE_Y:
        case GL_TEXTURE_CUBE_MAP_NEGATIVE_Y:
        case GL_TEXTURE_CUBE_MAP_POSITIVE_Z:
        case GL_TEXTURE_CUBE_MAP_NEGATIVE_Z:
        {
            *out_result_ptr = TextureBindingTarget::TEXTURE_CUBE_MAP;

            break;
        }

        case GL_TEXTURE_RECTANGLE:
        {
            *out_result_ptr = TextureBindingTarget::TEXTURE_RECTANGLE;

            break;
        }

        default:
        {
            assert(false);

            result = false;
        }
    }

    return result;
}

bool OpenGL::Utils::get_buffer_binding_target_for_gl_enum(const GLenum&        in_target,
                                                          BufferBindingTarget* out_result_ptr)
{
    bool result = true;

    switch (in_target)
    {
        case GL_ARRAY_BUFFER:              *out_result_ptr = BufferBindingTarget::ARRAY_BUFFER;               break;
        case GL_ATOMIC_COUNTER_BUFFER:     *out_result_ptr = BufferBindingTarget::ATOMIC_COUNTER_BUFFER;      break;
        case GL_COPY_READ_BUFFER:          *out_result_ptr = BufferBindingTarget::COPY_READ_BUFFER;           break;
        case GL_COPY_WRITE_BUFFER:         *out_result_ptr = BufferBindingTarget::COPY_WRITE_BUFFER;          break;
        case GL_DISPATCH_INDIRECT_BUFFER:  *out_result_ptr = BufferBindingTarget::DISPATCH_INDIRECT_BUFFER;   break;
        case GL_DRAW_INDIRECT_BUFFER:      *out_result_ptr = BufferBindingTarget::DRAW_INDIRECT_BUFFER;       break;
        case GL_ELEMENT_ARRAY_BUFFER:      *out_result_ptr = BufferBindingTarget::ELEMENT_ARRAY_BUFFER;       break;
        case GL_PIXEL_PACK_BUFFER:         *out_result_ptr = BufferBindingTarget::PIXEL_PACK_BUFFER;          break;
        case GL_PIXEL_UNPACK_BUFFER:       *out_result_ptr = BufferBindingTarget::PIXEL_UNPACK_BUFFER;        break;
        case GL_QUERY_BUFFER:              *out_result_ptr = BufferBindingTarget::QUERY_BUFFER;               break;
        case GL_SHADER_STORAGE_BUFFER:     *out_result_ptr = BufferBindingTarget::SHADER_STORAGE_BUFFER;      break;
        case GL_TEXTURE_BUFFER:            *out_result_ptr = BufferBindingTarget::TEXTURE_BUFFER;             break;
        case GL_TRANSFORM_FEEDBACK_BUFFER: *out_result_ptr = BufferBindingTarget::TRANSFORM_FEEDBACK_BUFFER;  break;
        case GL_UNIFORM_BUFFER:            *out_result_ptr = BufferBindingTarget::UNIFORM_BUFFER;             break;

        default:
        {
            assert(false);

            result = false;
        }
    }

    return result;
}

bool OpenGL::Utils::is_packed_pixel_type(const GLenum& in_type)
{
    switch (in_type)
    {
        case GL_UNSIGNED_BYTE_3_3_2:
        case GL_UNSIGNED_BYTE_2_3_3_REV:
        case GL_UNSIGNED_SHORT_5_6_5:
        case GL_UNSIGNED_SHORT_5_6_5_REV:
        case GL_UNSIGNED_SHORT_4_4_4_4:
        case GL_UNSIGNED_SHORT_4_4_4_4_REV:
        case GL_UNSIGNED_SHORT_5_5_5_1:
        case GL_UNSIGNED_SHORT_1_5_5_5_REV:
        case GL_UNSIGNED_INT_8_8_8_8:
        case GL_UNSIGNED_INT_8_8_8_8_REV:
        case GL_UNSIGNED_INT_10_10_10_2:
        case GL_UNSIGNED_INT_2_10_10_10_REV:
        case GL_UNSIGNED_INT_24_8:
        case GL_UNSIGNED_INT_5_9_9_9_REV:
        case GL_UNSIGNED_INT_10F_11F_11F_REV:
        case GL_FLOAT_32_UNSIGNED_INT_24_8_REV:
        {
            return true;
        }

        default:
        {
            return false;
        }
    }
}

uint32_t OpenGL::Utils::get_n_bytes_for_type(const GLenum& in_type)
{
    uint32_t result = 0;

    switch (in_type)
    {
        case GL_BYTE:                              result = static_cast<uint32_t>(sizeof(int8_t)  );  break;
        case GL_FLOAT:                             result = static_cast<uint32_t>(sizeof(float)   );  break;
        case GL_HALF_FLOAT:                        result = 2;                                        break;
        case GL_INT:                               result = static_cast<uint32_t>(sizeof(int32_t) );  break;
        case GL_SHORT:                             result = static_cast<uint32_t>(sizeof(int16_t) );  break;
        case GL_UNSIGNED_BYTE:                     result = static_cast<uint32_t>(sizeof(uint8_t) );  break;
        case GL_UNSIGNED_BYTE_2_3_3_REV:           result = 1;                                        break;
        case GL_UNSIGNED_BYTE_3_3_2:               result = 1;                                        break;
        case GL_UNSIGNED_INT:                      result = static_cast<uint32_t>(sizeof(uint32_t) ); break;
        case GL_UNSIGNED_INT_2_10_10_10_REV:       result = 4;                                        break;
        case GL_UNSIGNED_INT_5_9_9_9_REV:          result = 4;                                        break;
        case GL_UNSIGNED_INT_8_8_8_8:              result = 4;                                        break;
        case GL_UNSIGNED_INT_8_8_8_8_REV:          result = 4;                                        break;
        case GL_UNSIGNED_INT_10_10_10_2:           result = 4;                                        break;
        case GL_UNSIGNED_INT_10F_11F_11F_REV:      result = 4;                                        break;
        case GL_UNSIGNED_INT_24_8:                 result = 4;                                        break;
        case GL_FLOAT_32_UNSIGNED_INT_24_8_REV:    result = 8;                                        break;
        case GL_UNSIGNED_SHORT:                    result = static_cast<uint32_t>(sizeof(uint16_t) ); break;
        case GL_UNSIGNED_SHORT_1_5_5_5_REV:        result = 2;                                        break;
        case GL_UNSIGNED_SHORT_4_4_4_4:            result = 2;                                        break;
        case GL_UNSIGNED_SHORT_4_4_4_4_REV:        result = 2;                                        break;
        case GL_UNSIGNED_SHORT_5_5_5_1:            result = 2;                                        break;
        case GL_UNSIGNED_SHORT_5_6_5:              result = 2;                                        break;
        case GL_UNSIGNED_SHORT_5_6_5_REV:          result = 2;                                        break;

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
        case GL_ALPHA:           result = 1; break;
        case GL_BGR:             result = 3; break;
        case GL_BGR_INTEGER:     result = 3; break;
        case GL_BGRA:            result = 4; break;
        case GL_BGRA_INTEGER:    result = 4; break;
        case GL_BLUE:            result = 1; break;
        case GL_BLUE_INTEGER:    result = 1; break;
        case GL_DEPTH_COMPONENT: result = 1; break;
        case GL_DEPTH_STENCIL:   result = 1; break;
        case GL_GREEN:           result = 1; break;
        case GL_GREEN_INTEGER:   result = 1; break;
        case GL_LUMINANCE:       result = 1; break;
        case GL_LUMINANCE_ALPHA: result = 2; break;
        case GL_RED:             result = 1; break;
        case GL_RED_INTEGER:     result = 1; break;
        case GL_RG:              result = 2; break;
        case GL_RG_INTEGER:      result = 2; break;
        case GL_RGB:             result = 3; break;
        case GL_RGB_INTEGER:     result = 3; break;
        case GL_RGBA:            result = 4; break;
        case GL_RGBA_INTEGER:    result = 4; break;
        case GL_STENCIL_INDEX:   result = 1; break;

        default:
        {
            assert(false);
        }
    }

    assert(result != 0);
    return result;
}

uint32_t OpenGL::Utils::get_n_texel_bytes(const GLenum& in_format,
                                          const GLenum& in_type)
{
    uint32_t result = 0;

    if (OpenGL::Utils::is_packed_pixel_type(in_type) )
    {
        result = OpenGL::Utils::get_n_bytes_for_type(in_type);
    }
    else
    {
        result = OpenGL::Utils::get_n_components_for_format(in_format) * OpenGL::Utils::get_n_bytes_for_type(in_type);
    }

    return result;
}
