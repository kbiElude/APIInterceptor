/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_MULTI_TEX_COORD_4FV_H
#define AI_GL_MULTI_TEX_COORD_4FV_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiMultiTexCoord4fv(GLenum         target,
                                        const GLfloat* v);
}

#endif /* AI_GL_MULTI_TEX_COORD_4FV_H */