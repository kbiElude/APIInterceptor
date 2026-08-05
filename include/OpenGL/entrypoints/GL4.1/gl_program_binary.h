/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_PROGRAM_BINARY_H
#define AI_GL_PROGRAM_BINARY_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiProgramBinary(GLuint program, GLenum binaryFormat, const void* binary, GLsizei length);
}

#endif /* AI_GL_PROGRAM_BINARY_H */
