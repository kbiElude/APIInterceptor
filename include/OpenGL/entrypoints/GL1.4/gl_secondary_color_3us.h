/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_SECONDARY_COLOR_3US_H
#define AI_GL_SECONDARY_COLOR_3US_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiSecondaryColor3us(GLushort red,
                                         GLushort green,
                                         GLushort blue);
}

#endif /* AI_GL_SECONDARY_COLOR_3US_H */