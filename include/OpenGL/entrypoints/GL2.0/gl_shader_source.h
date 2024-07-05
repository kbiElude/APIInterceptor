/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_SHADER_SOURCE_H
#define AI_GL_SHADER_SOURCE_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiShaderSource(GLuint               shader,
                                    GLsizei              count,
                                    const GLchar* const* string,
                                    const GLint*         length);
}

#endif /* AI_GL_SHADER_SOURCE_H */