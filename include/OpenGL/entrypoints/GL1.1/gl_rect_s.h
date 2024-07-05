/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_RECT_S_H
#define AI_GL_RECT_S_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiRects(GLshort x1,
                             GLshort y1,
                             GLshort x2,
                             GLshort y2);
}

#endif /* AI_GL_RECT_S_H */