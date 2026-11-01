/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_GET_QUERY_OBJECTUIV_H
#define AI_GL_GET_QUERY_OBJECTUIV_H

#include "Interception/Hooks/OpenGL/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            void AI_APIENTRY aiGetQueryObjectuiv(GLuint  id,
                                                 GLenum  pname,
                                                 GLuint* params);
        }
    }
}

#endif /* AI_GL_GET_QUERY_OBJECTUIV_H */