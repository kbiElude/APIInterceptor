/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_VERTEX_ATTRIB_POINTER_H
#define AI_GL_VERTEX_ATTRIB_POINTER_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiVertexAttribPointer(GLuint      index,
                                           GLint       size,
                                           GLenum      type,
                                           GLboolean   normalized,
                                           GLsizei     stride,
                                           const void* pointer);
}

#endif /* AI_GL_VERTEX_ATTRIB_POINTER_H */