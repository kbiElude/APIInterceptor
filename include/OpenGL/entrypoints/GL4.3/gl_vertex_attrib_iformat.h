/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_VERTEX_ATTRIB_IFORMAT_H
#define AI_GL_VERTEX_ATTRIB_IFORMAT_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiVertexAttribIFormat(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
}

#endif /* AI_GL_VERTEX_ATTRIB_IFORMAT_H */
