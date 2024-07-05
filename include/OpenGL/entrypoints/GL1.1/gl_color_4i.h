/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_COLOR_4I_H
#define AI_GL_COLOR_4I_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiColor4i(GLint red,
                               GLint green,
                               GLint blue,
                               GLint alpha);
}

#endif /* AI_GL_COLOR_4I_H */