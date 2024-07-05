/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_UNIFORM_3I_H
#define AI_GL_UNIFORM_3I_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiUniform3i(GLint location,
                                 GLint v0,
                                 GLint v1,
                                 GLint v2);
}

#endif /* AI_GL_UNIFORM_3I_H */