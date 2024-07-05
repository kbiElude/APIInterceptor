/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_DRAW_PIXELS_H
#define AI_GL_DRAW_PIXELS_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiDrawPixels(GLsizei       width,
                                  GLsizei       height,
                                  GLenum        format,
                                  GLenum        type,
                                  const GLvoid* pixels);
}

#endif /* AI_GL_DRAW_PIXELS_H */