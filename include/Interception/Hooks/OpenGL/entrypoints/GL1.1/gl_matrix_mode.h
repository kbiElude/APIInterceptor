/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_MATRIX_MODE_H
#define AI_GL_MATRIX_MODE_H

#include "Interception/Hooks/OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiMatrixMode(GLenum mode);
}

#endif /* AI_GL_MATRIX_MODE_H */