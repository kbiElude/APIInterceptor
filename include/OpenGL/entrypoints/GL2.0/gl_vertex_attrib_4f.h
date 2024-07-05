/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_VERTEX_ATTRIB_4F_H
#define AI_GL_VERTEX_ATTRIB_4F_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiVertexAttrib4f(GLuint  index,
                                      GLfloat x,
                                      GLfloat y,
                                      GLfloat z,
                                      GLfloat w);
}

#endif /* AI_GL_VERTEX_ATTRIB_4F_H */