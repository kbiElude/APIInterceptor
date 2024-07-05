/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_UNIFORM_4F_H
#define AI_GL_UNIFORM_4F_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiUniform4f(GLint   location,
                                 GLfloat v0,
                                 GLfloat v1,
                                 GLfloat v2,
                                 GLfloat v3);
}

#endif /* AI_GL_UNIFORM_4F_H */