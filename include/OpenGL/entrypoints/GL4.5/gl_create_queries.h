/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_CREATE_QUERIES_H
#define AI_GL_CREATE_QUERIES_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiCreateQueries(GLenum target, GLsizei n, GLuint* ids);
}

#endif /* AI_GL_CREATE_QUERIES_H */
