/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_VERTEX_ATTRIB_2S_H
#define AI_GL_VERTEX_ATTRIB_2S_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiVertexAttrib2s(GLuint  index,
                                      GLshort x,
                                      GLshort y);
}

#endif /* AI_GL_VERTEX_ATTRIB_2S_H */