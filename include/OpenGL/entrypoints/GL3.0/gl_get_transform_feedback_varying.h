/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_GET_TRANSFORM_FEEDBACK_VARYING_H
#define AI_GL_GET_TRANSFORM_FEEDBACK_VARYING_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiGetTransformFeedbackVarying(GLuint   program,
                                                   GLuint   index,
                                                   GLsizei  bufSize,
                                                   GLsizei* length,
                                                   GLsizei* size,
                                                   GLenum*  type,
                                                   GLchar*  name);
}

#endif /* AI_GL_GET_TRANSFORM_FEEDBACK_VARYING_H */