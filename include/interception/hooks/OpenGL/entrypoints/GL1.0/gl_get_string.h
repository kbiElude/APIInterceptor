/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_GET_STRING_H
#define AI_GL_GET_STRING_H

#include "interception/hooks/OpenGL/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            const GLubyte *APIENTRY aiGetString(GLenum name);
        }
    }
}

#endif /* AI_GL_GET_STRING_H */