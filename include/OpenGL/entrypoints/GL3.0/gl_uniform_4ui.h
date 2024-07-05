/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_UNIFORM_4UI_H
#define AI_GL_UNIFORM_4UI_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiUniform4ui(GLint  location,
                                  GLuint v0,
                                  GLuint v1,
                                  GLuint v2,
                                  GLuint v3);
}

#endif /* AI_GL_UNIFORM_4UI_H */