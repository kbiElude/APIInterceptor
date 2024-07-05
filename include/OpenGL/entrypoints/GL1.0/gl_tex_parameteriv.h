/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_TEX_PARAMETERIV_H
#define AI_GL_TEX_PARAMETERIV_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiTexParameteriv(GLenum       target,
                                      GLenum       pname,
                                      const GLint* params);
}

#endif /* AI_GL_TEX_PARAMETERIV_H */