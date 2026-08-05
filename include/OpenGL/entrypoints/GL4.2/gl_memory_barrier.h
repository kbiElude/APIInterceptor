/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_MEMORY_BARRIER_H
#define AI_GL_MEMORY_BARRIER_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiMemoryBarrier(GLbitfield barriers);
}

#endif /* AI_GL_MEMORY_BARRIER_H */
