/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_MAP_BUFFER_RANGE_H
#define AI_GL_MAP_BUFFER_RANGE_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void *AI_APIENTRY aiMapBufferRange(GLenum     target,
                                       GLintptr   offset,
                                       GLsizeiptr length,
                                       GLbitfield access);
}


#endif /* AI_GL_MAP_BUFFER_RANGE_H */