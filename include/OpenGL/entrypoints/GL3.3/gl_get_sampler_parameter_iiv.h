/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_GET_SAMPLER_PARAMETER_IIV_H
#define AI_GL_GET_SAMPLER_PARAMETER_IIV_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiGetSamplerParameterIiv(GLuint  sampler,
                                              GLenum  pname,
                                              GLint*  params);
}

#endif /* AI_GL_GET_SAMPLER_PARAMETER_IIV_H */
