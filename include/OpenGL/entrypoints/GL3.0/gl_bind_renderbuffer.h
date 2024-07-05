/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_BIND_RENDERBUFFER_H
#define AI_GL_BIND_RENDERBUFFER_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiBindRenderbuffer(GLenum target,
                                        GLuint renderbuffer);
}

#endif /* AI_GL_BIND_RENDERBUFFER_H */