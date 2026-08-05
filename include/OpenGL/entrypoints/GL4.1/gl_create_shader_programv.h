/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_CREATE_SHADER_PROGRAMV_H
#define AI_GL_CREATE_SHADER_PROGRAMV_H

#include "OpenGL/types.h"

namespace OpenGL
{
    GLuint AI_APIENTRY aiCreateShaderProgramv(GLenum type, GLsizei count, const GLchar* const* strings);
}

#endif /* AI_GL_CREATE_SHADER_PROGRAMV_H */
