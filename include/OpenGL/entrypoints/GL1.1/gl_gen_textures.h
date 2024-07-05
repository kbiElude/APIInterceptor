/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_GEN_TEXTURES_H
#define AI_GL_GEN_TEXTURES_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiGenTextures(GLsizei n,
                                   GLuint* textures);
}

#endif /* AI_GL_GEN_TEXTURES_H */