/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_CLAMP_COLOR_H
#define AI_GL_CLAMP_COLOR_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiClampColor(GLenum target,
                                  GLenum clamp);
}

#endif /* AI_GL_CLAMP_COLOR_H */