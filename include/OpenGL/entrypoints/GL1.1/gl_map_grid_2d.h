/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_MAP_GRID_2D_H
#define AI_GL_MAP_GRID_2D_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiMapGrid2d(GLint    un,
                                 GLdouble u1,
                                 GLdouble u2,
                                 GLint    vn,
                                 GLdouble v1,
                                 GLdouble v2);
}

#endif /* AI_GL_MAP_GRID_2D_H */