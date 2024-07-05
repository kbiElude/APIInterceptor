/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_COPY_BUFFER_SUB_DATA_H
#define AI_GL_COPY_BUFFER_SUB_DATA_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiCopyBufferSubData(GLenum     readTarget,
                                         GLenum     writeTarget,
                                         GLintptr   readOffset,
                                         GLintptr   writeOffset,
                                         GLsizeiptr size);
}

#endif /* AI_GL_COPY_BUFFER_SUB_DATA_H */