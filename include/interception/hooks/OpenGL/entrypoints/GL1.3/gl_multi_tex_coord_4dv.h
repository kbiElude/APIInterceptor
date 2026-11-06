/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_MULTI_TEX_COORD_4DV_H
#define AI_GL_MULTI_TEX_COORD_4DV_H

#include "interception/hooks/OpenGL/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            void AI_APIENTRY aiMultiTexCoord4dv(GLenum          target,
                                                const GLdouble* v);
        }
    }
}

#endif /* AI_GL_MULTI_TEX_COORD_4DV_H */