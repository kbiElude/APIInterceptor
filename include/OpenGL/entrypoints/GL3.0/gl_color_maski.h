/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_COLOR_MASKI_H
#define AI_GL_COLOR_MASKI_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiColorMaski(GLuint    index,
                                  GLboolean r,
                                  GLboolean g,
                                  GLboolean b,
                                  GLboolean a);
}

#endif /* AI_GL_COLOR_MASKI_H */