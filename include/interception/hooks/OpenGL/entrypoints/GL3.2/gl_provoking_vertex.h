/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_PROVOKING_VERTEX_H
#define AI_GL_PROVOKING_VERTEX_H

#include "interception/hooks/OpenGL/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            void AI_APIENTRY aiProvokingVertex(GLenum mode);
        }
    }
}

#endif /* AI_GL_PROVOKING_VERTEX_H */