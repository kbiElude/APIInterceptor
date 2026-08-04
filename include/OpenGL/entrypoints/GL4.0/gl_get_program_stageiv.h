/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_GET_PROGRAM_STAGEIV_H
#define AI_GL_GET_PROGRAM_STAGEIV_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiGetProgramStageiv(GLuint program, GLenum shadertype, GLenum pname, GLint* values);
}

#endif /* AI_GL_GET_PROGRAM_STAGEIV_H */
