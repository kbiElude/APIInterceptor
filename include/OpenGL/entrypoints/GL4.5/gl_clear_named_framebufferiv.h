/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_CLEAR_NAMED_FRAMEBUFFERIV_H
#define AI_GL_CLEAR_NAMED_FRAMEBUFFERIV_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiClearNamedFramebufferiv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLint* value);
}

#endif /* AI_GL_CLEAR_NAMED_FRAMEBUFFERIV_H */
