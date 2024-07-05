/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_PIXEL_STOREF_H
#define AI_GL_PIXEL_STOREF_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void APIENTRY aiPixelStoref(GLenum  pname,
                                GLfloat param);
}

#endif /* AI_GL_PIXEL_STOREF_H */