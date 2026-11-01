/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_VERTEX_ATTRIB_4BV_H
#define AI_GL_VERTEX_ATTRIB_4BV_H

#include "Interception/Hooks/OpenGL/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            void AI_APIENTRY aiVertexAttrib4bv(GLuint        index,
                                               const GLbyte* v);
        }
    }
}

#endif /* AI_GL_VERTEX_ATTRIB_4BV_H */