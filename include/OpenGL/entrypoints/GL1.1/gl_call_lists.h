/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_CALL_LISTS_H
#define AI_GL_CALL_LISTS_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiCallLists(GLsizei       n,
                                 GLenum        type,
                                 const GLvoid* lists);
}

#endif /* AI_GL_CALL_LISTS_H */