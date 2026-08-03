/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_MULTI_TEX_COORD_2D_H
#define AI_GL_MULTI_TEX_COORD_2D_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiMultiTexCoord2d(GLenum   target,
                                       GLdouble s,
                                       GLdouble t);
}

#endif /* AI_GL_MULTI_TEX_COORD_2D_H */