/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_GEN_VERTEX_ARRAYS_H
#define AI_GL_GEN_VERTEX_ARRAYS_H

#include "Interception/Hooks/OpenGL/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            void AI_APIENTRY aiGenVertexArrays(GLsizei n,
                                               GLuint* arrays);
        }
    }
}

#endif /* AI_GL_GEN_VERTEX_ARRAYS_H */