/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_DEPTH_RANGE_ARRAYV_H
#define AI_GL_DEPTH_RANGE_ARRAYV_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiDepthRangeArrayv(GLuint first, GLsizei count, const GLdouble* v);
}

#endif /* AI_GL_DEPTH_RANGE_ARRAYV_H */
