/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_FEEDBACK_BUFFER_H
#define AI_GL_FEEDBACK_BUFFER_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiFeedbackBuffer(GLsizei  size,
                                      GLenum   type,
                                      GLfloat* buffer);
}

#endif /* AI_GL_FEEDBACK_BUFFER_H */