/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_MAP_2D_H
#define AI_GL_MAP_2D_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiMap2d(GLenum          target,
                             GLdouble        u1,
                             GLdouble        u2,
                             GLint           ustride,
                             GLint           uorder,
                             GLdouble        v1,
                             GLdouble        v2,
                             GLint           vstride,
                             GLint           vorder,
                             const GLdouble* points);
}

#endif /* AI_GL_MAP_2D_H */