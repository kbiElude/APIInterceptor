/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_TEX_COORD_4S_H
#define AI_GL_TEX_COORD_4S_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiTexCoord4s(GLshort s,
                                  GLshort t,
                                  GLshort r,
                                  GLshort q);
}

#endif /* AI_GL_TEX_COORD_4S_H */