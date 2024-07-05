/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_VERTEX_ATTRIB_I_3UIV_H
#define AI_GL_VERTEX_ATTRIB_I_3UIV_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiVertexAttribI3uiv(GLuint        index,
                                         const GLuint* v);
}

#endif /* AI_GL_VERTEX_ATTRIB_I_3UIV_H */