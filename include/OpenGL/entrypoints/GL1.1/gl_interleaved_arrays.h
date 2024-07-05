/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_INTERLEAVED_ARRAYS_H
#define AI_GL_INTERLEAVED_ARRAYS_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiInterleavedArrays(GLenum        format,
                                         GLsizei       stride,
                                         const GLvoid* pointer);
}

#endif /* AI_GL_INTERLEAVED_ARRAYS_H */