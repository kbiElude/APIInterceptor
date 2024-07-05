/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_POLYGON_STIPPLE_H
#define AI_GL_POLYGON_STIPPLE_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiPolygonStipple(const GLubyte *mask);
}

#endif /* AI_GL_POLYGON_STIPPLE_H */