/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_DISPATCH_COMPUTE_H
#define AI_GL_DISPATCH_COMPUTE_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiDispatchCompute(GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z);
}

#endif /* AI_GL_DISPATCH_COMPUTE_H */
