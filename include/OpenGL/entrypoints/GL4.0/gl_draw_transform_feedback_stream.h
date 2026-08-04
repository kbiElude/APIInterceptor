/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_DRAW_TRANSFORM_FEEDBACK_STREAM_H
#define AI_GL_DRAW_TRANSFORM_FEEDBACK_STREAM_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiDrawTransformFeedbackStream(GLenum mode, GLuint id, GLuint stream);
}

#endif /* AI_GL_DRAW_TRANSFORM_FEEDBACK_STREAM_H */
