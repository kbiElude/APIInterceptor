/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_PROGRAM_UNIFORM1UI_H
#define AI_GL_PROGRAM_UNIFORM1UI_H

#include "interception/hooks/OpenGL/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            void AI_APIENTRY aiProgramUniform1ui(GLuint program,
                                                 GLint  location,
                                                 GLuint v0);
        }
    }
}

#endif /* AI_GL_PROGRAM_UNIFORM1UI_H */
