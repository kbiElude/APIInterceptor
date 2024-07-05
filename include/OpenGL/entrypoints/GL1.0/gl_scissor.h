/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_SCISSOR_H
#define AI_GL_SCISSOR_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiScissor(GLint   x,
                               GLint   y,
                               GLsizei width,
                               GLsizei height);
}

#endif /* AI_GL_SCISSOR_H */