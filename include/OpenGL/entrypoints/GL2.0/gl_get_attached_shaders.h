/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_GET_ATTACHED_SHADERS_H
#define AI_GL_GET_ATTACHED_SHADERS_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiGetAttachedShaders(GLuint   program,
                                          GLsizei  maxCount,
                                          GLsizei* count,
                                          GLuint*  shaders);
}

#endif /* AI_GL_GET_ATTACHED_SHADERS_H */