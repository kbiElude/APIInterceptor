/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_GET_QUERY_BUFFER_OBJECTUI64V_H
#define AI_GL_GET_QUERY_BUFFER_OBJECTUI64V_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiGetQueryBufferObjectui64v(GLuint id, GLuint buffer, GLenum pname, GLintptr offset);
}

#endif /* AI_GL_GET_QUERY_BUFFER_OBJECTUI64V_H */
