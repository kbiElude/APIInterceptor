/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_SAMPLER_PARAMETER_IIV_H
#define AI_GL_SAMPLER_PARAMETER_IIV_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiSamplerParameterIiv(GLuint       sampler,
                                           GLenum       pname,
                                           const GLint* param);
}

#endif /* AI_GL_SAMPLER_PARAMETER_IIV_H */
