/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_FRAMEBUFFER_PARAMETERI_H
#define AI_GL_FRAMEBUFFER_PARAMETERI_H

#include "interception/hooks/OpenGL/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            void AI_APIENTRY aiFramebufferParameteri(GLenum target,
                                                     GLenum pname,
                                                     GLint  param);
        }
    }
}

#endif /* AI_GL_FRAMEBUFFER_PARAMETERI_H */
