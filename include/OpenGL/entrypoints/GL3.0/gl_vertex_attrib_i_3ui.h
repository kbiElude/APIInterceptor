/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_VERTEX_ATTRIB_I_3UI_H
#define AI_GL_VERTEX_ATTRIB_I_3UI_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiVertexAttribI3ui(GLuint index,
                                        GLuint x,
                                        GLuint y,
                                        GLuint z);
}

#endif /* AI_GL_VERTEX_ATTRIB_I_3UI_H */