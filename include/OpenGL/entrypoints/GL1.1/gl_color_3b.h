/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_COLOR_3B_H
#define AI_GL_COLOR_3B_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiColor3b(GLbyte red,
                               GLbyte green,
                               GLbyte blue);
}

#endif /* AI_GL_COLOR_3B_H */