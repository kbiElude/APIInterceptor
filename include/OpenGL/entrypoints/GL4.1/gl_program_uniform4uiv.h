/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_PROGRAM_UNIFORM4UIV_H
#define AI_GL_PROGRAM_UNIFORM4UIV_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiProgramUniform4uiv(GLuint program, GLint location, GLsizei count, const GLuint* value);
}

#endif /* AI_GL_PROGRAM_UNIFORM4UIV_H */
