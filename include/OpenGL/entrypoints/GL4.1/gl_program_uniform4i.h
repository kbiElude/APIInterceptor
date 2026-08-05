/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_PROGRAM_UNIFORM4I_H
#define AI_GL_PROGRAM_UNIFORM4I_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiProgramUniform4i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
}

#endif /* AI_GL_PROGRAM_UNIFORM4I_H */
