/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_MULTI_TEX_COORD_2S_H
#define AI_GL_MULTI_TEX_COORD_2S_H

#include "Interception/Hooks/OpenGL/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            void AI_APIENTRY aiMultiTexCoord2s(GLenum  target,
                                               GLshort s,
                                               GLshort t);
        }
    }
}

#endif /* AI_GL_MULTI_TEX_COORD_2S_H */