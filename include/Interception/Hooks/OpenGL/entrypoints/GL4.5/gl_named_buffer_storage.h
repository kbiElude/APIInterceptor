/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_NAMED_BUFFER_STORAGE_H
#define AI_GL_NAMED_BUFFER_STORAGE_H

#include "Interception/Hooks/OpenGL/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            void AI_APIENTRY aiNamedBufferStorage(GLuint      buffer,
                                                  GLsizeiptr  size,
                                                  const void* data,
                                                  GLbitfield  flags);
        }
    }
}

#endif /* AI_GL_NAMED_BUFFER_STORAGE_H */
