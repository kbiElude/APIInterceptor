/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_COMPRESSED_TEX_IMAGE_2D_H
#define AI_GL_COMPRESSED_TEX_IMAGE_2D_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiCompressedTexImage2D(GLenum      target,
                                            GLint       level,
                                            GLenum      internalformat,
                                            GLsizei     width,
                                            GLsizei     height,
                                            GLint       border,
                                            GLsizei     imageSize,
                                            const void* data);
}

#endif /* AI_GL_COMPRESSED_TEX_IMAGE_2D_H */