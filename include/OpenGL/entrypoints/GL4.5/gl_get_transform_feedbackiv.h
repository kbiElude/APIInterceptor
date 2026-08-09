/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_GET_TRANSFORM_FEEDBACKIV_H
#define AI_GL_GET_TRANSFORM_FEEDBACKIV_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiGetTransformFeedbackiv(GLuint xfb, GLenum pname, GLint* param);
}

#endif /* AI_GL_GET_TRANSFORM_FEEDBACKIV_H */
