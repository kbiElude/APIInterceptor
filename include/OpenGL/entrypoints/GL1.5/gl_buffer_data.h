/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_BUFFER_DATA_H
#define AI_GL_BUFFER_DATA_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiBufferData(GLenum      target,
                                  GLsizeiptr  size,
                                  const void* data,
                                  GLenum      usage);
}

#endif /* AI_GL_BUFFER_DATA_H */