/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_COPY_PIXELS_H
#define AI_GL_COPY_PIXELS_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiCopyPixels(GLint   x,
                                  GLint   y,
                                  GLsizei width,
                                  GLsizei height,
                                  GLenum  type);
}

#endif /* AI_GL_COPY_PIXELS_H */