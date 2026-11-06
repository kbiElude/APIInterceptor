/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_TEX_COORD_2S_H
#define AI_GL_TEX_COORD_2S_H

#include "interception/hooks/OpenGL/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            void AI_APIENTRY aiTexCoord2s(GLshort s,
                                          GLshort t);
        }
    }
}

#endif /* AI_GL_TEX_COORD_2S_H */