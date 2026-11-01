/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_VERTEX_ATTRIB_4NUBV_H
#define AI_GL_VERTEX_ATTRIB_4NUBV_H

#include "Interception/Hooks/OpenGL/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            void AI_APIENTRY aiVertexAttrib4Nubv(GLuint         index,
                                                 const GLubyte* v);
        }
    }
}

#endif /* AI_GL_VERTEX_ATTRIB_4NUBV_H */