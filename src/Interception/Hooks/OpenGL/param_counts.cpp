/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/macros.h"
#include "Interception/Hooks/OpenGL/param_counts.h"

/* gl/gl.h provides the compatibility-profile tokens which are absent from glcorearb.h. */
#include "gl/gl.h"

/* Compatibility-profile tokens which neither gl/gl.h nor the (core-guarded) Khronos headers provide. */
static constexpr GLenum COMPAT_GL_FOG_COORD_SRC             = 0x8450;
static constexpr GLenum COMPAT_GL_LIGHT_MODEL_COLOR_CONTROL = 0x81F8;
static constexpr GLenum COMPAT_GL_POINT_SPRITE              = 0x8861;
static constexpr GLenum COMPAT_GL_SRC0_ALPHA                = 0x8588;
static constexpr GLenum COMPAT_GL_SRC0_RGB                  = 0x8580;
static constexpr GLenum COMPAT_GL_SRC1_RGB                  = 0x8581;
static constexpr GLenum COMPAT_GL_SRC2_ALPHA                = 0x858A;
static constexpr GLenum COMPAT_GL_SRC2_RGB                  = 0x8582;

uint32_t Interception::Hooks::OpenGL::Utils::get_n_call_lists_type_bytes(const GLenum& in_type)
{
    uint32_t result = 1;

    switch (in_type)
    {
        case GL_2_BYTES:        result = 2; break;
        case GL_3_BYTES:        result = 3; break;
        case GL_4_BYTES:        result = 4; break;
        case GL_BYTE:           result = 1; break;
        case GL_FLOAT:          result = 4; break;
        case GL_INT:            result = 4; break;
        case GL_SHORT:          result = 2; break;
        case GL_UNSIGNED_BYTE:  result = 1; break;
        case GL_UNSIGNED_INT:   result = 4; break;
        case GL_UNSIGNED_SHORT: result = 2; break;

        default:
        {
            AI_FAIL_UNSUPPORTED(in_type);
        }
    }

    return result;
}

uint32_t Interception::Hooks::OpenGL::Utils::get_n_clear_buffer_values(const GLenum& in_buffer)
{
    uint32_t result = 1;

    switch (in_buffer)
    {
        case GL_COLOR:   result = 4; break;
        case GL_DEPTH:   result = 1; break;
        case GL_STENCIL: result = 1; break;

        default:
        {
            AI_FAIL_UNSUPPORTED(in_buffer);
        }
    }

    return result;
}

uint32_t Interception::Hooks::OpenGL::Utils::get_n_fog_params(const GLenum& in_pname)
{
    uint32_t result = 1;

    switch (in_pname)
    {
        case GL_FOG_COLOR: result = 4; break;

        case COMPAT_GL_FOG_COORD_SRC: /* fall-back */
        case GL_FOG_DENSITY:   /* fall-back */
        case GL_FOG_END:       /* fall-back */
        case GL_FOG_INDEX:     /* fall-back */
        case GL_FOG_MODE:      /* fall-back */
        case GL_FOG_START:
        {
            result = 1;

            break;
        }

        default:
        {
            AI_FAIL_UNSUPPORTED(in_pname);
        }
    }

    return result;
}

uint32_t Interception::Hooks::OpenGL::Utils::get_n_light_model_params(const GLenum& in_pname)
{
    uint32_t result = 1;

    switch (in_pname)
    {
        case GL_LIGHT_MODEL_AMBIENT: result = 4; break;

        case COMPAT_GL_LIGHT_MODEL_COLOR_CONTROL: /* fall-back */
        case GL_LIGHT_MODEL_LOCAL_VIEWER:  /* fall-back */
        case GL_LIGHT_MODEL_TWO_SIDE:
        {
            result = 1;

            break;
        }

        default:
        {
            AI_FAIL_UNSUPPORTED(in_pname);
        }
    }

    return result;
}

uint32_t Interception::Hooks::OpenGL::Utils::get_n_light_params(const GLenum& in_pname)
{
    uint32_t result = 1;

    switch (in_pname)
    {
        case GL_SPOT_DIRECTION: result = 3; break;

        case GL_AMBIENT:  /* fall-back */
        case GL_DIFFUSE:  /* fall-back */
        case GL_POSITION: /* fall-back */
        case GL_SPECULAR:
        {
            result = 4;

            break;
        }

        case GL_CONSTANT_ATTENUATION:  /* fall-back */
        case GL_LINEAR_ATTENUATION:    /* fall-back */
        case GL_QUADRATIC_ATTENUATION: /* fall-back */
        case GL_SPOT_CUTOFF:           /* fall-back */
        case GL_SPOT_EXPONENT:
        {
            result = 1;

            break;
        }

        default:
        {
            AI_FAIL_UNSUPPORTED(in_pname);
        }
    }

    return result;
}

