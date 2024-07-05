/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_GET_VERTEX_ATTRIBIV_H
#define AI_GL_GET_VERTEX_ATTRIBIV_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiGetVertexAttribiv(GLuint index,
                                         GLenum pname,
                                         GLint* params);
}

#endif /* AI_GL_GET_VERTEX_ATTRIBIV_H */