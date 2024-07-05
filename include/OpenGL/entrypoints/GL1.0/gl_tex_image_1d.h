/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_TEX_IMAGE_1D_H
#define AI_GL_TEX_IMAGE_1D_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiTexImage1D(GLenum      target,
                                  GLint       level,
                                  GLint       internalformat,
                                  GLsizei     width,
                                  GLint       border,
                                  GLenum      format,
                                  GLenum      type,
                                  const void* pixels);
}

#endif /* AI_GL_TEX_IMAGE_1D_H */