/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_MAP_1F_H
#define AI_GL_MAP_1F_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiMap1f(GLenum         target,
                             GLfloat        u1,
                             GLfloat        u2,
                             GLint          stride,
                             GLint          order,
                             const GLfloat* points);
}

#endif /* AI_GL_MAP_1F_H */