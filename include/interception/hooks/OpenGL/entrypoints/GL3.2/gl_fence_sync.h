/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_FENCE_SYNC_H
#define AI_GL_FENCE_SYNC_H

#include "interception/hooks/OpenGL/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            GLsync AI_APIENTRY aiFenceSync(GLenum     condition,
                                           GLbitfield flags);
        }
    }
}

#endif /* AI_GL_FENCE_SYNC_H */