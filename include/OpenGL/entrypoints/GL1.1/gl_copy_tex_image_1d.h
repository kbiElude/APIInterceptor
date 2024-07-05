/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_COPY_TEX_IMAGE_1D_H
#define AI_GL_COPY_TEX_IMAGE_1D_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiCopyTexImage1D(GLenum  target,
                                      GLint   level,
                                      GLenum  internalformat,
                                      GLint   x,
                                      GLint   y,
                                      GLsizei width,
                                      GLint   border);
}

#endif /* AI_GL_COPY_TEX_IMAGE_1D_H */