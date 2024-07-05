/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_VERTEX_ATTRIB_I_4UI_H
#define AI_GL_VERTEX_ATTRIB_I_4UI_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiVertexAttribI4ui(GLuint index,
                                        GLuint x,
                                        GLuint y,
                                        GLuint z,
                                        GLuint w);
}

#endif /* AI_GL_VERTEX_ATTRIB_I_4UI_H */