uint32_t Interception::Hooks::OpenGL::Utils::get_n_map1_values(const GLenum& in_target,
                                                               const GLint&  in_stride,
                                                               const GLint&  in_order)
{
    uint32_t result = 0;

    if (in_stride >= 0 &&
        in_order  >  0)
    {
        result = static_cast<uint32_t>(in_order - 1) * static_cast<uint32_t>(in_stride) + get_n_map_components(in_target);
    }

    return result;
}

uint32_t Interception::Hooks::OpenGL::Utils::get_n_map2_values(const GLenum& in_target,
                                                               const GLint&  in_ustride,
                                                               const GLint&  in_uorder,
                                                               const GLint&  in_vstride,
                                                               const GLint&  in_vorder)
{
    uint32_t result = 0;

    if (in_ustride >= 0 &&
        in_uorder  >  0 &&
        in_vstride >= 0 &&
        in_vorder  >  0)
    {
        result = static_cast<uint32_t>(in_uorder - 1) * static_cast<uint32_t>(in_ustride) +
                 static_cast<uint32_t>(in_vorder - 1) * static_cast<uint32_t>(in_vstride) +
                 get_n_map_components(in_target);
    }

    return result;
}

uint32_t Interception::Hooks::OpenGL::Utils::get_n_map_components(const GLenum& in_target)
{
    uint32_t result = 1;

    switch (in_target)
    {
        case GL_MAP1_COLOR_4:         result = 4; break;
        case GL_MAP1_INDEX:           result = 1; break;
        case GL_MAP1_NORMAL:          result = 3; break;
        case GL_MAP1_TEXTURE_COORD_1: result = 1; break;
        case GL_MAP1_TEXTURE_COORD_2: result = 2; break;
        case GL_MAP1_TEXTURE_COORD_3: result = 3; break;
        case GL_MAP1_TEXTURE_COORD_4: result = 4; break;
        case GL_MAP1_VERTEX_3:        result = 3; break;
        case GL_MAP1_VERTEX_4:        result = 4; break;
        case GL_MAP2_COLOR_4:         result = 4; break;
        case GL_MAP2_INDEX:           result = 1; break;
        case GL_MAP2_NORMAL:          result = 3; break;
        case GL_MAP2_TEXTURE_COORD_1: result = 1; break;
        case GL_MAP2_TEXTURE_COORD_2: result = 2; break;
        case GL_MAP2_TEXTURE_COORD_3: result = 3; break;
        case GL_MAP2_TEXTURE_COORD_4: result = 4; break;
        case GL_MAP2_VERTEX_3:        result = 3; break;
        case GL_MAP2_VERTEX_4:        result = 4; break;

        default:
        {
            AI_FAIL_UNSUPPORTED(in_target);
        }
    }

    return result;
}

uint32_t Interception::Hooks::OpenGL::Utils::get_n_material_params(const GLenum& in_pname)
{
    uint32_t result = 1;

    switch (in_pname)
    {
        case GL_COLOR_INDEXES: result = 3; break;
        case GL_SHININESS:     result = 1; break;

        case GL_AMBIENT:             /* fall-back */
        case GL_AMBIENT_AND_DIFFUSE: /* fall-back */
        case GL_DIFFUSE:             /* fall-back */
        case GL_EMISSION:            /* fall-back */
        case GL_SPECULAR:
        {
            result = 4;

            break;
        }

        default:
        {
            AI_FAIL_UNSUPPORTED(in_pname);
        }
    }

    return result;
}

uint32_t Interception::Hooks::OpenGL::Utils::get_n_patch_parameter_values(const GLenum& in_pname)
{
    uint32_t result = 1;

    switch (in_pname)
    {
        case GL_PATCH_DEFAULT_INNER_LEVEL: result = 2; break;
        case GL_PATCH_DEFAULT_OUTER_LEVEL: result = 4; break;

        default:
        {
            AI_FAIL_UNSUPPORTED(in_pname);
        }
    }

    return result;
}

