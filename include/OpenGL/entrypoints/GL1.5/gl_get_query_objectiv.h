/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_GET_QUERY_OBJECTIV_H
#define AI_GL_GET_QUERY_OBJECTIV_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiGetQueryObjectiv(GLuint id,
                                        GLenum pname,
                                        GLint* params);
}

#endif /* AI_GL_GET_QUERY_OBJECTIV_H */