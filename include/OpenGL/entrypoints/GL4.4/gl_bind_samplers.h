/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_BIND_SAMPLERS_H
#define AI_GL_BIND_SAMPLERS_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiBindSamplers(GLuint        first,
                                    GLsizei       count,
                                    const GLuint* samplers);
}

#endif /* AI_GL_BIND_SAMPLERS_H */
