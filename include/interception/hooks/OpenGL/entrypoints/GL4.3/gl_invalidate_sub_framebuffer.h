/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_INVALIDATE_SUB_FRAMEBUFFER_H
#define AI_GL_INVALIDATE_SUB_FRAMEBUFFER_H

#include "interception/hooks/OpenGL/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            void AI_APIENTRY aiInvalidateSubFramebuffer(GLenum        target,
                                                        GLsizei       numAttachments,
                                                        const GLenum* attachments,
                                                        GLint         x,
                                                        GLint         y,
                                                        GLsizei       width,
                                                        GLsizei       height);
        }
    }
}

#endif /* AI_GL_INVALIDATE_SUB_FRAMEBUFFER_H */
