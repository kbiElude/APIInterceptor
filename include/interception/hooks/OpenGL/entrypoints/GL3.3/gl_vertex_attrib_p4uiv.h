/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_VERTEX_ATTRIB_P4UIV_H
#define AI_GL_VERTEX_ATTRIB_P4UIV_H

#include "interception/hooks/OpenGL/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            void AI_APIENTRY aiVertexAttribP4uiv(GLuint        index,
                                                 GLenum        type,
                                                 GLboolean     normalized,
                                                 const GLuint* value);
        }
    }
}

#endif /* AI_GL_VERTEX_ATTRIB_P4UIV_H */
