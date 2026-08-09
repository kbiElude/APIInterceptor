/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_GET_VERTEX_ARRAYIV_H
#define AI_GL_GET_VERTEX_ARRAYIV_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiGetVertexArrayiv(GLuint vaobj, GLenum pname, GLint* param);
}

#endif /* AI_GL_GET_VERTEX_ARRAYIV_H */
