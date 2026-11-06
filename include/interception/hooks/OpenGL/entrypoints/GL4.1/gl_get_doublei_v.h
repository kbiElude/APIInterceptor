/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_GET_DOUBLEI_V_H
#define AI_GL_GET_DOUBLEI_V_H

#include "interception/hooks/OpenGL/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            void AI_APIENTRY aiGetDoublei_v(GLenum    target,
                                            GLuint    index,
                                            GLdouble* data);
        }
    }
}

#endif /* AI_GL_GET_DOUBLEI_V_H */
