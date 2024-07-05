/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_BLIT_FRAMEBUFFER_H
#define AI_GL_BLIT_FRAMEBUFFER_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiBlitFramebuffer(GLint      srcX0,
                                       GLint      srcY0,
                                       GLint      srcX1,
                                       GLint      srcY1,
                                       GLint      dstX0,
                                       GLint      dstY0,
                                       GLint      dstX1,
                                       GLint      dstY1,
                                       GLbitfield mask,
                                       GLenum     filter);
}

#endif /* AI_GL_BLIT_FRAMEBUFFER_H */