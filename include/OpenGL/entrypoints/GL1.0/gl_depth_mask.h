/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_DEPTH_MASK_H
#define AI_GL_DEPTH_MASK_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiDepthMask(GLboolean flag);
}

#endif /* AI_GL_DEPTH_MASK_H */