/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_GET_ACTIVE_SUBROUTINE_UNIFORMIV_H
#define AI_GL_GET_ACTIVE_SUBROUTINE_UNIFORMIV_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiGetActiveSubroutineUniformiv(GLuint program, GLenum shadertype, GLuint index, GLenum pname, GLint* values);
}

#endif /* AI_GL_GET_ACTIVE_SUBROUTINE_UNIFORMIV_H */
