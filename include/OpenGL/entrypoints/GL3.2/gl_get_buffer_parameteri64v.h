/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_GET_BUFFER_PARAMETERI64V_H
#define AI_GL_GET_BUFFER_PARAMETERI64V_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiGetBufferParameteri64v(GLenum   target,
                                              GLenum   pname,
                                              GLint64* params);
}

#endif /* AI_GL_GET_BUFFER_PARAMETERI64V_H */