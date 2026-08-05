/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_INVALIDATE_BUFFER_SUB_DATA_H
#define AI_GL_INVALIDATE_BUFFER_SUB_DATA_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiInvalidateBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr length);
}

#endif /* AI_GL_INVALIDATE_BUFFER_SUB_DATA_H */
