/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_CLEAR_COLOR_H
#define AI_GL_CLEAR_COLOR_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiClearColor(GLfloat red,
                                  GLfloat green,
                                  GLfloat blue,
                                  GLfloat alpha);
}

#endif /* AI_GL_CLEAR_COLOR_H */