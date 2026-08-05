/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_SHADER_BINARY_H
#define AI_GL_SHADER_BINARY_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiShaderBinary(GLsizei count, const GLuint* shaders, GLenum binaryformat, const void* binary, GLsizei length);
}

#endif /* AI_GL_SHADER_BINARY_H */
