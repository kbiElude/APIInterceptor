/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_BIND_SAMPLER_H
#define AI_GL_BIND_SAMPLER_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiBindSampler(GLuint unit,
                                   GLuint sampler);
}

#endif /* AI_GL_BIND_SAMPLER_H */
