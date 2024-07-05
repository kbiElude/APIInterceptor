/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_COLOR_3UB_H
#define AI_GL_COLOR_3UB_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiColor3ub(GLubyte red,
                                GLubyte green,
                                GLubyte blue);
}

#endif /* AI_GL_COLOR_3UB_H */