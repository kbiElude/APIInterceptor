/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_SCISSOR_INDEXED_H
#define AI_GL_SCISSOR_INDEXED_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiScissorIndexed(GLuint index, GLint left, GLint bottom, GLsizei width, GLsizei height);
}

#endif /* AI_GL_SCISSOR_INDEXED_H */
