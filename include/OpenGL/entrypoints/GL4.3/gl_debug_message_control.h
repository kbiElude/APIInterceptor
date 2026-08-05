/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_DEBUG_MESSAGE_CONTROL_H
#define AI_GL_DEBUG_MESSAGE_CONTROL_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiDebugMessageControl(GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint* ids, GLboolean enabled);
}

#endif /* AI_GL_DEBUG_MESSAGE_CONTROL_H */
