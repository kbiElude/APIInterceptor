/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_VERTEX_ATTRIB_3F_H
#define AI_GL_VERTEX_ATTRIB_3F_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiVertexAttrib3f(GLuint  index,
                                      GLfloat x,
                                      GLfloat y,
                                      GLfloat z);
}

#endif /* AI_GL_VERTEX_ATTRIB_3F_H */