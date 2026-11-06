/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_GET_UNIFORM_LOCATION_H
#define AI_GL_GET_UNIFORM_LOCATION_H

#include "interception/hooks/OpenGL/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            GLint AI_APIENTRY aiGetUniformLocation(GLuint        program,
                                                   const GLchar* name);
        }
    }
}

#endif /* AI_GL_GET_UNIFORM_LOCATION_H */