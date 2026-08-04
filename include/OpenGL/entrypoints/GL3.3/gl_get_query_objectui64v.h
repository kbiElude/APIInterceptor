/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_GET_QUERY_OBJECTUI64V_H
#define AI_GL_GET_QUERY_OBJECTUI64V_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiGetQueryObjectui64v(GLuint    id,
                                           GLenum    pname,
                                           GLuint64* params);
}

#endif /* AI_GL_GET_QUERY_OBJECTUI64V_H */
