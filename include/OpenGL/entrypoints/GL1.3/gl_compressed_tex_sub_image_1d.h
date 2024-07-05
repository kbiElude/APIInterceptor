/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_COMPRESSED_TEX_SUB_IMAGE_1D_H
#define AI_GL_COMPRESSED_TEX_SUB_IMAGE_1D_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiCompressedTexSubImage1D(GLenum      target,
                                               GLint       level,
                                               GLint       xoffset,
                                               GLsizei     width,
                                               GLenum      format,
                                               GLsizei     imageSize,
                                               const void* data);
}

#endif /* AI_GL_COMPRESSED_TEX_SUB_IMAGE_1D_H */