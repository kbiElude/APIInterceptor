/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_BIND_TEXTURES_H
#define AI_GL_BIND_TEXTURES_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiBindTextures(GLuint        first,
                                    GLsizei       count,
                                    const GLuint* textures);
}

#endif /* AI_GL_BIND_TEXTURES_H */
