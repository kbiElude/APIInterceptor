/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_GET_VERTEX_ATTRIB_POINTERV_H
#define AI_GL_GET_VERTEX_ATTRIB_POINTERV_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiGetVertexAttribPointerv(GLuint index,
                                               GLenum pname,
                                               void** pointer);
}

#endif /* AI_GL_GET_VERTEX_ATTRIB_POINTERV_H */