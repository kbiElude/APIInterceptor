/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_READN_PIXELS_H
#define AI_GL_READN_PIXELS_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiReadnPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, void* data);
}

#endif /* AI_GL_READN_PIXELS_H */
