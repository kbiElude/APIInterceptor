/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_TEX_SUB_IMAGE_3D_H
#define AI_GL_TEX_SUB_IMAGE_3D_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiTexSubImage3D(GLenum      target,
                                     GLint       level,
                                     GLint       xoffset,
                                     GLint       yoffset,
                                     GLint       zoffset,
                                     GLsizei     width,
                                     GLsizei     height,
                                     GLsizei     depth,
                                     GLenum      format,
                                     GLenum      type,
                                     const void* pixels);
}

#endif /* AI_GL_TEX_SUB_IMAGE_3D_H */