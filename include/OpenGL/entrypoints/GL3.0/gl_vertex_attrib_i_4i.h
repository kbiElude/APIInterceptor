/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_VERTEX_ATTRIB_I_4I_H
#define AI_GL_VERTEX_ATTRIB_I_4I_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiVertexAttribI4i(GLuint index,
                                       GLint  x,
                                       GLint  y,
                                       GLint  z,
                                       GLint  w);
}

#endif /* AI_GL_VERTEX_ATTRIB_I_4I_H */