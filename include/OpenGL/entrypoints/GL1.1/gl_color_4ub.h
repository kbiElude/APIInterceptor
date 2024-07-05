/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_COLOR_4UB_H
#define AI_GL_COLOR_4UB_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiColor4ub(GLubyte red,
                                GLubyte green,
                                GLubyte blue,
                                GLubyte alpha);
}

#endif /* AI_GL_COLOR_4UB_H */