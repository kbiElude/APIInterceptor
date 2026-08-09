/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_NAMED_FRAMEBUFFER_TEXTURE_H
#define AI_GL_NAMED_FRAMEBUFFER_TEXTURE_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiNamedFramebufferTexture(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level);
}

#endif /* AI_GL_NAMED_FRAMEBUFFER_TEXTURE_H */
