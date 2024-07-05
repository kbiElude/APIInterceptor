/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_TEX_COORD_4D_H
#define AI_GL_TEX_COORD_4D_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiTexCoord4d(GLdouble s,
                                  GLdouble t,
                                  GLdouble r,
                                  GLdouble q);
}

#endif /* AI_GL_TEX_COORD_4D_H */