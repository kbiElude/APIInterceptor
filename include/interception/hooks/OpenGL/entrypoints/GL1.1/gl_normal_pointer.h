/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_NORMAL_POINTER_H
#define AI_GL_NORMAL_POINTER_H

#include "interception/hooks/OpenGL/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            void AI_APIENTRY aiNormalPointer(GLenum        type,
                                             GLsizei       stride,
                                             const GLvoid* pointer);
        }
    }
}

#endif /* AI_GL_NORMAL_POINTER_H */