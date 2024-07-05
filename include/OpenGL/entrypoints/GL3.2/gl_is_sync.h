/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_IS_SYNC_H
#define AI_GL_IS_SYNC_H

#include "OpenGL/types.h"

namespace OpenGL
{
    GLboolean AI_APIENTRY aiIsSync(GLsync sync);
}

#endif /* AI_GL_IS_SYNC_H */