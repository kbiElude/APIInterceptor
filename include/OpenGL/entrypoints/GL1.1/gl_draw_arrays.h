/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_DRAW_ARRAYS_H
#define AI_GL_DRAW_ARRAYS_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiDrawArrays(GLenum  mode,
                                  GLint   first,
                                  GLsizei count);
}

#endif /* AI_GL_DRAW_ARRAYS_H */