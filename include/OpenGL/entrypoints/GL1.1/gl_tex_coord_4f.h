/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_TEX_COORD_4F_H
#define AI_GL_TEX_COORD_4F_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiTexCoord4f(GLfloat s,
                                  GLfloat t,
                                  GLfloat r,
                                  GLfloat q);
}

#endif /* AI_GL_TEX_COORD_4F_H */