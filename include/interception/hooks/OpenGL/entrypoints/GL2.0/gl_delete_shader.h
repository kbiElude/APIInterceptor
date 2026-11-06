/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_DELETE_SHADER_H
#define AI_GL_DELETE_SHADER_H

#include "interception/hooks/OpenGL/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            void AI_APIENTRY aiDeleteShader(GLuint shader);
        }
    }
}

#endif /* AI_GL_DELETE_SHADER_H */