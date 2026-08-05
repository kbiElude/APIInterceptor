/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_PUSH_DEBUG_GROUP_H
#define AI_GL_PUSH_DEBUG_GROUP_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiPushDebugGroup(GLenum source, GLuint id, GLsizei length, const GLchar* message);
}

#endif /* AI_GL_PUSH_DEBUG_GROUP_H */
