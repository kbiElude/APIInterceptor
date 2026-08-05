/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_GET_INTERNALFORMATI64V_H
#define AI_GL_GET_INTERNALFORMATI64V_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiGetInternalformati64v(GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint64* params);
}

#endif /* AI_GL_GET_INTERNALFORMATI64V_H */
