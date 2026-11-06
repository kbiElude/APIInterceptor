/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_VERTEX_ARRAY_BINDING_DIVISOR_H
#define AI_GL_VERTEX_ARRAY_BINDING_DIVISOR_H

#include "interception/hooks/OpenGL/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            void AI_APIENTRY aiVertexArrayBindingDivisor(GLuint vaobj,
                                                         GLuint bindingindex,
                                                         GLuint divisor);
        }
    }
}

#endif /* AI_GL_VERTEX_ARRAY_BINDING_DIVISOR_H */
