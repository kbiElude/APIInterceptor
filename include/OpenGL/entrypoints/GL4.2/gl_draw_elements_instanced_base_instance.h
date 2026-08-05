/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_DRAW_ELEMENTS_INSTANCED_BASE_INSTANCE_H
#define AI_GL_DRAW_ELEMENTS_INSTANCED_BASE_INSTANCE_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiDrawElementsInstancedBaseInstance(GLenum      mode,
                                                         GLsizei     count,
                                                         GLenum      type,
                                                         const void* indices,
                                                         GLsizei     instancecount,
                                                         GLuint      baseinstance);
}

#endif /* AI_GL_DRAW_ELEMENTS_INSTANCED_BASE_INSTANCE_H */
