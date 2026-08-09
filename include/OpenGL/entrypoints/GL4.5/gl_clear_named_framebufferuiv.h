/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_CLEAR_NAMED_FRAMEBUFFERUIV_H
#define AI_GL_CLEAR_NAMED_FRAMEBUFFERUIV_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiClearNamedFramebufferuiv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLuint* value);
}

#endif /* AI_GL_CLEAR_NAMED_FRAMEBUFFERUIV_H */
