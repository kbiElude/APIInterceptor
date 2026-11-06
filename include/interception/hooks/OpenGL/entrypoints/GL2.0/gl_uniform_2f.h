/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_UNIFORM_2F_H
#define AI_GL_UNIFORM_2F_H

#include "interception/hooks/OpenGL/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            void AI_APIENTRY aiUniform2f(GLint   location,
                                         GLfloat v0,
                                         GLfloat v1);
        }
    }
}

#endif /* AI_GL_UNIFORM_2F_H */