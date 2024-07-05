/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_COLOR_4B_H
#define AI_GL_COLOR_4B_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiColor4b(GLbyte red,
                               GLbyte green,
                               GLbyte blue,
                               GLbyte alpha);
}

#endif /* AI_GL_COLOR_4B_H */