/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_GET_SAMPLER_PARAMETER_IUIV_H
#define AI_GL_GET_SAMPLER_PARAMETER_IUIV_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiGetSamplerParameterIuiv(GLuint  sampler,
                                               GLenum  pname,
                                               GLuint* params);
}

#endif /* AI_GL_GET_SAMPLER_PARAMETER_IUIV_H */
