/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_PRIORITIZE_TEXTURES_H
#define AI_GL_PRIORITIZE_TEXTURES_H

#include "Interception/Hooks/OpenGL/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            void AI_APIENTRY aiPrioritizeTextures(GLsizei         n,
                                                  const GLuint*   textures,
                                                  const GLclampf* priorities);
        }
    }
}

#endif /* AI_GL_PRIORITIZE_TEXTURES_H */