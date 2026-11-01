/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_CREATE_TEXTURES_H
#define AI_GL_CREATE_TEXTURES_H

#include "Interception/Hooks/OpenGL/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            void AI_APIENTRY aiCreateTextures(GLenum  target,
                                              GLsizei n,
                                              GLuint* textures);
        }
    }
}

#endif /* AI_GL_CREATE_TEXTURES_H */
