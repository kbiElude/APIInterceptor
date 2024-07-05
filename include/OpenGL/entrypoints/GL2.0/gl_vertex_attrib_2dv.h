/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_VERTEX_ATTRIB_2DV_H
#define AI_GL_VERTEX_ATTRIB_2DV_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiVertexAttrib2dv(GLuint          index,
                                       const GLdouble* v);
}

#endif /* AI_GL_VERTEX_ATTRIB_2DV_H */