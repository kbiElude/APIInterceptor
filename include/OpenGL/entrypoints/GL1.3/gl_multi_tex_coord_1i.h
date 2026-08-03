/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_MULTI_TEX_COORD_1I_H
#define AI_GL_MULTI_TEX_COORD_1I_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiMultiTexCoord1i(GLenum target,
                                       GLint  s);
}

#endif /* AI_GL_MULTI_TEX_COORD_1I_H */