/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_FRAMEBUFFER_TEXTURE_3D_H
#define AI_GL_FRAMEBUFFER_TEXTURE_3D_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiFramebufferTexture3D(GLenum target,
                                            GLenum attachment,
                                            GLenum textarget,
                                            GLuint texture,
                                            GLint  level,
                                            GLint  zoffset);
}

#endif /* AI_GL_FRAMEBUFFER_TEXTURE_3D_H */