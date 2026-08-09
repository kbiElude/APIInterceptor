/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_COPY_TEXTURE_SUB_IMAGE2D_H
#define AI_GL_COPY_TEXTURE_SUB_IMAGE2D_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiCopyTextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
}

#endif /* AI_GL_COPY_TEXTURE_SUB_IMAGE2D_H */
