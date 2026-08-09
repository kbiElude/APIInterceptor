/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_COPY_NAMED_BUFFER_SUB_DATA_H
#define AI_GL_COPY_NAMED_BUFFER_SUB_DATA_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiCopyNamedBufferSubData(GLuint readBuffer, GLuint writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size);
}

#endif /* AI_GL_COPY_NAMED_BUFFER_SUB_DATA_H */
