/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_GET_ACTIVE_UNIFORM_H
#define AI_GL_GET_ACTIVE_UNIFORM_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiGetActiveUniform(GLuint   program,
                                        GLuint   index,
                                        GLsizei  bufSize,
                                        GLsizei* length,
                                        GLint*   size,
                                        GLenum*  type,
                                        GLchar*  name);
}

#endif /* AI_GL_GET_ACTIVE_UNIFORM_H */