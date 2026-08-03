/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_MULTI_TEX_COORD_3SV_H
#define AI_GL_MULTI_TEX_COORD_3SV_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiMultiTexCoord3sv(GLenum         target,
                                        const GLshort* v);
}

#endif /* AI_GL_MULTI_TEX_COORD_3SV_H */