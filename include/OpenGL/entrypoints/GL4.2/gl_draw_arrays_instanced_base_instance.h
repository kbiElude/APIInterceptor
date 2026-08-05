/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_DRAW_ARRAYS_INSTANCED_BASE_INSTANCE_H
#define AI_GL_DRAW_ARRAYS_INSTANCED_BASE_INSTANCE_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiDrawArraysInstancedBaseInstance(GLenum  mode,
                                                       GLint   first,
                                                       GLsizei count,
                                                       GLsizei instancecount,
                                                       GLuint  baseinstance);
}

#endif /* AI_GL_DRAW_ARRAYS_INSTANCED_BASE_INSTANCE_H */
