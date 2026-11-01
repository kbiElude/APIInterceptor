/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_PROGRAM_UNIFORM1I_H
#define AI_GL_PROGRAM_UNIFORM1I_H

#include "Interception/Hooks/OpenGL/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            void AI_APIENTRY aiProgramUniform1i(GLuint program,
                                                GLint  location,
                                                GLint  v0);
        }
    }
}

#endif /* AI_GL_PROGRAM_UNIFORM1I_H */
