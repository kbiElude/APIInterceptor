/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_VERTEX_ATTRIB_LFORMAT_H
#define AI_GL_VERTEX_ATTRIB_LFORMAT_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiVertexAttribLFormat(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
}

#endif /* AI_GL_VERTEX_ATTRIB_LFORMAT_H */
