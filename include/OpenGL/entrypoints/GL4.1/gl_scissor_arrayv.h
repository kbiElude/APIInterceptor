/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_SCISSOR_ARRAYV_H
#define AI_GL_SCISSOR_ARRAYV_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiScissorArrayv(GLuint first, GLsizei count, const GLint* v);
}

#endif /* AI_GL_SCISSOR_ARRAYV_H */
