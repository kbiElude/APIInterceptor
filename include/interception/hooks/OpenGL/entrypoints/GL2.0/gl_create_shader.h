/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_CREATE_SHADER_H
#define AI_GL_CREATE_SHADER_H

#include "interception/hooks/OpenGL/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            GLuint AI_APIENTRY aiCreateShader(GLenum type);
        }
    }
}

#endif /* AI_GL_CREATE_SHADER_H */