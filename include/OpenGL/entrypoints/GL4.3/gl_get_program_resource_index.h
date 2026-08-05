/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_GET_PROGRAM_RESOURCE_INDEX_H
#define AI_GL_GET_PROGRAM_RESOURCE_INDEX_H

#include "OpenGL/types.h"

namespace OpenGL
{
    GLuint AI_APIENTRY aiGetProgramResourceIndex(GLuint program, GLenum programInterface, const GLchar* name);
}

#endif /* AI_GL_GET_PROGRAM_RESOURCE_INDEX_H */
