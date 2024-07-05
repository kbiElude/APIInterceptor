/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_DRAW_ARRAYS_INSTANCED_H
#define AI_GL_DRAW_ARRAYS_INSTANCED_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiDrawArraysInstanced(GLenum  mode,
                                           GLint   first,
                                           GLsizei count,
                                           GLsizei instancecount);
}

#endif /* AI_GL_DRAW_ARRAYS_INSTANCED_H */