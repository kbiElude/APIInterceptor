/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_COMPRESSED_TEX_SUB_IMAGE_3D_H
#define AI_GL_COMPRESSED_TEX_SUB_IMAGE_3D_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiCompressedTexSubImage3D(GLenum      target,
                                               GLint       level,
                                               GLint       xoffset,
                                               GLint       yoffset,
                                               GLint       zoffset,
                                               GLsizei     width,
                                               GLsizei     height,
                                               GLsizei     depth,
                                               GLenum      format,
                                               GLsizei     imageSize,
                                               const void* data);
}

#endif /* AI_GL_COMPRESSED_TEX_SUB_IMAGE_3D_H */