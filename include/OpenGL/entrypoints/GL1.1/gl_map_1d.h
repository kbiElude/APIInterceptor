/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_MAP_1D_H
#define AI_GL_MAP_1D_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiMap1d(GLenum          target,
                             GLdouble        u1,
                             GLdouble        u2,
                             GLint           stride,
                             GLint           order,
                             const GLdouble* points);
}

#endif /* AI_GL_MAP_1D_H */