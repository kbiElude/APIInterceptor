/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_COLOR_3D_H
#define AI_GL_COLOR_3D_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiColor3d(GLdouble red,
                               GLdouble green,
                               GLdouble blue);
}

#endif /* AI_GL_COLOR_3D_H */