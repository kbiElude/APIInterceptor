/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_GET_PROGRAM_BINARY_H
#define AI_GL_GET_PROGRAM_BINARY_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiGetProgramBinary(GLuint program, GLsizei bufSize, GLsizei* length, GLenum* binaryFormat, void* binary);
}

#endif /* AI_GL_GET_PROGRAM_BINARY_H */
