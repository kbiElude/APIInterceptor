/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_COLOR_4D_H
#define AI_GL_COLOR_4D_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiColor4d(GLdouble red,
                               GLdouble green,
                               GLdouble blue,
                               GLdouble alpha);
}

#endif /* AI_GL_COLOR_4D_H */