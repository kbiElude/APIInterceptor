/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_RECT_I_H
#define AI_GL_RECT_I_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiRecti(GLint x1,
                             GLint y1,
                             GLint x2,
                             GLint y2);
}

#endif /* AI_GL_RECT_I_H */