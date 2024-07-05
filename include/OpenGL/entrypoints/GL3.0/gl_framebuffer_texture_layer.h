/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_FRAMEBUFFER_TEXTURE_LAYER_H
#define AI_GL_FRAMEBUFFER_TEXTURE_LAYER_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiFramebufferTextureLayer(GLenum target,
                                               GLenum attachment,
                                               GLuint texture,
                                               GLint  level,
                                               GLint  layer);
}

#endif /* AI_GL_FRAMEBUFFER_TEXTURE_LAYER_H */