/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_TEX_COORD_2DV_H
#define AI_GL_TEX_COORD_2DV_H

#include "Interception/Hooks/OpenGL/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            void AI_APIENTRY aiTexCoord2dv(const GLdouble* v);
        }
    }
}

#endif /* AI_GL_TEX_COORD_2DV_H */