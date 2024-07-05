/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_TEX_GEN_D_H
#define AI_GL_TEX_GEN_D_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiTexGend(GLenum   coord,
                               GLenum   pname,
                               GLdouble param);
}

#endif /* AI_GL_TEX_GEN_D_H */