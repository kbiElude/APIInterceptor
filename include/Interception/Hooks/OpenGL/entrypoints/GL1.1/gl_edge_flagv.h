/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_EDGE_FLAGV_H
#define AI_GL_EDGE_FLAGV_H

#include "Interception/Hooks/OpenGL/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            void AI_APIENTRY aiEdgeFlagv(const GLboolean *flag);
        }
    }
}

#endif /* AI_GL_EDGE_FLAGV_H */