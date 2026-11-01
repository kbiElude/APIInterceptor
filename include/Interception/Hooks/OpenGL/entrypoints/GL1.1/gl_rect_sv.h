/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_RECT_SV_H
#define AI_GL_RECT_SV_H

#include "Interception/Hooks/OpenGL/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            void AI_APIENTRY aiRectsv(const GLshort* v1,
                                      const GLshort* v2);
        }
    }
}

#endif /* AI_GL_RECT_SV_H */