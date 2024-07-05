/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_MULTI_DRAW_ELEMENTS_H
#define AI_GL_MULTI_DRAW_ELEMENTS_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiMultiDrawElements(GLenum             mode,
                                         const GLsizei*     count,
                                         GLenum             type,
                                         const void* const* indices,
                                         GLsizei            drawcount);
}

#endif /* AI_GL_MULTI_DRAW_ELEMENTS_H */