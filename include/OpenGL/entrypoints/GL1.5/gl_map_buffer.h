/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_MAP_BUFFER_H
#define AI_GL_MAP_BUFFER_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void *AI_APIENTRY aiMapBuffer(GLenum target,
                                  GLenum access);
}

#endif /* AI_GL_MAP_BUFFER_H */