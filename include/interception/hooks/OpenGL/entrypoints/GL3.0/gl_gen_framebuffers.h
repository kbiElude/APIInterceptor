/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_GEN_FRAMEBUFFERS_H
#define AI_GL_GEN_FRAMEBUFFERS_H

#include "interception/hooks/OpenGL/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            void AI_APIENTRY aiGenFramebuffers(GLsizei n,
                                               GLuint* framebuffers);
        }
    }
}

#endif /* AI_GL_GEN_FRAMEBUFFERS_H */