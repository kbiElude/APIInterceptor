/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_GET_COMPRESSED_TEXTURE_IMAGE_H
#define AI_GL_GET_COMPRESSED_TEXTURE_IMAGE_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiGetCompressedTextureImage(GLuint texture, GLint level, GLsizei bufSize, void* pixels);
}

#endif /* AI_GL_GET_COMPRESSED_TEXTURE_IMAGE_H */
