/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_GET_ACTIVE_ATOMIC_COUNTER_BUFFERIV_H
#define AI_GL_GET_ACTIVE_ATOMIC_COUNTER_BUFFERIV_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiGetActiveAtomicCounterBufferiv(GLuint  program,
                                                      GLuint  bufferIndex,
                                                      GLenum  pname,
                                                      GLint*  params);
}

#endif /* AI_GL_GET_ACTIVE_ATOMIC_COUNTER_BUFFERIV_H */
