/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_CLEAR_NAMED_BUFFER_DATA_H
#define AI_GL_CLEAR_NAMED_BUFFER_DATA_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiClearNamedBufferData(GLuint buffer, GLenum internalformat, GLenum format, GLenum type, const void* data);
}

#endif /* AI_GL_CLEAR_NAMED_BUFFER_DATA_H */
