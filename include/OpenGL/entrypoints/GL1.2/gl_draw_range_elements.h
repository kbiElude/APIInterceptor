/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_DRAW_RANGE_ELEMENTS_H
#define AI_GL_DRAW_RANGE_ELEMENTS_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiDrawRangeElements(GLenum      mode,
                                         GLuint      start,
                                         GLuint      end,
                                         GLsizei     count,
                                         GLenum      type,
                                         const void* indices);
}

#endif /* AI_GL_DRAW_RANGE_ELEMENTS_H */