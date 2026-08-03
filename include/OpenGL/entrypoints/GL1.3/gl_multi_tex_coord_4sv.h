/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_MULTI_TEX_COORD_4SV_H
#define AI_GL_MULTI_TEX_COORD_4SV_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiMultiTexCoord4sv(GLenum         target,
                                        const GLshort* v);
}

#endif /* AI_GL_MULTI_TEX_COORD_4SV_H */