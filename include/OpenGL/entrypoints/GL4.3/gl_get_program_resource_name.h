/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_GET_PROGRAM_RESOURCE_NAME_H
#define AI_GL_GET_PROGRAM_RESOURCE_NAME_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiGetProgramResourceName(GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei* length, GLchar* name);
}

#endif /* AI_GL_GET_PROGRAM_RESOURCE_NAME_H */
