/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_CLEAR_NAMED_FRAMEBUFFERFI_H
#define AI_GL_CLEAR_NAMED_FRAMEBUFFERFI_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiClearNamedFramebufferfi(GLuint framebuffer, GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil);
}

#endif /* AI_GL_CLEAR_NAMED_FRAMEBUFFERFI_H */
