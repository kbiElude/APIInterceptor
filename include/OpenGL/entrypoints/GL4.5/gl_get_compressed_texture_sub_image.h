/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_GET_COMPRESSED_TEXTURE_SUB_IMAGE_H
#define AI_GL_GET_COMPRESSED_TEXTURE_SUB_IMAGE_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiGetCompressedTextureSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLsizei bufSize, void* pixels);
}

#endif /* AI_GL_GET_COMPRESSED_TEXTURE_SUB_IMAGE_H */
