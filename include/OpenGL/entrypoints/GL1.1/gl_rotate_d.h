/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_ROTATE_D_H
#define AI_GL_ROTATE_D_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiRotated(GLdouble angle,
                               GLdouble x,
                               GLdouble y,
                               GLdouble z);
}

#endif /* AI_GL_ROTATE_D_H */