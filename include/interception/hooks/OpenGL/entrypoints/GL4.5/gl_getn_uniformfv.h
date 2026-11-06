/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_GETN_UNIFORMFV_H
#define AI_GL_GETN_UNIFORMFV_H

#include "interception/hooks/OpenGL/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            void AI_APIENTRY aiGetnUniformfv(GLuint   program,
                                             GLint    location,
                                             GLsizei  bufSize,
                                             GLfloat* params);
        }
    }
}

#endif /* AI_GL_GETN_UNIFORMFV_H */
