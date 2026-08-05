/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_GET_PROGRAM_RESOURCEIV_H
#define AI_GL_GET_PROGRAM_RESOURCEIV_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiGetProgramResourceiv(GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum* props, GLsizei bufSize, GLsizei* length, GLint* params);
}

#endif /* AI_GL_GET_PROGRAM_RESOURCEIV_H */
