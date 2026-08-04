/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_GET_QUERY_OBJECTI64V_H
#define AI_GL_GET_QUERY_OBJECTI64V_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiGetQueryObjecti64v(GLuint   id,
                                          GLenum   pname,
                                          GLint64* params);
}

#endif /* AI_GL_GET_QUERY_OBJECTI64V_H */
