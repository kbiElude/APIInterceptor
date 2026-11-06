/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_DRAW_ARRAYS_INDIRECT_H
#define AI_GL_DRAW_ARRAYS_INDIRECT_H

#include "interception/hooks/OpenGL/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            void AI_APIENTRY aiDrawArraysIndirect(GLenum      mode,
                                                  const void* indirect);
        }
    }
}

#endif /* AI_GL_DRAW_ARRAYS_INDIRECT_H */
