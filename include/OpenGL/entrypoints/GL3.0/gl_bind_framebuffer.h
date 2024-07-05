/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_BIND_FRAMEBUFFER_H
#define AI_GL_BIND_FRAMEBUFFER_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiBindFramebuffer(GLenum target,
                                       GLuint framebuffer);
}

#endif /* AI_GL_BIND_FRAMEBUFFER_H */