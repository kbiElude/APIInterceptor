/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_UNIFORM_3UIV_H
#define AI_GL_UNIFORM_3UIV_H

#include "Interception/Hooks/OpenGL/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            void AI_APIENTRY aiUniform3uiv(GLint         location,
                                           GLsizei       count,
                                           const GLuint* value);
        }
    }
}

#endif /* AI_GL_UNIFORM_3UIV_H */