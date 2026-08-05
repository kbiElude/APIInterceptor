/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_PROGRAM_UNIFORM1IV_H
#define AI_GL_PROGRAM_UNIFORM1IV_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiProgramUniform1iv(GLuint program, GLint location, GLsizei count, const GLint* value);
}

#endif /* AI_GL_PROGRAM_UNIFORM1IV_H */
