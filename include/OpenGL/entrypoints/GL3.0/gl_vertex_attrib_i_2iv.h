/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_VERTEX_ATTRIB_I_2IV_H
#define AI_GL_VERTEX_ATTRIB_I_2IV_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiVertexAttribI2iv(GLuint       index,
                                        const GLint* v);
}

#endif /* AI_GL_VERTEX_ATTRIB_I_2IV_H */