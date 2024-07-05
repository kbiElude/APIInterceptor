/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_VERTEX_ATTRIB_4NUB_H
#define AI_GL_VERTEX_ATTRIB_4NUB_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiVertexAttrib4Nub(GLuint  index,
                                        GLubyte x,
                                        GLubyte y,
                                        GLubyte z,
                                        GLubyte w);
}

#endif /* AI_GL_VERTEX_ATTRIB_4NUB_H */