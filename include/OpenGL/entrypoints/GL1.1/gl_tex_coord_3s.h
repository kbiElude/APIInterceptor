/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_TEX_COORD_3S_H
#define AI_GL_TEX_COORD_3S_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiTexCoord3s(GLshort s,
                                  GLshort t,
                                  GLshort r);
}

#endif /* AI_GL_TEX_COORD_3S_H */