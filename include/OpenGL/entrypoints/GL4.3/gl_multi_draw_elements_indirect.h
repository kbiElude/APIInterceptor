/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_MULTI_DRAW_ELEMENTS_INDIRECT_H
#define AI_GL_MULTI_DRAW_ELEMENTS_INDIRECT_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiMultiDrawElementsIndirect(GLenum mode, GLenum type, const void* indirect, GLsizei drawcount, GLsizei stride);
}

#endif /* AI_GL_MULTI_DRAW_ELEMENTS_INDIRECT_H */
