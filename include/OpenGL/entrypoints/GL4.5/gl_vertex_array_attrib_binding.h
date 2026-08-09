/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_VERTEX_ARRAY_ATTRIB_BINDING_H
#define AI_GL_VERTEX_ARRAY_ATTRIB_BINDING_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiVertexArrayAttribBinding(GLuint vaobj, GLuint attribindex, GLuint bindingindex);
}

#endif /* AI_GL_VERTEX_ARRAY_ATTRIB_BINDING_H */
