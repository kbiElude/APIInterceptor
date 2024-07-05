/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_UNIFORM_2UIV_H
#define AI_GL_UNIFORM_2UIV_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiUniform2uiv(GLint         location,
                                   GLsizei       count,
                                   const GLuint* value);
}

#endif /* AI_GL_UNIFORM_2UIV_H */