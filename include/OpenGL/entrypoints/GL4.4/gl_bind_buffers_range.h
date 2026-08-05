/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_BIND_BUFFERS_RANGE_H
#define AI_GL_BIND_BUFFERS_RANGE_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiBindBuffersRange(GLenum           target,
                                        GLuint           first,
                                        GLsizei          count,
                                        const GLuint*    buffers,
                                        const GLintptr*  offsets,
                                        const GLsizeiptr* sizes);
}

#endif /* AI_GL_BIND_BUFFERS_RANGE_H */
