/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_GET_VERTEX_ATTRIB_LDV_H
#define AI_GL_GET_VERTEX_ATTRIB_LDV_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiGetVertexAttribLdv(GLuint index, GLenum pname, GLdouble* params);
}

#endif /* AI_GL_GET_VERTEX_ATTRIB_LDV_H */
