/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_BIND_BUFFERS_BASE_H
#define AI_GL_BIND_BUFFERS_BASE_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiBindBuffersBase(GLenum        target,
                                       GLuint        first,
                                       GLsizei       count,
                                       const GLuint* buffers);
}

#endif /* AI_GL_BIND_BUFFERS_BASE_H */
