/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_GET_DOUBLEV_H
#define AI_GL_GET_DOUBLEV_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiGetDoublev(GLenum    pname,
                                  GLdouble* data);
}

#endif /* AI_GL_GET_DOUBLEV_H */