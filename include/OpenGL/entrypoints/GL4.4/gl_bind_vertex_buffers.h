/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_BIND_VERTEX_BUFFERS_H
#define AI_GL_BIND_VERTEX_BUFFERS_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiBindVertexBuffers(GLuint           first,
                                         GLsizei          count,
                                         const GLuint*    buffers,
                                         const GLintptr*  offsets,
                                         const GLsizei*   strides);
}

#endif /* AI_GL_BIND_VERTEX_BUFFERS_H */
