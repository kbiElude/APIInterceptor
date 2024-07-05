/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_CHECK_FRAMEBUFFER_STATUS_H
#define AI_GL_CHECK_FRAMEBUFFER_STATUS_H

#include "OpenGL/types.h"

namespace OpenGL
{
    GLenum AI_APIENTRY aiCheckFramebufferStatus(GLenum target);
}

#endif /* AI_GL_CHECK_FRAMEBUFFER_STATUS_H */