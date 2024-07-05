/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_DELETE_LISTS_H
#define AI_GL_DELETE_LISTS_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiDeleteLists(GLuint  list,
                                   GLsizei range);
}

#endif /* AI_GL_DELETE_LISTS_H */