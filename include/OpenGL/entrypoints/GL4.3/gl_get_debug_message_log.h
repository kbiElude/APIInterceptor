/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_GET_DEBUG_MESSAGE_LOG_H
#define AI_GL_GET_DEBUG_MESSAGE_LOG_H

#include "OpenGL/types.h"

namespace OpenGL
{
    GLuint AI_APIENTRY aiGetDebugMessageLog(GLuint count, GLsizei bufSize, GLenum* sources, GLenum* types, GLuint* ids, GLenum* severities, GLsizei* lengths, GLchar* messageLog);
}

#endif /* AI_GL_GET_DEBUG_MESSAGE_LOG_H */
