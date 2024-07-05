/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_PIXEL_STOREI_H
#define AI_GL_PIXEL_STOREI_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiPixelStorei(GLenum pname,
                                   GLint  param);
}

#endif /* AI_GL_PIXEL_STOREI_H */