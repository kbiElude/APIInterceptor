/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_GET_VERTEX_ARRAY_INDEXED64IV_H
#define AI_GL_GET_VERTEX_ARRAY_INDEXED64IV_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiGetVertexArrayIndexed64iv(GLuint vaobj, GLuint index, GLenum pname, GLint64* param);
}

#endif /* AI_GL_GET_VERTEX_ARRAY_INDEXED64IV_H */
