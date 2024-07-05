/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_CLEAR_BUFFER_FI_H
#define AI_GL_CLEAR_BUFFER_FI_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiClearBufferfi(GLenum  buffer,
                                     GLint   drawbuffer,
                                     GLfloat depth,
                                     GLint   stencil);
}

#endif /* AI_GL_CLEAR_BUFFER_FI_H */