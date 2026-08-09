/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_GET_TRANSFORM_FEEDBACKI64_V_H
#define AI_GL_GET_TRANSFORM_FEEDBACKI64_V_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiGetTransformFeedbacki64_v(GLuint xfb, GLenum pname, GLuint index, GLint64* param);
}

#endif /* AI_GL_GET_TRANSFORM_FEEDBACKI64_V_H */
