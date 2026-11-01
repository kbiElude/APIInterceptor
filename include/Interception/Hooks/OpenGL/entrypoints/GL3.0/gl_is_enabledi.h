/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_IS_ENABLEDI_H
#define AI_GL_IS_ENABLEDI_H

#include "Interception/Hooks/OpenGL/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            GLboolean AI_APIENTRY aiIsEnabledi(GLenum target,
                                               GLuint index);
        }
    }
}

#endif /* AI_GL_IS_ENABLEDI_H */