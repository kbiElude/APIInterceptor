/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_COMPRESSED_TEXTURE_SUB_IMAGE2D_H
#define AI_GL_COMPRESSED_TEXTURE_SUB_IMAGE2D_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiCompressedTextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void* data);
}

#endif /* AI_GL_COMPRESSED_TEXTURE_SUB_IMAGE2D_H */
