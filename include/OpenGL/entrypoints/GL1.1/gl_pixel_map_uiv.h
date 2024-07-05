/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_PIXEL_MAP_UIV_H
#define AI_GL_PIXEL_MAP_UIV_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiPixelMapuiv(GLenum        map,
                                   GLsizei       mapsize,
                                   const GLuint* values);
}

#endif /* AI_GL_PIXEL_MAP_UIV_H */