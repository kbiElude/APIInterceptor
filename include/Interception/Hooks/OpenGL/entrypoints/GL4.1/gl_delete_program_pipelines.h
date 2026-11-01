/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_DELETE_PROGRAM_PIPELINES_H
#define AI_GL_DELETE_PROGRAM_PIPELINES_H

#include "Interception/Hooks/OpenGL/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            void AI_APIENTRY aiDeleteProgramPipelines(GLsizei       n,
                                                      const GLuint* pipelines);
        }
    }
}

#endif /* AI_GL_DELETE_PROGRAM_PIPELINES_H */
