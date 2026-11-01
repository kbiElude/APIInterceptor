/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_COLOR_4US_H
#define AI_GL_COLOR_4US_H

#include "Interception/Hooks/OpenGL/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            void AI_APIENTRY aiColor4us(GLushort red,
                                        GLushort green,
                                        GLushort blue,
                                        GLushort alpha);
        }
    }
}

#endif /* AI_GL_COLOR_4US_H */