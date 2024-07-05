/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_MAP_2F_H
#define AI_GL_MAP_2F_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiMap2f(GLenum         target,
                             GLfloat        u1,
                             GLfloat        u2,
                             GLint          ustride,
                             GLint          uorder,
                             GLfloat        v1,
                             GLfloat        v2,
                             GLint          vstride,
                             GLint          vorder,
                             const GLfloat* points);
}

#endif /* AI_GL_MAP_2F_H */