/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_GET_PROGRAM_INTERFACEIV_H
#define AI_GL_GET_PROGRAM_INTERFACEIV_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiGetProgramInterfaceiv(GLuint program, GLenum programInterface, GLenum pname, GLint* params);
}

#endif /* AI_GL_GET_PROGRAM_INTERFACEIV_H */
