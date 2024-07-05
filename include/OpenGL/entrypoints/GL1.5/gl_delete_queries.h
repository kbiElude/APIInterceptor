/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_DELETE_QUERIES_H
#define AI_GL_DELETE_QUERIES_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiDeleteQueries(GLsizei       n,
                                     const GLuint* ids);
}

#endif /* AI_GL_DELETE_QUERIES_H */