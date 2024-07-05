/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_WAIT_SYNC_H
#define AI_GL_WAIT_SYNC_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiWaitSync(GLsync     sync,
                                GLbitfield flags,
                                GLuint64   timeout);
}

#endif /* AI_GL_WAIT_SYNC_H */