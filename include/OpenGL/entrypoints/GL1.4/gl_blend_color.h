/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_BLEND_COLOR_H
#define AI_GL_BLEND_COLOR_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiBlendColor(GLfloat red,
                                  GLfloat green,
                                  GLfloat blue,
                                  GLfloat alpha);
}

#endif /* AI_GL_BLEND_COLOR_H */