/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_FRUSTUM_H
#define AI_GL_FRUSTUM_H

#include "Interception/Hooks/OpenGL/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            void AI_APIENTRY aiFrustum(GLdouble left,
                                       GLdouble right,
                                       GLdouble bottom,
                                       GLdouble top,
                                       GLdouble zNear,
                                       GLdouble zFar);
        }
    }
}

#endif /* AI_GL_FRUSTUM_H */