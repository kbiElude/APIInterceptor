/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_RECT_FV_H
#define AI_GL_RECT_FV_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiRectfv(const GLfloat* v1,
                              const GLfloat* v2);
}

#endif /* AI_GL_RECT_FV_H */