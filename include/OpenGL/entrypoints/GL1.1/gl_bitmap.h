/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_BITMAP_H
#define AI_GL_BITMAP_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiBitmap(GLsizei        width,
                              GLsizei        height,
                              GLfloat        xorig,
                              GLfloat        yorig,
                              GLfloat        xmove,
                              GLfloat        ymove,
                              const GLubyte* bitmap);
}

#endif /* AI_GL_BITMAP_H */