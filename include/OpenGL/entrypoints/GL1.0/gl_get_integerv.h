/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_GET_INTEGERV_H
#define AI_GL_GET_INTEGERV_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiGetIntegerv(GLenum pname,
                                   GLint* data);
}

#endif /* AI_GL_GET_INTEGERV_H */