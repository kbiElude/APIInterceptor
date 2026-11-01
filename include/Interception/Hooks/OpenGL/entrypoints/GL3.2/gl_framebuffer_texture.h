/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_FRAMEBUFFER_TEXTURE_H
#define AI_GL_FRAMEBUFFER_TEXTURE_H

#include "Interception/Hooks/OpenGL/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            void AI_APIENTRY aiFramebufferTexture(GLenum target,
                                                  GLenum attachment,
                                                  GLuint texture,
                                                  GLint  level);
        }
    }
}

#endif /* AI_GL_FRAMEBUFFER_TEXTURE_H */