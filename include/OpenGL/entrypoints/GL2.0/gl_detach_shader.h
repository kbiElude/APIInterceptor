/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_DETACH_SHADER_H
#define AI_GL_DETACH_SHADER_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiDetachShader(GLuint program,
                                    GLuint shader);
}

#endif /* AI_GL_DETACH_SHADER_H */