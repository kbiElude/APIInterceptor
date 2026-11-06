/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_MULTI_TEX_COORD_3D_H
#define AI_GL_MULTI_TEX_COORD_3D_H

#include "interception/hooks/OpenGL/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            void AI_APIENTRY aiMultiTexCoord3d(GLenum   target,
                                               GLdouble s,
                                               GLdouble t,
                                               GLdouble r);
        }
    }
}

#endif /* AI_GL_MULTI_TEX_COORD_3D_H */