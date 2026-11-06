/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_NAMED_FRAMEBUFFER_DRAW_BUFFERS_H
#define AI_GL_NAMED_FRAMEBUFFER_DRAW_BUFFERS_H

#include "interception/hooks/OpenGL/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            void AI_APIENTRY aiNamedFramebufferDrawBuffers(GLuint        framebuffer,
                                                           GLsizei       n,
                                                           const GLenum* bufs);
        }
    }
}

#endif /* AI_GL_NAMED_FRAMEBUFFER_DRAW_BUFFERS_H */
