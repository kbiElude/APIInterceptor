/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_CREATE_PROGRAM_H
#define AI_GL_CREATE_PROGRAM_H

#include "Interception/Hooks/OpenGL/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            GLuint AI_APIENTRY aiCreateProgram();
        }
    }
}

#endif /* AI_GL_CREATE_PROGRAM_H */