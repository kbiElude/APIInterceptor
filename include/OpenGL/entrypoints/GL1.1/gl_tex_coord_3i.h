/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_TEX_COORD_3I_H
#define AI_GL_TEX_COORD_3I_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiTexCoord3i(GLint s,
                                  GLint t,
                                  GLint r);
}

#endif /* AI_GL_TEX_COORD_3I_H */