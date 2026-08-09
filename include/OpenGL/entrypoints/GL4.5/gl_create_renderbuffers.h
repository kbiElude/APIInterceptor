/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_CREATE_RENDERBUFFERS_H
#define AI_GL_CREATE_RENDERBUFFERS_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiCreateRenderbuffers(GLsizei n, GLuint* renderbuffers);
}

#endif /* AI_GL_CREATE_RENDERBUFFERS_H */
