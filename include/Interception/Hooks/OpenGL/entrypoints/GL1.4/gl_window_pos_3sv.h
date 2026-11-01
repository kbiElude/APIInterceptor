/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_WINDOW_POS_3SV_H
#define AI_GL_WINDOW_POS_3SV_H

#include "Interception/Hooks/OpenGL/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            void AI_APIENTRY aiWindowPos3sv(const GLshort* v);
        }
    }
}

#endif /* AI_GL_WINDOW_POS_3SV_H */