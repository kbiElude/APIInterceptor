/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_RECT_F_H
#define AI_GL_RECT_F_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiRectf(GLfloat x1,
                             GLfloat y1,
                             GLfloat x2,
                             GLfloat y2);
}

#endif /* AI_GL_RECT_F_H */