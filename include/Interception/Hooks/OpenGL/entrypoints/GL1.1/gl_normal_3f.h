/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_NORMAL_3F_H
#define AI_GL_NORMAL_3F_H

#include "Interception/Hooks/OpenGL/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            void AI_APIENTRY aiNormal3f(GLfloat nx,
                                        GLfloat ny,
                                        GLfloat nz);
        }
    }
}

#endif /* AI_GL_NORMAL_3F_H */