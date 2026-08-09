/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_NAMED_FRAMEBUFFER_RENDERBUFFER_H
#define AI_GL_NAMED_FRAMEBUFFER_RENDERBUFFER_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiNamedFramebufferRenderbuffer(GLuint framebuffer, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
}

#endif /* AI_GL_NAMED_FRAMEBUFFER_RENDERBUFFER_H */
