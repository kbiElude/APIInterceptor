/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_UNIFORM_SUBROUTINESUIV_H
#define AI_GL_UNIFORM_SUBROUTINESUIV_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiUniformSubroutinesuiv(GLenum shadertype, GLsizei count, const GLuint* indices);
}

#endif /* AI_GL_UNIFORM_SUBROUTINESUIV_H */
