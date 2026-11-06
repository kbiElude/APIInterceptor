/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_VIEWPORT_INDEXEDF_H
#define AI_GL_VIEWPORT_INDEXEDF_H

#include "interception/hooks/OpenGL/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            void AI_APIENTRY aiViewportIndexedf(GLuint  index,
                                                GLfloat x,
                                                GLfloat y,
                                                GLfloat w,
                                                GLfloat h);
        }
    }
}

#endif /* AI_GL_VIEWPORT_INDEXEDF_H */
