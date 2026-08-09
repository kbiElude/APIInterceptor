/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_NAMED_FRAMEBUFFER_DRAW_BUFFER_H
#define AI_GL_NAMED_FRAMEBUFFER_DRAW_BUFFER_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiNamedFramebufferDrawBuffer(GLuint framebuffer, GLenum buf);
}

#endif /* AI_GL_NAMED_FRAMEBUFFER_DRAW_BUFFER_H */
