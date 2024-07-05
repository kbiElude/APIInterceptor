/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_pixel_zoom.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiPixelZoom(GLfloat xfactor,
                                     GLfloat yfactor)
{
    AI_TRACE("glPixelZoom(xfactor=[%.4f], yfactor=[%.4f])",
             xfactor,
             yfactor);

    reinterpret_cast<PFNGLPIXELZOOMPROC>(OpenGL::g_cached_gl_pixel_zoom)(xfactor,
                                                                         yfactor);
}