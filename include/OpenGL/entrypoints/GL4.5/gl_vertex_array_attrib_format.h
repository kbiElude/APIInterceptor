/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_VERTEX_ARRAY_ATTRIB_FORMAT_H
#define AI_GL_VERTEX_ARRAY_ATTRIB_FORMAT_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiVertexArrayAttribFormat(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset);
}

#endif /* AI_GL_VERTEX_ARRAY_ATTRIB_FORMAT_H */
