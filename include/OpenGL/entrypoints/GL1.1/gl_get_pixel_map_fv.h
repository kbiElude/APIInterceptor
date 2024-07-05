/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_GET_PIXEL_MAP_FV_H
#define AI_GL_GET_PIXEL_MAP_FV_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiGetPixelMapfv(GLenum   map,
                                     GLfloat* values);
}

#endif /* AI_GL_GET_PIXEL_MAP_FV_H */