/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_ACTIVE_SHADER_PROGRAM_H
#define AI_GL_ACTIVE_SHADER_PROGRAM_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiActiveShaderProgram(GLuint pipeline, GLuint program);
}

#endif /* AI_GL_ACTIVE_SHADER_PROGRAM_H */