uint32_t Interception::Hooks::OpenGL::Utils::get_n_tex_env_params(const GLenum& in_target,
                                                                  const GLenum& in_pname)
{
    uint32_t result = 1;

    switch (in_target)
    {
        case COMPAT_GL_POINT_SPRITE:
        {
            AI_ASSERT(in_pname == GL_COORD_REPLACE);

            result = 1;

            break;
        }

        case GL_TEXTURE_ENV:
        {
            switch (in_pname)
            {
                case GL_TEXTURE_ENV_COLOR: result = 4; break;

                case GL_ALPHA_SCALE:       /* fall-back */
                case GL_COMBINE_ALPHA:     /* fall-back */
                case GL_COMBINE_RGB:       /* fall-back */
                case GL_OPERAND0_ALPHA:    /* fall-back */
                case GL_OPERAND0_RGB:      /* fall-back */
                case GL_OPERAND1_ALPHA:    /* fall-back */
                case GL_OPERAND1_RGB:      /* fall-back */
                case GL_OPERAND2_ALPHA:    /* fall-back */
                case GL_OPERAND2_RGB:      /* fall-back */
                case GL_RGB_SCALE:         /* fall-back */
                case COMPAT_GL_SRC0_ALPHA:        /* fall-back */
                case COMPAT_GL_SRC0_RGB:          /* fall-back */
                case GL_SRC1_ALPHA:        /* fall-back */
                case COMPAT_GL_SRC1_RGB:          /* fall-back */
                case COMPAT_GL_SRC2_ALPHA:        /* fall-back */
                case COMPAT_GL_SRC2_RGB:          /* fall-back */
                case GL_TEXTURE_ENV_MODE:
                {
                    result = 1;

                    break;
                }

                default:
                {
                    AI_FAIL_UNSUPPORTED(in_pname);
                }
            }

            break;
        }

        case GL_TEXTURE_FILTER_CONTROL:
        {
            AI_ASSERT(in_pname == GL_TEXTURE_LOD_BIAS);

            result = 1;

            break;
        }

        default:
        {
            AI_FAIL_UNSUPPORTED(in_target);
        }
    }

    return result;
}

uint32_t Interception::Hooks::OpenGL::Utils::get_n_tex_gen_params(const GLenum& in_pname)
{
    uint32_t result = 1;

    switch (in_pname)
    {
        case GL_EYE_PLANE:    /* fall-back */
        case GL_OBJECT_PLANE:
        {
            result = 4;

            break;
        }

        case GL_TEXTURE_GEN_MODE: result = 1; break;

        default:
        {
            AI_FAIL_UNSUPPORTED(in_pname);
        }
    }

    return result;
}

uint32_t Interception::Hooks::OpenGL::Utils::get_n_texture_parameter_params(const GLenum& in_pname)
{
    uint32_t result = 1;

    switch (in_pname)
    {
        case GL_TEXTURE_BORDER_COLOR: /* fall-back */
        case GL_TEXTURE_SWIZZLE_RGBA:
        {
            result = 4;

            break;
        }

        case GL_DEPTH_STENCIL_TEXTURE_MODE: /* fall-back */
        case GL_DEPTH_TEXTURE_MODE:         /* fall-back */
        case GL_GENERATE_MIPMAP:            /* fall-back */
        case GL_TEXTURE_BASE_LEVEL:         /* fall-back */
        case GL_TEXTURE_COMPARE_FUNC:       /* fall-back */
        case GL_TEXTURE_COMPARE_MODE:       /* fall-back */
        case GL_TEXTURE_LOD_BIAS:           /* fall-back */
        case GL_TEXTURE_MAG_FILTER:         /* fall-back */
        case GL_TEXTURE_MAX_ANISOTROPY_EXT: /* fall-back */
        case GL_TEXTURE_MAX_LEVEL:          /* fall-back */
        case GL_TEXTURE_MAX_LOD:            /* fall-back */
        case GL_TEXTURE_MIN_FILTER:         /* fall-back */
        case GL_TEXTURE_MIN_LOD:            /* fall-back */
        case GL_TEXTURE_PRIORITY:           /* fall-back */
        case GL_TEXTURE_SWIZZLE_A:          /* fall-back */
        case GL_TEXTURE_SWIZZLE_B:          /* fall-back */
        case GL_TEXTURE_SWIZZLE_G:          /* fall-back */
        case GL_TEXTURE_SWIZZLE_R:          /* fall-back */
        case GL_TEXTURE_WRAP_R:             /* fall-back */
        case GL_TEXTURE_WRAP_S:             /* fall-back */
        case GL_TEXTURE_WRAP_T:
        {
            result = 1;

            break;
        }

        default:
        {
            AI_FAIL_UNSUPPORTED(in_pname);
        }
    }

    return result;
}
