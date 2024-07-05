/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_DELETE_BUFFERS_H
#define AI_GL_DELETE_BUFFERS_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiDeleteBuffers(GLsizei       n,
                                     const GLuint* buffers);
}

#endif /* AI_GL_DELETE_BUFFERS_H */