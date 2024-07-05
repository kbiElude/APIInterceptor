/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_BEGIN_TRANSFORM_FEEDBACK_H
#define AI_GL_BEGIN_TRANSFORM_FEEDBACK_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiBeginTransformFeedback(GLenum primitiveMode);
}

#endif /* AI_GL_BEGIN_TRANSFORM_FEEDBACK_H */