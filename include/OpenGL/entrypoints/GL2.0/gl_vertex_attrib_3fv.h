/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_VERTEX_ATTRIB_3FV_H
#define AI_GL_VERTEX_ATTRIB_3FV_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiVertexAttrib3fv(GLuint         index,
                                       const GLfloat* v);
}

#endif /* AI_GL_VERTEX_ATTRIB_3FV_H */