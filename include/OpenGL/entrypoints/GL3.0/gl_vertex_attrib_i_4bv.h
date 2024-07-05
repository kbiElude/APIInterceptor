/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_VERTEX_ATTRIB_I_4BV_H
#define AI_GL_VERTEX_ATTRIB_I_4BV_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiVertexAttribI4bv(GLuint        index,
                                        const GLbyte* v);
}

#endif /* AI_GL_VERTEX_ATTRIB_I_4BV_H */