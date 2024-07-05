/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_ORTHO_H
#define AI_GL_ORTHO_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiOrtho(GLdouble left,
                             GLdouble right,
                             GLdouble bottom,
                             GLdouble top,
                             GLdouble zNear,
                             GLdouble zFar);
}

#endif /* AI_GL_ORTHO_H */