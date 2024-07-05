/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_POLYGON_OFFSET_H
#define AI_GL_POLYGON_OFFSET_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiPolygonOffset(GLfloat factor,
                                     GLfloat units);
}

#endif /* AI_GL_POLYGON_OFFSET_H */