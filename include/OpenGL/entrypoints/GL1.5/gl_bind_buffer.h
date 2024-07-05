/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_BIND_BUFFER_H
#define AI_GL_BIND_BUFFER_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiBindBuffer(GLenum target,
                                  GLuint buffer);
}

#endif /* AI_GL_BIND_BUFFER_H */