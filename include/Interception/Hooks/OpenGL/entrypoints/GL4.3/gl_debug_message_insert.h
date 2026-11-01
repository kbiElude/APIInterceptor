/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_DEBUG_MESSAGE_INSERT_H
#define AI_GL_DEBUG_MESSAGE_INSERT_H

#include "Interception/Hooks/OpenGL/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            void AI_APIENTRY aiDebugMessageInsert(GLenum        source,
                                                  GLenum        type,
                                                  GLuint        id,
                                                  GLenum        severity,
                                                  GLsizei       length,
                                                  const GLchar* buf);
        }
    }
}

#endif /* AI_GL_DEBUG_MESSAGE_INSERT_H */
