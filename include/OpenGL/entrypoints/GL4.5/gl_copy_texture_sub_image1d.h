/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_COPY_TEXTURE_SUB_IMAGE1D_H
#define AI_GL_COPY_TEXTURE_SUB_IMAGE1D_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiCopyTextureSubImage1D(GLuint texture, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
}

#endif /* AI_GL_COPY_TEXTURE_SUB_IMAGE1D_H */
