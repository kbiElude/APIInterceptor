/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_FRAMEBUFFER_TEXTURE_1D_H
#define AI_GL_FRAMEBUFFER_TEXTURE_1D_H

#include "Interception/Hooks/OpenGL/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            void AI_APIENTRY aiFramebufferTexture1D(GLenum target,
                                                    GLenum attachment,
                                                    GLenum textarget,
                                                    GLuint texture,
                                                    GLint  level);
        }
    }
}

#endif /* AI_GL_FRAMEBUFFER_TEXTURE_1D_H */