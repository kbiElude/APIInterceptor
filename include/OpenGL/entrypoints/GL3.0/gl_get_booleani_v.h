/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_GET_BOOLEANI_V_H
#define AI_GL_GET_BOOLEANI_V_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiGetBooleani_v(GLenum     target,
                                     GLuint     index,
                                     GLboolean* data);
}

#endif /* AI_GL_GET_BOOLEANI_V_H */