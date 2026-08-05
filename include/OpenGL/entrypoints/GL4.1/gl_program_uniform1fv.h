/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_PROGRAM_UNIFORM1FV_H
#define AI_GL_PROGRAM_UNIFORM1FV_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiProgramUniform1fv(GLuint program, GLint location, GLsizei count, const GLfloat* value);
}

#endif /* AI_GL_PROGRAM_UNIFORM1FV_H */
