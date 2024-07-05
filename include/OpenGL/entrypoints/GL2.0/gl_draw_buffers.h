/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_DRAW_BUFFERS_H
#define AI_GL_DRAW_BUFFERS_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiDrawBuffers(GLsizei       n,
                                   const GLenum* bufs);
}

#endif /* AI_GL_DRAW_BUFFERS_H */