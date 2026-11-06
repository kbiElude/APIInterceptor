/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_VERTEX_ATTRIB_I_2I_H
#define AI_GL_VERTEX_ATTRIB_I_2I_H

#include "interception/hooks/OpenGL/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            void AI_APIENTRY aiVertexAttribI2i(GLuint index,
                                               GLint  x,
                                               GLint  y);
        }
    }
}

#endif /* AI_GL_VERTEX_ATTRIB_I_2I_H */