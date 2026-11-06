/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Number of values which an API call reads through a pointer, when it depends on the parameter name. A name which is
 * not recognized trips an assertion, and gives 1, so that no more than a single value is ever read from the app.
 */
#if !defined(OPENGL_PARAM_COUNTS_H)
#define OPENGL_PARAM_COUNTS_H

#include "interception/hooks/OpenGL/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            namespace Utils
            {
                uint32_t get_n_call_lists_type_bytes   (const GLenum& in_type);
                uint32_t get_n_clear_buffer_values     (const GLenum& in_buffer);
                uint32_t get_n_fog_params              (const GLenum& in_pname);
                uint32_t get_n_light_model_params      (const GLenum& in_pname);
                uint32_t get_n_light_params            (const GLenum& in_pname);
                uint32_t get_n_map1_values             (const GLenum& in_target,
                                                        const GLint&  in_stride,
                                                        const GLint&  in_order);
                uint32_t get_n_map2_values             (const GLenum& in_target,
                                                        const GLint&  in_ustride,
                                                        const GLint&  in_uorder,
                                                        const GLint&  in_vstride,
                                                        const GLint&  in_vorder);
                uint32_t get_n_map_components          (const GLenum& in_target);
                uint32_t get_n_material_params         (const GLenum& in_pname);
                uint32_t get_n_patch_parameter_values  (const GLenum& in_pname);
                uint32_t get_n_tex_env_params          (const GLenum& in_target,
                                                        const GLenum& in_pname);
                uint32_t get_n_tex_gen_params          (const GLenum& in_pname);
                uint32_t get_n_texture_parameter_params(const GLenum& in_pname);
            }
        }
    }
}

#endif /* OPENGL_PARAM_COUNTS_H */
