/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_VERTEX_ATTRIB_P3UI_H
#define AI_GL_VERTEX_ATTRIB_P3UI_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiVertexAttribP3ui(GLuint    index,
                                        GLenum    type,
                                        GLboolean normalized,
                                        GLuint    value);
}

#endif /* AI_GL_VERTEX_ATTRIB_P3UI_H */
