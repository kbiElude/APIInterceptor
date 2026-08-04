/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_GET_ACTIVE_SUBROUTINE_UNIFORM_NAME_H
#define AI_GL_GET_ACTIVE_SUBROUTINE_UNIFORM_NAME_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiGetActiveSubroutineUniformName(GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei* length, GLchar* name);
}

#endif /* AI_GL_GET_ACTIVE_SUBROUTINE_UNIFORM_NAME_H */
