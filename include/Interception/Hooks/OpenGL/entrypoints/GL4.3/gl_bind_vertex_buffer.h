/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_BIND_VERTEX_BUFFER_H
#define AI_GL_BIND_VERTEX_BUFFER_H

#include "Interception/Hooks/OpenGL/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            void AI_APIENTRY aiBindVertexBuffer(GLuint   bindingindex,
                                                GLuint   buffer,
                                                GLintptr offset,
                                                GLsizei  stride);
        }
    }
}

#endif /* AI_GL_BIND_VERTEX_BUFFER_H */
