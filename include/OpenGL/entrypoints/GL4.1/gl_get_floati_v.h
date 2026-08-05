/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_GET_FLOATI_V_H
#define AI_GL_GET_FLOATI_V_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiGetFloati_v(GLenum target, GLuint index, GLfloat* data);
}

#endif /* AI_GL_GET_FLOATI_V_H */
