/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_GET_SHADER_INFO_LOG_H
#define AI_GL_GET_SHADER_INFO_LOG_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiGetShaderInfoLog(GLuint   shader,
                                        GLsizei  bufSize,
                                        GLsizei* length,
                                        GLchar*  infoLog);
}

#endif /* AI_GL_GET_SHADER_INFO_LOG_H */