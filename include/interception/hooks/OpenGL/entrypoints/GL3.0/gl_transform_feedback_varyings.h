/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_TRANSFORM_FEEDBACK_VARYINGS_H
#define AI_GL_TRANSFORM_FEEDBACK_VARYINGS_H

#include "interception/hooks/OpenGL/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            void AI_APIENTRY aiTransformFeedbackVaryings(GLuint               program,
                                                         GLsizei              count,
                                                         const GLchar* const* varyings,
                                                         GLenum               bufferMode);
        }
    }
}

#endif /* AI_GL_TRANSFORM_FEEDBACK_VARYINGS_H */