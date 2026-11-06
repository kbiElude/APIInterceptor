/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_SECONDARY_COLOR_3USV_H
#define AI_GL_SECONDARY_COLOR_3USV_H

#include "interception/hooks/OpenGL/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            void AI_APIENTRY aiSecondaryColor3usv(const GLushort* v);
        }
    }
}

#endif /* AI_GL_SECONDARY_COLOR_3USV_H */