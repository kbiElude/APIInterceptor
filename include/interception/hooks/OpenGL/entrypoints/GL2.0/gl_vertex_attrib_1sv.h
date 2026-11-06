/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_VERTEX_ATTRIB_1SV_H
#define AI_GL_VERTEX_ATTRIB_1SV_H

#include "interception/hooks/OpenGL/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            void AI_APIENTRY aiVertexAttrib1sv(GLuint         index,
                                               const GLshort* v);
        }
    }
}

#endif /* AI_GL_VERTEX_ATTRIB_1SV_H */