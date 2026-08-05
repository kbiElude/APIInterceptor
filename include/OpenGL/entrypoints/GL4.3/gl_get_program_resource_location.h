/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_GET_PROGRAM_RESOURCE_LOCATION_H
#define AI_GL_GET_PROGRAM_RESOURCE_LOCATION_H

#include "OpenGL/types.h"

namespace OpenGL
{
    GLint AI_APIENTRY aiGetProgramResourceLocation(GLuint program, GLenum programInterface, const GLchar* name);
}

#endif /* AI_GL_GET_PROGRAM_RESOURCE_LOCATION_H */
