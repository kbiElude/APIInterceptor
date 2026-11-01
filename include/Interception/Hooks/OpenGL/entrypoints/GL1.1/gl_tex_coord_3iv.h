/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_TEX_COORD_3IV_H
#define AI_GL_TEX_COORD_3IV_H

#include "Interception/Hooks/OpenGL/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            void AI_APIENTRY aiTexCoord3iv(const GLint* v);
        }
    }
}

#endif /* AI_GL_TEX_COORD_3IV_H */