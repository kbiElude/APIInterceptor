/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_COLOR_4S_H
#define AI_GL_COLOR_4S_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiColor4s(GLshort red,
                               GLshort green,
                               GLshort blue,
                               GLshort alpha);
}

#endif /* AI_GL_COLOR_4S_H */