/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_MAP_GRID_2F_H
#define AI_GL_MAP_GRID_2F_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiMapGrid2f(GLint   un,
                                 GLfloat u1,
                                 GLfloat u2,
                                 GLint   vn,
                                 GLfloat v1,
                                 GLfloat v2);
}

#endif /* AI_GL_MAP_GRID_2F_H */