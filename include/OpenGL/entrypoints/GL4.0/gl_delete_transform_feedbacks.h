/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_DELETE_TRANSFORM_FEEDBACKS_H
#define AI_GL_DELETE_TRANSFORM_FEEDBACKS_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiDeleteTransformFeedbacks(GLsizei n, const GLuint* ids);
}

#endif /* AI_GL_DELETE_TRANSFORM_FEEDBACKS_H */
