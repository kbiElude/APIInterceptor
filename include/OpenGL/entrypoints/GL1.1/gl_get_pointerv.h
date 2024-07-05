/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_GET_POINTERV_H
#define AI_GL_GET_POINTERV_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiGetPointerv(GLenum   pname,
                                   GLvoid** params);
}

#endif /* AI_GL_GET_POINTERV_H */