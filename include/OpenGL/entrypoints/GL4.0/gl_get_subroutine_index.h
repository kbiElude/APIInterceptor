/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_GET_SUBROUTINE_INDEX_H
#define AI_GL_GET_SUBROUTINE_INDEX_H

#include "OpenGL/types.h"

namespace OpenGL
{
    GLuint AI_APIENTRY aiGetSubroutineIndex(GLuint program, GLenum shadertype, const GLchar* name);
}

#endif /* AI_GL_GET_SUBROUTINE_INDEX_H */
