/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_ACCUM_H
#define AI_GL_ACCUM_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiAccum(GLenum op,
                             GLfloat value);
}

#endif /* AI_GL_ACCUM_H */