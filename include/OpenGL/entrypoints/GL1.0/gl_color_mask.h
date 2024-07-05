/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_COLOR_MASK_H
#define AI_GL_COLOR_MASK_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiColorMask(GLboolean red,
                                 GLboolean green,
                                 GLboolean blue,
                                 GLboolean alpha);
}

#endif /* AI_GL_COLOR_MASK_H */