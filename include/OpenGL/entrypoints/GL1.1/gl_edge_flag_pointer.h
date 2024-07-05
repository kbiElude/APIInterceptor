/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_EDGE_FLAG_POINTER_H
#define AI_GL_EDGE_FLAG_POINTER_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiEdgeFlagPointer(GLsizei       stride,
                                       const GLvoid* pointer);
}

#endif /* AI_GL_EDGE_FLAG_POINTER_H */